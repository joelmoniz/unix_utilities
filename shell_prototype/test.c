#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void to_foreground() {
  signal(SIGTTOU, SIG_IGN);
  //create a new proces sgroup.
  setpgid(getpid(),getpid());
  //set it as fg group in the terminal
  tcsetpgrp(0,getpgid(getpid()));
}

void to_background() {
//to be called only if to_foreground hasn't been
  signal(SIGTTOU, SIG_IGN);
  //create a new proces sgroup.
  setpgid(getpid(),getpid());
}

static int validate_stdin(void) {
    pid_t fg = tcgetpgrp(STDIN_FILENO);
    int rc = 0;
    if(fg == -1) {
        printf("Piped\n");
    }  else if (fg == getpgrp()) {
        printf("foreground\n");
    } else {
        printf("background\n");
        rc = -1;
    }
    return rc;
}

int main() {
  pid_t n;
  signal(SIGQUIT, SIG_IGN); // ctrl+\
  // n = fork();
  int x =0;

  if ((n=fork())<0) {
    perror("Fork error");
  }
  else if (n==0) {
    int i=4;
    validate_stdin();
    // to_background();
    // validate_stdin();
    to_foreground();
    // validate_stdin();
    // while(i--) {
    //   printf(".");
    //   fflush(stdout);
    //   sleep(1);
    // }
    execlp("./dot.out", "./dot.out", (char *) NULL);
  }
  else {
    int stat = 0;
    int pid;
    // do {
    //   pid = waitpid(-1,stat, WEXITED|WSTOPPED|WUNTRACED);
      pid = waitpid(-1, &stat, WUNTRACED);
      printf("%d %d %d\n", pid, stat, WIFEXITED(stat));
    // }
    // while (pid != -1 && stat == NULL && !(WIFEXITED(*stat) || (WIFSTOPPED(*stat) && WSTOPSIG(*stat) == SIGTSTP)));
    printf("Back to parent\n");
  }
  return 0;
}