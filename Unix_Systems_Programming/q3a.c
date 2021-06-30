#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  fork();
  fork();
  printf("A\n");
  fork();
  printf("B\n");
  return 0;
}
