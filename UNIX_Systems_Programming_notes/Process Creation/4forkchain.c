/**
 * @file 4forkchain.c
 * @author Ahmed Nadeem (u2018047@giki.ed.pk; ahmed210899@gmail.com)
 * @brief A program that creates a chain of n processes, where n is defined
 * @version 0.1
 * @date 2021-05-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * @brief Defines the number of chained processes you want to create
 * 
 */
#define NUM_PROCESSES 4

/**
 * @brief main function
 * 
 * @return int 
 */
int main(void)
{
  pid_t childpid = 0;
  int i;

  for (i = 1; i <= NUM_PROCESSES; i++)
  {
    if (childpid = fork())
      break;
  }

  fprintf(stderr, "i:%d  process ID:%5ld  parent ID:%5ld  child ID:%5ld\n",
          i, (long)getpid(), (long)getppid(), (long)childpid);
  return 0;
}
