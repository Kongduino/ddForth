#include <sys/socket.h>
#include <sys/un.h>
#include <sys/poll.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

class MyGUI {
public:
  MyGUI(int);
  void CreateButton(char *, char *, int, int, int, int);
  void CreateListbox(char *, int, int, int, int, int);
  void CreatePopupMenu(char *, int, int, int, int);
  void AddLBrow(char *, char *);
  void AddPMrow(char *, char *);
  void Alert(char *);

private:
  int myClient_fd;
  char myBuffer[255];
};

MyGUI::MyGUI(int fd) {
  myClient_fd = fd;
}

void MyGUI::CreateButton(char *name, char *caption, int posx, int posy, int width, int height) {
  // "BT|TAGADA|Caption|20|320|-1|-1\n"
  int xxxxxx = snprintf(
    myBuffer, 255,
    "BT|%s|%s|%d|%d|%d|%d\n",
    name, caption, posx, posy, width, height
  );
  int n = send(myClient_fd, myBuffer, strlen(myBuffer), 0);
}

void MyGUI::CreateListbox(char *name, int posx, int posy, int width, int height, int rows) {
  // "LB|TOGODO|20|20|400|300|3\n"
  int xxxxxx = snprintf(
    myBuffer, 255,
    "LB|%s|%d|%d|%d|%d|%d\n",
    name, posx, posy, width, height, rows
  );
  int n = send(myClient_fd, myBuffer, strlen(myBuffer), 0);
}

void MyGUI::CreatePopupMenu(char *name, int posx, int posy, int width, int height) {
  // "PM|PM00|120|320|120|-1\n";
  int xxxxxx = snprintf(
    myBuffer, 255,
    "PM|%s|%d|%d|%d|%d\n",
    name, posx, posy, width, height
  );
  int n = send(myClient_fd, myBuffer, strlen(myBuffer), 0);
}

void MyGUI::AddLBrow(char *name, char *row) {
  // "ADDLB|TOGODO|Three|Columns|Total\n";
  // Last %s is %s|%s etc...
  int xxxxxx = snprintf(
    myBuffer, 255,
    "ADDLB|%s|%s\n",
    name, row
  );
  int n = send(myClient_fd, myBuffer, strlen(myBuffer), 0);
}

void MyGUI::AddPMrow(char *name, char *row) {
  // "ADDPM|PM00|Choice 0\n";
  int xxxxxx = snprintf(
    myBuffer, 255,
    "ADDPM|%s|%s\n",
    name, row
  );
  int n = send(myClient_fd, myBuffer, strlen(myBuffer), 0);
}

void MyGUI::Alert(char *msg) {
  // "MSG|Ok Thanks!\n";
  int xxxxxx = snprintf(
    myBuffer, 255,
    "MSG|%s\n",
    msg
  );
  int n = send(myClient_fd, myBuffer, strlen(myBuffer), 0);
}

int main() {
  int server_fd, client_fd;
  struct sockaddr_un server_addr, client_addr;
  socklen_t client_len;
  char buffer[256];
  const char* socket_path = "/tmp/my_unix_socket";

  // Create socket
  server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (server_fd == -1) {
    perror("socket");
    return 1;
  }

  // Prepare address
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sun_family = AF_UNIX;
  strncpy(server_addr.sun_path, socket_path, sizeof(server_addr.sun_path) - 1);
  unlink(socket_path); // Remove existing socket file

  // Bind socket
  if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
    perror("bind");
    close(server_fd);
    return 1;
  }

  // Listen for connections
  if (listen(server_fd, 5) == -1) {
    perror("listen");
    close(server_fd);
    return 1;
  }
  std::cout << "Server listening on " << socket_path << std::endl;
  // Accept connection
  client_len = sizeof(client_addr);
  client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
  if (client_fd == -1) {
    perror("accept");
    close(server_fd);
    return 1;
  }

  std::cout << "Client connected." << std::endl;
  MyGUI gui(client_fd);
  gui.CreateButton((char *)"TAGADA", (char *)"Click me!", 20, 320, -1, -1);
  std::cout << "Creating button." << std::endl;
  gui.CreateListbox((char *)"TOGODO", 20, 20, 400, 300, 3);
  std::cout << "Creating ListBox." << std::endl;
  gui.CreatePopupMenu((char *)"PM00", 120, 320, 120, -1);
  std::cout << "Creating Popup Menu." << std::endl;

  for (int ix = 0; ix < 5; ix++) {
    char test[32];
    int xx = snprintf(test, 32, "Choice %d", ix);
    gui.AddPMrow((char *)"PM00", test);
    std::cout << "Adding Choice " << ix << " to Popup Menu." << std::endl;
  }
  struct pollfd pfd;
  pfd.fd = client_fd;
  pfd.events = POLLIN | POLLHUP | POLLERR; // Monitor for input, hangup, and errors
  int rowIndex = 4;
  while (true) {
    // Receive data
    int ret = poll(&pfd, 1, 1000); // timeout_ms can be -1 for infinite wait
    if (ret > 0) {
      if (pfd.revents & POLLHUP) {
        std::cout << "Peer disconnected (POLLHUP)." << std::endl;
        break;
        // Handle disconnection
      } else if (pfd.revents & POLLERR) {
        std::cout << "Socket error (POLLERR)." << std::endl;
        break;
        // Handle error
      } else if (pfd.revents & POLLIN) {
        // Data available for reading
        ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received > 0) {
          buffer[bytes_received] = '\0';
          std::cout << "Received: " << buffer << std::endl;
          if (strcmp(buffer, "BT|TAGADA|PUSH") == 0) {
            gui.AddLBrow((char *)"TOGODO", (char *)"Three|Columns|Total");
            gui.Alert((char *)"Ok Thanks!");
            std::cout << "Adding row to LB" << std::endl;
            std::cout << "Sending MSG|Ok Thanks!\n" << std::endl;
          } else if (strncmp(buffer, "PM|PM00|SELECT|", 15) == 0) {
            char row[32];
            int xxxxxx = snprintf(row, 32, "Selected|Row|%s\n", buffer+15);
            gui.AddLBrow((char *)"TOGODO", row);
          }
        }
      }
    } else if (ret == 0) {
      std::cout << "Poll timed out." << std::endl;
    } else {
      perror("poll error");
      break;
    }
  }
  // Close sockets
  close(client_fd);
  close(server_fd);
  unlink(socket_path);  // Clean up socket file
  return 0;
}
