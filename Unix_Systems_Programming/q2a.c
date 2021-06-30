#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/**
 * @brief Write a program that sleeps for a random duration between 0 and 5 seconds
 *        and then displays,on a single line,its process id and parent process's id.
 *        [Hint: getpid(), getppid()]
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
  srand(time(NULL));
  sleep(rand() % 6);
  fprintf(stderr, "process ID:%ld  parent ID:%ld\n",
          (long)getpid(), (long)getppid());
  return 0;
}
