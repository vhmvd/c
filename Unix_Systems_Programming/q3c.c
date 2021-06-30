#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  fork();
  fork();
  fprintf(stderr, "A");
  fork();
  fprintf(stderr, "B");
  return 0;
}