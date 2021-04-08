// Arup Guha
// 6/20/07
// Written in COP 3502 to illustrate an array implementation of a stack.
 //modified by Tanvir Ahmed 6/1/2020

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include<string.h>

// The array will store the items in the stack, first in
// index 0, then 1, etc. top will represent the index
// to the top element in the stack. If the stack is
// empty top will be -1.

#define SIZE 30
#define EMPTY -1

struct stack {
    char items[SIZE];
    int  top;
};

void initialize(struct stack* stackPtr);
int  full(struct stack* stackPtr);
int  push(struct stack* stackPtr, char value);
int  empty(struct stack* stackPtr);
char pop(struct stack* stackPtr);
char top(struct stack* stackPtr);
void display(struct stack* stackPtr);
int  checkBalance(char exp[]);
int  priority(char ch); //returns the priority of a given operator
int  isOperator(char ch); //check whether it is an operator
char *infixToPostfix(char infix[]); //convert a given infix into postfix
int  isParenthesis(char ch1); //check is it a parenthesis or not
char postfix[SIZE] = {'\0'};

int main() {
    struct stack stk;
    char expression[20] = {'\0'};
    int i = 0;
    initialize(&stk);
    printf("Enter expression: ");
    scanf("%s", &expression);
    if(!checkBalance(expression))
    {
        printf("Parenthesis imbalanced");
        return 0;
    }
    char* postfix = infixToPostfix(expression);
    printf("Postfix expression: %s\n", postfix);
    return 0;
}

char *infixToPostfix(char infix[])
{ 
	int i, j;
	char item;
	char x;
    struct stack s;
	push(&s, '('); 
	strcat(infix,")");  

	i=0;
	j=0;
	item=infix[i]; 

	while(item != '\0')
	{
		if(item == '(')
		{
			push(&s,item);
		}
		else if( isdigit(item) || isalpha(item))
		{
			postfix[j++] = item;
		}
		else if(isOperator(item) == 1)  
		{
			x=pop(&s);
			while(isOperator(x) == 1 && priority(x)>= priority(item))
			{
				postfix[j++] = x;
				x = pop(&s);
			}
			push(&s, x);
			push(&s, item);
            postfix[j++] = ' ';        
		}
		else if(item == ')')      
		{
			x = pop(&s);  
			while(x != '(') 
			{
				postfix[j++] = x;
				x = pop(&s);
			}
		}
		i++;
		item = infix[i];
	}

	postfix[j] = '\0';
    return postfix;
}

int priority(char ch)
{
    if(ch == '^') 
    return 3; 
    else if(ch == '*' || ch == '/') 
    return 2; 
    else if(ch == '+' || ch == '-') 
    return 1; 

    return 0;  
}

int isOperator(char ch)
{
	if(ch == '^' || ch == '*' || ch == '/' || ch == '+' || ch =='-')
	{
		return 1;
	}
	else
	{
	return 0;
	}
}

int isParenthesis(char ch1)
{
    switch (ch1) {  
    case ']':  
    case ')':
    case '}':
    case '{':
    case '[':
    case '(':
        return 1;  
    }  
    return 0;
}


int checkBalance(char exp[]){
    char copy[20] = {'\0'};
    for(int i=0; i<SIZE; i++)
    {
        if(exp[i] == '\0')
        {
            break;
        }
        copy[i] = exp[i];
    }
    char head   = '\0';
    char follow = '\0';
    int ffol = 0;
    int hfol = 0;
    for(int i=0; i<SIZE; i++)
    {
        switch(copy[i])
        {
            case '(':
            case '{':
            case '[':
            if(head == '\0')
            {
                head = copy[i];
                hfol = i;
            }
            else
            {
                ffol = hfol;
                follow = head;
                head = copy[i];
                hfol = i;
            }
            break;

            case ')':
            case '}':
            case ']':
            if(head == '\0')
            {
                return 0;
            }
            else
            {
                ffol = hfol;
                follow = head;
                head = copy[i];
                hfol = i;
                if((follow == '(' && head == ')') || (follow == '{' && head == '}')  || (follow == '[' && head == ']'))
                {
                    copy[ffol] = ' ';
                    copy[hfol] = ' ';
                    ffol = 0;
                    hfol = 0;
                    follow = '\0';
                    head = '\0';
                    i = 0; 
                }
                else
                {
                    return 0;
                }
            }

            break;

            default:
            break;
        }
    }
    if(head == '\0' && follow == '\0')
    {
        return 1;
    }
    return 0;
}


void initialize(struct stack* stackPtr) {
     stackPtr->top = -1;
}

// If the push occurs, 1 is returned. If the
// stack is full and the push can't be done, 0 is
// returned.
int push(struct stack* stackPtr, char value) {

    // Check if the stack is full.
    if (full(stackPtr))
        return 0;

    // Add value to the top of the stack and adjust the value of the top.
    stackPtr->items[stackPtr->top+1] = value;
    (stackPtr->top)++;
    return 1;
}

// Returns true iff the stack pointed to by stackPtr is full.
int full(struct stack* stackPtr) {
    return (stackPtr->top == SIZE - 1);
}

// Returns true iff the stack pointed to by stackPtr is empty.
int empty(struct stack* stackPtr) {
    return (stackPtr->top == -1);
}

// Pre-condition: The stack pointed to by stackPtr is NOT empty.
// Post-condition: The value on the top of the stack is popped and returned.
// Note: If the stack pointed to by stackPtr is empty, -1 is returned.
char pop(struct stack* stackPtr) {

    char retval;

    // Check the case that the stack is empty.
    if (empty(stackPtr))
        return EMPTY;

    // Retrieve the item from the top of the stack, adjust the top and return
    // the item.
    retval = stackPtr->items[stackPtr->top];
    (stackPtr->top)--;
    return retval;
}

// Pre-condition: The stack pointed to by stackPtr is NOT empty.
// Post-condition: The value on the top of the stack is returned.
// Note: If the stack pointed to by stackPtr is empty, -1 is returned.
char top(struct stack* stackPtr) {

    // Take care of the empty case.
    if (empty(stackPtr))
        return EMPTY;

    // Return the desired item.
    return stackPtr->items[stackPtr->top];
}

void display(struct stack* stackPtr) {
    printf("\nPrinting the Current stack...");
    for(int i=0; i<=stackPtr->top; i++)
        printf("%c", stackPtr->items[i]);
}
