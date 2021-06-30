#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
  pid_t childpid = 0;
  int i;
  for (i = 1; i <= 3; i++)
    if ((childpid = fork()) <= 0)
      break;

  if ((long)childpid == 0)
    execv("q2a", argv);

  if (childpid != 0 && childpid != -1)
  {
    for (i = 1; i <= 3; i++)
    {
      childpid = waitpid(-1, NULL, 0);
      printf("Child with pid %ld completed execution\n", (long)childpid);
    }
  }

  return 0;
}