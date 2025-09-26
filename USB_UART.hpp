#include <iostream>
#include <string>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>

using namespace std;
bool popFloatFromStack(float *);
bool popFromLoopStack(int *);
bool popIntegerFromJumpStack(int *);
bool popIntegerFromStack(int *);
bool popStringFromStack(string *);
bool putFloatOnStack(float);
bool putIntegerOnJumpStack(int);
bool putIntegerOnStack(int);
bool putStringOnStack(string);
void logStack(char *);
void logInconsistent(char *who);
void logStackOverflow(char *who);
void logThis();

bool read_byte(char&);
string readUntil(char);
bool handleOpenPort();
bool handleReadLinePort();
bool handleClosePort();
bool handleFlushPort();

int serial_port = -1;

bool read_byte(char& byte) {
  if (serial_port == -1) return false;
  ssize_t num_bytes = read(serial_port, &byte, 1);
  return num_bytes == 1; // Placeholder
}

string readUntil(char delimiter) {
  string received_data;
  if (serial_port == -1) return received_data;
  char byte;
  while (true) {
    // Read a single byte (or small chunk) from the serial port
    // This would involve platform-specific API calls or library methods
    // e.g., ReadFile on Windows, read on Linux, or a library's read_byte function
    if (read_byte(byte)) {
      // Assume read_byte returns true on success
      received_data += byte;
      if (byte == delimiter) {
        break;  // Delimiter found
      }
    } else {
      // Handle read error or timeout
      break;
    }
  }
  return received_data;
}

bool handleOpenPort() {
  // ( 9600 s" /dev/tty.usb..." -- n ) UOPEN
  // n = TRUE / FALSE
  if (serial_port != -1) {
    // Already open ah
    putIntegerOnStack(0);
    return false;
  }
  string portName;
  if (popStringFromStack(&portName) == false) {
    logStackOverflow((char *)"handleOpenPort/0");
    putIntegerOnStack(0);
    return false;
  }
  int baudRate;
  if (popIntegerFromStack(&baudRate) == false) {
    logStackOverflow((char *)"handleOpenPort/1");
    putIntegerOnStack(0);
    return false;
  }
  serial_port = open(portName.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
  if (serial_port < 0) {
    cerr << "Error " << errno << " from open: " << strerror(errno) << endl;
    putIntegerOnStack(0);
    return false;
  }
  struct termios tty;
  memset(&tty, 0, sizeof(tty));
  if (tcgetattr(serial_port, &tty) != 0) {
    cerr << "Error " << errno << " from tcgetattr: " << strerror(errno) << endl;
    close(serial_port);
    putIntegerOnStack(0);
    return false;
  }

/*
 * Standard speeds
#define B0      0
#define B50     50
#define B75     75
#define B110    110
#define B134    134
#define B150    150
#define B200    200
#define B300    300
#define B600    600
#define B1200   1200
#define B1800   1800
#define B2400   2400
#define B4800   4800
#define B9600   9600
#define B19200  19200
#define B38400  38400
#if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
#define B7200   7200
#define B14400  14400
#define B28800  28800
#define B57600  57600
#define B76800  76800
#define B115200 115200
#define B230400 230400
#define EXTA    19200
#define EXTB    38400
#endif
 */

  cfsetispeed(&tty, baudRate);       // Set input baud rate to 9600
  cfsetospeed(&tty, baudRate);       // Set output baud rate to 9600
  tty.c_cflag &= ~PARENB;         // No parity
  tty.c_cflag &= ~CSTOPB;         // 1 stop bit
  tty.c_cflag &= ~CSIZE;          // Clear data size bits
  tty.c_cflag |= CS8;             // 8 data bits
  tty.c_cflag |= CREAD | CLOCAL;  // Enable receiver, ignore modem control lines
  cfmakeraw(&tty);                // Set raw mode for general-purpose serial communication
  tty.c_cc[VMIN] = 0;             // Read returns immediately if no data
  tty.c_cc[VTIME] = 5;            // 0.5 seconds timeout for read
  if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
    cerr << "Error " << errno << " from tcsetattr: " << strerror(errno) << endl;
    close(serial_port);
    putIntegerOnStack(0);
    return false;
  }
  cout << "Serial port configured successfully." << endl;
  // Example: Write a string
  //   string data_to_send = "Hello Serial!\n";
  //   write(serial_port, data_to_send.c_str(), data_to_send.length());
  //   cout << "Sent: " << data_to_send;
  // Example: Read data
  putIntegerOnStack(1);
  return true;
}

bool handleReadLinePort() {
  // ( -- s ) UREADL
  if (serial_port == -1) return false;
  string message = readUntil('\n');
  // cout << message;
  putStringOnStack(message);
  return true;
}

bool handleClosePort() {
  // ( -- ) UCLOSE
  if (serial_port == -1) return true;
  tcflush(serial_port, TCIOFLUSH);
  close(serial_port);
  serial_port = -1;
  return true;
}

bool handleFlushPort() {
  if (serial_port == -1) return false;
  tcflush(serial_port, TCIOFLUSH);
  return true;
}



// end
//   // Flush the input buffer (data received but not yet read)
//   tcflush(serial_port, TCIFLUSH);
//   // Flush the output buffer (data waiting to be sent)
//   tcflush(serial_port, TCOFLUSH);
//   // Flush both input and output buffers
//   tcflush(serial_port, TCIOFLUSH);
// 
//   char read_buf[256];
//   while (1) {
//     //     ssize_t num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
//     //     if (num_bytes > 0) {
//     //       read_buf[num_bytes] = '\0';  // Null-terminate the received data
//     //       cout << "Received: " << read_buf;
//     //     }
//   }
//   close(serial_port);
