/**
 * @file 3badfork.c
 * @author Ahmed Nadeem (u2018047@giki.ed.pk; ahmed210899@gmail.com)
 * @brief The parent sets the mypid value to its process ID before the fork.
 *        When fork executes, the child gets a copy of the process address space, including all 
 *        variables. Since the child does not reset mypid, the value of mypid for the child 
 *        does not agree with the value returned by getpid.
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
  pid_t mypid;

  mypid = getpid();
  childpid = fork();
  if (childpid == -1)
  {
    perror("Failed to fork");
    return 1;
  }
  if (childpid == 0) /* child code */
    printf("I am child %ld, ID = %ld\n", (long)getpid(), (long)mypid);
  else /* parent code */
    printf("I am parent %ld, ID = %ld\n", (long)getpid(), (long)mypid);
  return 0;
}
