#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <sys/

// _start: 
//   mov sp 0x120
//   call main

int run_child(char *exe) {
  printf("Starting %s\n", exe);
}


int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: gandalf <executable>\n");
    return 1;
  }
  
  pid_t child = fork();

  if (child == -1) {
    printf("Failed to fork\n");
    return 1;
  } else if (child == 0) {
    printf("Child process\n");
    run_child(argv[1]);
  } else {
    printf("Parent process\n");

  }
}