#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <dwarf/elf.h>


int run_child(char *exe) {
  printf("Starting %s\n", exe);
  execl(exe, (char *) NULL);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: gandalf <executable>\n");
    return 1;
  }
  char *child_exe = argv[1];
  
  FILE *file = fopen(child_exe, "r");
  if (!file) {
    exit(1);
  }
  parse_elf(file);
  
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