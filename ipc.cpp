#include <sys/socket.h>
#include <sys/un.h>
#include <sys/poll.h>
#include <unistd.h>
#include <iostream>
#include <cstring>


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
  char btnCreate[] = "BT|TAGADA|Caption|20|320|-1|-1\n";
  char lbCreate[] = "LB|TOGODO|20|20|400|300|3\n";
  char lbAdd[] = "ADDLB|TOGODO|Three|Columns|Total\n";
  int n = send(client_fd, btnCreate, strlen(btnCreate), 0);
  std::cout << "Sending " << btnCreate << std::endl;
  n = send(client_fd, lbCreate, strlen(lbCreate), 0);
  std::cout << "Sending " << lbCreate << std::endl;
  n = send(client_fd, lbAdd, strlen(lbAdd), 0);
  std::cout << "Sending " << lbAdd << std::endl;
  struct pollfd pfd;
  pfd.fd = client_fd;
  pfd.events = POLLIN | POLLHUP | POLLERR;  // Monitor for input, hangup, and errors
  while (true) {
    // Receive data
    int ret = poll(&pfd, 1, 1000);  // timeout_ms can be -1 for infinite wait
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
            n = send(client_fd, lbAdd, strlen(lbAdd), 0);
            n = send(client_fd, "MSG|Ok Thanks!\n", 15, 0);
            std::cout << "Sending " << lbAdd << std::endl;
            std::cout << "Sending MSG|Ok Thanks!\n" << std::endl;
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
