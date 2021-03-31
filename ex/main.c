#include <stdio.h>

struct Node
{
  int data;
  struct Node* next;
};

void PrintReverseEven(struct Node *ptr);

int main()
{
  return 0;
}

void PrintReverseEven(struct Node *ptr) 
{
  if(ptr->next != NULL)
  {
    PrintReverseEven(ptr->next);
  }
  if(ptr->data % 2 == 0)
  {
    printf("%d ", ptr->data);
    return;
  }
}
