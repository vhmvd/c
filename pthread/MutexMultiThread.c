#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void* threadFunction(void*);

int main()
{
  const int SIZE = 5;
  int i;
  int pth_return;
  pthread_t tid[SIZE];
  for(i=0; i<5; i++)
  {
    pth_return = pthread_create(&(tid[i]), NULL, threadFunction, (void*)&(tid[i]));
    if(pth_return != 0)
    {
      printf("\nThread can't be created : [%s]\n" "Press 'Enter' to continue . . .", strerror(pth_return));
    }
  }
  for(i=0; i<5; i++)
  {
    pthread_join(tid[i], NULL);
  }
  return 0;
}

void* threadFunction(void* vargp)
{
  const int loop = 50;
  int i;
  int* myid = (int*)vargp;
  printf("\n\n----------\nThread ID %u has started\n----------\n\n", *myid);

  for(i=0; i<50; i++)
  {
    printf("Thread ID %u printing\n", *myid);
  }
  printf("\n\n----------\nThread ID %u has finished\n----------\n\n", *myid);
  return NULL;
}