#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
  pid_t childpid = 0;
  int i;
  for (i = 1; i < 4; i++)
    if ((childpid = fork()) <= 0)
      break;

  if((long)childpid == 0)
    execv("q2a", argv);
  return 0;
}