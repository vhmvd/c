#include <stdio.h>
#include "stack.h"

coordinates stack[MAX_SIZE];
int top = 0;

/**
 * @brief 0 is false 1 is true
 * 
 * @return int 
 */
int isEmpty()
{
  if (top == 0)
    return 1;
  else
    return 0;
}

/**
 * @brief 0 is false 1 is true
 * 
 * @return int 
 */
int isFull()
{
  if (top == MAX_SIZE)
    return 1;
  else
    return 0;
}

/**
 * @brief Returns the top element of stack
 * 
 * @return coordinates 
 */
coordinates peek()
{
  if (top != 0)
    return stack[top - 1];
  else
    perror("Stack is empty\n");
}

/**
 * @brief Removes the top element of stack
 * 
 * @return coordinates 
 */
coordinates pop()
{
  coordinates data;
  if (isEmpty() != 1)
  {
    data = stack[top - 1];
    top = top - 1;
    return data;
  }
  else
    perror("Error: Stack is empty\n");
}

/**
 * @brief Pushes cords on stack
 * 
 * @param data 
 */
void push(coordinates data)
{

  if (isFull() == 0)
    stack[top++] = data;
  else
    perror("Error: Stack is full\n");
}

/**
 * @brief Resets stack position
 * 
 */
void clear()
{
  top = 0;
}
