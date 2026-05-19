#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#define PORTNUM 25555
#define MAXSIZE 1024

int main(int argc, char *argv[])
{
  int client_fd;
  // Stores the connecting client's address information after accept() returns.
  struct sockaddr_in dest;
  char *msg = "Hello from Client";
  char buffer[MAXSIZE];
  char option[MAXSIZE];
  int len;

  // Set up server address structure
  dest.sin_family = AF_INET;
  dest.sin_addr.s_addr = inet_addr("127.0.0.1");
  dest.sin_port = htons(PORTNUM);

  // Create socket
  if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("\nSocket Creation Error\n");
    exit(EXIT_FAILURE);
  }

  // Connect to server
  if (connect(client_fd, (struct sockaddr *)&dest, sizeof(struct sockaddr)) < 0)
  {
    perror("\nError creating connection\n");
    exit(EXIT_FAILURE);
  }

  // Gets size of input received from server
  len = recv(client_fd, buffer, MAXSIZE, 0);
  // Ensures it is null terminated
  buffer[len] = '\0';
  // Print the buffer string
  printf("%s", buffer);

  // Option user will select if they want to play
  // Read from stdin
  scanf(" %s", option);
  // Send that response to server
  send(client_fd, option, strlen(option), 0);

  // Loop through 5 questions
  for (int i = 0; i < 5; i++)
  {
    // Gets size of input received from server
    memset(buffer, 0, MAXSIZE);
    len = recv(client_fd, buffer, MAXSIZE, 0);
    // Ensures it is null terminated
    buffer[len] = '\0';
    // Print the buffer string, which should be the question
    printf("\n%s\n", buffer);

    // Now we send answer to that question
    // Read from stdin
    scanf("%s", option);
    // Send that response to server
    send(client_fd, option, strlen(option), 0);
  }

  // Receive final score from server
  memset(buffer, 0, MAXSIZE);
  len = recv(client_fd, buffer, MAXSIZE - 1, 0);
  printf("%s", buffer);

  // Close client socket
  close(client_fd);

  return 0;
}