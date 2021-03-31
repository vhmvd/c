#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringManipulation.h"

int main(int argc, char *argv[])
{
  char solution[100] = {'\0'};
  performOperations(solution, argc, argv);
  printf("%s\n", solution);
  return 0;
}