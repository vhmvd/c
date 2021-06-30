/**
 * @file 2twoprocesses.c
 * @author Ahmed Nadeem (u2018047@giki.ed.pk; ahmed210899@gmail.com)
 * @brief Creates a process and executes by checking the return value of the
 *        child process.
 * @version 0.1
 * @date 2021-05-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

/**
 * @brief main function
 * 
 * @return int 
 */
int main(void)
{
  pid_t childpid;

  childpid = fork();
  if (childpid == -1)
  {
    perror("Failed to fork");
    return 1;
  }
  if (childpid == 0) /* child code */
    printf("I am child %ld\n", (long)getpid());
  else /* parent code */
    printf("I am parent %ld\n", (long)getpid());
  return 0;
}