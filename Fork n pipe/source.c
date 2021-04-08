#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

const int p1_r = 0;
const int p2_2 = 1;
const int p2_r = 2;
const int p1_w = 3;
const int num_pipes = 2;

int main(int argc, char *argv[])
{
  int f_d[2 * num_pipes];
  int value = 0, len, i;
  pid_t process_id;

  for (i = 0; i < num_pipes; ++i)
  {
    if (pipe(f_d + (i * 2)) < 0)
    {
      perror("Failed to allocate pipes");
      exit(EXIT_FAILURE);
    }
  }

  // fork() for child process
  if ((process_id = fork()) < 0)
  {
    perror("Failed to fork process");
    return EXIT_FAILURE;
  }

  if (process_id == 0)
  {
    close(f_d[p1_r]);
    close(f_d[p1_w]);
    process_id = getpid();

    clock_t begin = clock();
    len = read(f_d[p2_r], &value, sizeof(value));
    if (len < 0)
    {
      perror("Child: Failed to read data from pipe");
      exit(EXIT_FAILURE);
    }
    else if (len == 0)
    {
      fprintf(stderr, "Child: Read EOF from pipe");
    }
    else
    {
      printf("Child %d: Received %d\n", process_id, value);

      clock_t end = clock();
      double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

      printf("Time taken: %f\n", time_spent);

      // Changing the value
      value *= 2;

      printf("Child %d: Sending %d to parent\n", process_id, value);
      if (write(f_d[p2_2], &value, sizeof(value)) < 0)
      {
        perror("Child: Failed to write response value");
        exit(EXIT_FAILURE);
      }
    }
    close(f_d[p2_r]);
    close(f_d[p2_2]);

    return EXIT_SUCCESS;
  }

  clock_t begin = clock();

  close(f_d[p2_r]);
  close(f_d[p2_2]);
  process_id = getpid();
  value = 42;
  printf("Parent %d: Sending %d to child\n", process_id, value);
  if (write(f_d[p1_w], &value, sizeof(value)) != sizeof(value))
  {
    perror("Parent: Failed to send value to child ");
    exit(EXIT_FAILURE);
  }
  len = read(f_d[p1_r], &value, sizeof(value));
  if (len < 0)
  {
    perror("Parent: failed to read value from pipe");
    exit(EXIT_FAILURE);
  }
  else if (len == 0)
  {
    fprintf(stderr, "Parent %d: Read EOF from pipe", process_id);
  }
  else
  {
    printf("Parent %d: Received %d\n", process_id, value);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Time taken: %f\n", time_spent);
  }
  close(f_d[p1_r]);
  close(f_d[p1_w]);
  wait(NULL);

  return EXIT_SUCCESS;
}

/*
Main factors in context switching cost includes cache sahring between tasks, translation lookaside buffer flushing and runnning of
the task scheduler adds major perfomance overhead

A system call involves the following actions, which do not occur during a simple procedure call, and thus entails a high overhead:
-A context switch
-A trap to a specific location in the interrupt vector
-Control passes to a service routine, which runs in 'monitor' mode
-The monitor determines what system call has occurred
-Monitor verifies that the parameters passed are correct and legal


Throughput - Number of processes completed per unit time. May range from 10 / second to 1 / hour depending on the specific processes.
Turnaround time - Time required for a particular process to complete, from submission time to completion. ( Wall clock time. )
Waiting time - How much time processes spend in the ready queue waiting their turn to get on the CPU
*/