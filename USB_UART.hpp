#include <iostream>
#include <string>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include <sys/ioctl.h>

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

int serial_port = -1;

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

  cfsetispeed(&tty, baudRate); // Set input baud rate to 9600
  cfsetospeed(&tty, baudRate); // Set output baud rate to 9600
  tty.c_cflag &= ~PARENB; // No parity
  tty.c_cflag &= ~CSTOPB; // 1 stop bit
  tty.c_cflag &= ~CSIZE; // Clear data size bits
  tty.c_cflag |= CS8; // 8 data bits
  tty.c_cflag |= CREAD | CLOCAL;  // Enable receiver, ignore modem control lines
  cfmakeraw(&tty); // Set raw mode for general-purpose serial communication
  tty.c_cc[VMIN] = 0; // Read returns immediately if no data
  tty.c_cc[VTIME] = 5; // 0.5 seconds timeout for read
  if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
    cerr << "Error " << errno << " from tcsetattr: " << strerror(errno) << endl;
    close(serial_port);
    putIntegerOnStack(0);
    return false;
  }
  cout << "Serial port configured successfully." << endl;
  putIntegerOnStack(1);
  return true;
}

bool handleClosePort() {
  // ( -- ) UCLOSE
  if (serial_port == -1) return true;
  // close fails gracefully – unlike me.
  tcflush(serial_port, TCIOFLUSH);
  close(serial_port);
  serial_port = -1;
  return true;
}

bool handleFIONREAD() {
  if (serial_port == -1) return false;
  int argp = -1;
  int rslt = ioctl(serial_port, FIONREAD, &argp);
  if (rslt == -1) return false;
  putIntegerOnStack(argp);
  return true;
}

bool read_byte(char& byte) {
  if (serial_port == -1) return false;
  ssize_t num_bytes = 0;
  uint8_t count = 0; // timeout x 0.5 seconds
  while (num_bytes == 0 && count < 3) {
    num_bytes = read(serial_port, &byte, 1);
    count += 1;
  }
  if (num_bytes == 0) return false;
  return true;
}

bool readUntil(char delimiter, string *received_data) {
  if (serial_port == -1) return false;
  char byte;
  while (true) {
    // Read a single byte (or small chunk) from the serial port
    // This would involve platform-specific API calls or library methods
    // e.g., ReadFile on Windows, read on Linux, or a library's read_byte function
    if (read_byte(byte)) {
      // Assume read_byte returns true on success
      received_data += byte;
      if (byte == delimiter) {
        break; // Delimiter found
      }
    } else {
      // Handle read error or timeout
      return false;
    }
  }
  return true;
}

bool handleReadRawPort() {
  // ( n -- s ) UREADRAW
  string received_data;
  if (serial_port == -1) return false;
  int i0;
  if (popIntegerFromStack(&i0) == false) {
    logStackOverflow((char *)"handleReadRawPort/0");
    return false;
  }
  char byte;
  while (i0 > 0) {
    // Read a single byte (or small chunk) from the serial port
    // This would involve platform-specific API calls or library methods
    // e.g., ReadFile on Windows, read on Linux, or a library's read_byte function
    if (read_byte(byte)) {
      // Assume read_byte returns true on success
      received_data += byte;
      i0 -= 1;
    } else {
      // Handle read error or timeout
      return false;
    }
  }
  putStringOnStack(received_data);
  return true;
}

bool handleReadLinePort() {
  // ( -- s ) UREADL
  string received_data;
  if (serial_port == -1) return false;
  char byte;
  while (true) {
    // Read a single byte (or small chunk) from the serial port
    // This would involve platform-specific API calls or library methods
    // e.g., ReadFile on Windows, read on Linux, or a library's read_byte function
    if (read_byte(byte)) {
      // Assume read_byte returns true on success
      if (byte == '\n') {
        break; // Delimiter found
      } else if (byte != '\r') {
        // skip \r
        received_data += byte;
      }
    } else {
      // Handle read error or timeout
      return false;
    }
  }
  putStringOnStack(received_data);
  return true;
}

bool handleReadCharPort() {
  // ( -- c ) UREADC
  char byte;
  if (serial_port == -1) return false;
  ssize_t num_bytes = 0;
  uint8_t count = 0; // timeout x 0.5 seconds
  while (num_bytes == 0 && count < 3) {
    num_bytes = read(serial_port, &byte, 1);
    count += 1;
  }
  if (num_bytes == 0) return false;
  xxxxxx = snprintf((char *)msg, 255, "%c", byte);
  putStringOnStack(msg);
  return true;
}

bool handleReadUntilPort() {
  // ( c -- s ) UREADUNTIL
  if (serial_port == -1) return false;
  char delim;
  string d;
  // c can be a uint8_t or a string
  // in the later case, the first char will be used
  if(dataStack.at(dataStack.size() - 1) == xINTEGER) {
    int i0;
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char *)"handleReadUntilPort/0");
      return false;
    }
    delim = (uint8_t) (i0 & 0xFF);
  } else if (dataStack.at(dataStack.size() - 1) == xSTRING) {
    if (popStringFromStack(&d) == false) {
      logStackOverflow((char *)"handleReadUntilPort/1");
      return false;
    }
    delim = d.at(0);
  }
  if (readUntil(delim, &d)) {
    putStringOnStack(d);
    return true;
  }
  return false;
}

bool handleReadDiscardPort() {
  // ( s -- ) UDISCARDUNTIL
  // c can be a uint8_t or a string
  // in the later case, the first char will be used
  if (serial_port == -1) return false;
  char delim;
  string d;
  if(dataStack.at(dataStack.size() - 1) == xINTEGER) {
    int i0;
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char *)"handleReadDiscardPort/0");
      return false;
    }
    delim = (uint8_t) i0 & 0xFF;
  } else if (dataStack.at(dataStack.size() - 1) == xSTRING) {
    if (popStringFromStack(&d) == false) {
      logStackOverflow((char *)"handleReadDiscardPort/1");
      return false;
    }
    delim = d.at(0);
  }
  char byte;
  while (true) {
    // Read a single byte (or small chunk) from the serial port
    // This would involve platform-specific API calls or library methods
    // e.g., ReadFile on Windows, read on Linux, or a library's read_byte function
    if (read_byte(byte)) {
      // Assume read_byte returns true on success
      if (byte == delim) {
        break; // Delimiter found
      }
    } else {
      // Handle read error or timeout
      break;
    }
  }
  return true;
}

bool handleFlushPort() {
  if (serial_port == -1) return true;
  tcflush(serial_port, TCIOFLUSH);
  return true;
}

bool handleWritePort() {
  // Write a string ( s -- )
  if (serial_port == -1) return false;
  string s;
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleWritePort/0");
    return false;
  }
  write(serial_port, s.c_str(), s.length());
  cout << "Sent to USB: " << s << endl;
  return true;
}


// end
