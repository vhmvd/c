/**
 * @file simplefork.c
 * @author Ahmed Nadeem (u2018047@giki.ed.pk; ahmed210899@gmail.com)
 * @brief Creates a simple child process which executes exactly the same instructions
 *        as the parent.
 * @version 0.1
 * @date 2021-05-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <unistd.h>

/**
 * @brief main function
 * 
 * @return int 
 */
int main(void)
{
  int x;

  x = 0;
  fork();
  x = 1;
  printf("I am process %ld and my x is %d\n", (long)getpid(), x);
  return 0;
}
