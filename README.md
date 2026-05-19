# Simple-Client-Server-Program-with-Sockets
A TCP socket-based quiz server that tests clients on Unix/Linux programming concepts with 43 questions, random selection and score tracking

# Unix Programming Quiz Server

A TCP socket-based quiz server that tests clients on Unix/Linux programming concepts. The server randomly selects 5 questions from a database of 43, evaluates answers, and provides a final score.

## 👤 Author
**Tirenioluwa Aruwajoye** (24388243)

## 📋 Features

| Feature | Status |
|---------|--------|
| TCP socket server (port 25555) | ✅ |
| Random question selection (43 questions) | ✅ |
| Score tracking (5 questions) | ✅ |
| Single client connection | ✅ |
| Right/Wrong answer feedback | ✅ |
| Final score display | ✅ |

## 🛠 Requirements

- Linux/Unix environment (or WSL)
- GCC compiler


## 📊 Question Database Topics

| Category | Examples |
|----------|----------|
| Memory Management | Stack, Heap, malloc(), calloc(), free() |
| Process Management | fork(), pthreads, process address space |
| File Operations | fopen(), fclose(), chmod, chown |
| Compilation | Preprocessing, linking, assembler |
| Signals | SIGINT(2), SIGTERM(15), SIGSEGV(11), SIGCHLD(17) |
| Networking | sockets, IPv4/IPv6, ssh, 127.0.0.1 |
| System Architecture | 32-bit vs 64-bit, pointer sizes |

## 🔧 Compilation

```bash
# Compile server
gcc -o quiz-server server.c -Wall -Wextra

# Compile client
gcc -o quiz-client client.c -Wall -Wextra

Welcome to Unix Programming Quiz!
The quiz comprises five questions posed to you one after the other.
You have only one attempt to answer a question.
Your final score will be sent to you after conclusion of the quiz.
To start the quiz, press Y and <enter>.
To quit the quiz, press q and <enter>.
y

In a 32-bit system architecture, each process can address 4 Giga bytes of memory. Y or N?
Y

Right Answer

Is Stack a section of a process's address space? (Y or N)
Y

Right Answer

What is the program that allows users to run programs with security privileges of another user? (Hint: Answer is a 4-letter word.)
sudo

Right Answer

What does the malloc() library function return on failure? (Hint: A four-letter word)
NULL

Right Answer

Is malloc() a system call? (Y or N)
N

Right Answer

Your quiz score is 5/5. Goodbye!
