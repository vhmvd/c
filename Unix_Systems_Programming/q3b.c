#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  fork();
  fork();
  printf("A");
  fork();
  printf("B");
  return 0;
}
