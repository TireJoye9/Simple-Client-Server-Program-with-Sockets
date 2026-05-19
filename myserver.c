#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include "QuizDB.h"
#include <time.h>
#define PORTNUM 25555
#define MAXSIZE 1024
#define NUMBER_OF_QUESTIONS 43


int main (int argc, char *argv[])
{
  srand(time(0));
  int server_fd, consocket;
  struct sockaddr_in dest, serv;
  socklen_t socksize;
  char buffer[MAXSIZE];
  char *result;
  char *opening_msg = "Welcome to Unix Programming Quiz!\n The quiz comprises five questions posed to you one after the other.\n You have only one attempt to answer a question.\n Your final score will be sent to you after conclusion of the quiz.\n To start the quiz, press Y and <enter>.\n To quit the quiz, press q and <enter>.\n";
  int quiz_running = 0;
  int user_score = 0;
  int question_number[5];
  extern char* QuizQ[];
  extern char* QuizA[];

  // Initialize server address structure to zero
  memset(&serv, 0, sizeof(serv));
  // Set address family to IPv4
  serv.sin_family = AF_INET;
  // Listen on localhost only
  serv.sin_addr.s_addr = inet_addr("127.0.0.1");
  // Set port number
  serv.sin_port = htons(PORTNUM);

  // Generate 5 random question indices
  for (int i = 0; i < 5; i++)
  {
    // Assigns array with random numbers, selects random number of question each time
    question_number[i] = rand() % NUMBER_OF_QUESTIONS;
  }

  // Create socket
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("\n Socket creation error \n");
    exit(EXIT_FAILURE);
  }

  // Allow reuse of address
  int opt = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
  {
    perror("setsockopt failed");
  }

  // Bind IP address to server_fd
  if (bind(server_fd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
  {
    perror("\nBind error\n");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  // Second parameter limits number of pending requests
  if (listen(server_fd, 3) < 0)
  {
    exit(EXIT_FAILURE);
  }

  printf("<Listening on %s:%d>\n", inet_ntoa(serv.sin_addr), PORTNUM);
  printf("<Press ctrl-C to terminate>\n");

  // Creates a new connected socket using the accept() function, and returns a new file descriptor referring to that socket.
  socksize = sizeof(dest);
  if ((consocket = accept(server_fd, (struct sockaddr*)&dest, &socksize)) < 0)
  {
    perror("\nError Accepting connection\n");
    exit(EXIT_FAILURE);
  }

  // Sends opening message to the client, only handles one client at a time
  send(consocket, opening_msg, strlen(opening_msg), 0);

  // Either yes or no anything else is rejected prompt user to enter again
  int len = recv(consocket, buffer, MAXSIZE, 0);
  buffer[len] = '\0';
  printf("\nUser selected: %s\n", buffer);

  if (strcasecmp(buffer, "y") == 0)
  {
    printf("Starting Quiz\n");
    quiz_running = 1;
  }
  else if (strcasecmp(buffer, "q") == 0)
  {
    printf("Quiting..........\n");
    close(consocket);
    exit(EXIT_FAILURE);
  }
  else
  {
    printf("Unrecognsied input\nQuiting..........\n");
    close(consocket);
    exit(EXIT_FAILURE);
  }
  
  if (quiz_running)
  {
    // Provide Questions
    for (int i = 0; i < 5; i++)
    {
      char *question = QuizQ[question_number[i]];
      send(consocket, question, strlen(question), 0);

      memset(buffer, 0, MAXSIZE);
      int len = recv(consocket, buffer, MAXSIZE, 0);
      buffer[len] = '\0';
      printf("\nUser selected: %s\n", buffer);

      if (strcasecmp(buffer, QuizA[question_number[i]]) == 0)
      {
        result = "Right Answer\n";
        send(consocket, result, strlen(result), 0);
        user_score++;
      }
      else
      {
        char concatenated_result[100] = "Wrong Answer. Right answer is ";
        strcat(concatenated_result, QuizA[question_number[i]]);
        strcat(concatenated_result, "\n");
        result = concatenated_result;
        send(consocket, result, strlen(result), 0);
      }
    }

    // Send final score to client
    char score_msg[100];
    snprintf(score_msg, sizeof(score_msg), "\nYour quiz score is %d/5. Goodbye!\n", user_score);
    send(consocket, score_msg, strlen(score_msg), 0);
  }

  // Close client socket
  close(consocket);

  return 0;
}