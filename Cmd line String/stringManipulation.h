#if !defined(STRING_MANIPULATION_H)
#define STRING_MANIPULATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* stringSubtraction(char*, char*);
void performOperations(char*, int, char**);
void argumentCountCheck(int);
void argumentOperatorCheck(int, char**);
void operandAtStringPlaceCheck(int, char**);
void usagePrintAndExit();
void invalidOperandPrintAndExit();
void operandAtStringPlaceCheckAndExit();
void validityChecks(int, char**);
int precedenceIndex(int, char**);
int succeedingString(int, int, char**);
char operatorType(int, char**);
int empty(int, char**);

void performOperations(char* solution, int argc, char** argv)
{
  int indexOfOperator;
  int preceedingOperandIndex;
  int succeedingOperandIndex;
  char operator = '\0';
  validityChecks(argc, argv);
  while(empty(argc, argv) == 1)
  {
    int i;
    indexOfOperator = precedenceIndex(argc, argv);
    operator = operatorType(indexOfOperator, argv);
    preceedingOperandIndex = indexOfOperator - 1;
    succeedingOperandIndex = succeedingString(indexOfOperator, argc, argv);
    
    switch(operator)
    {
    case '*':
      for(i=0; i<atoi(argv[succeedingOperandIndex]); i++)
      {
        strcat(solution, argv[preceedingOperandIndex]);
      }
      strcpy(argv[indexOfOperator], "\0");
      strcpy(argv[preceedingOperandIndex], "\0");
      strcpy(argv[succeedingOperandIndex], "\0");
      break;
    case '+':
      strcat(solution, argv[preceedingOperandIndex]);
      strcat(solution, argv[succeedingOperandIndex]);
      strcpy(argv[indexOfOperator], "\0");
      strcpy(argv[preceedingOperandIndex], "\0");
      strcpy(argv[succeedingOperandIndex], "\0");
      break;
    case '-':
      if(!strcmp(solution, "\0"))
      {
        strcpy(solution, stringSubtraction(argv[preceedingOperandIndex], argv[succeedingOperandIndex]));
        strcpy(argv[indexOfOperator], "\0");
        strcpy(argv[preceedingOperandIndex], "\0");
        strcpy(argv[succeedingOperandIndex], "\0");
      }
      else
      {
        strcpy(solution, stringSubtraction(solution, argv[succeedingOperandIndex]));
        strcpy(argv[indexOfOperator], "\0");
        strcpy(argv[preceedingOperandIndex], "\0");
        strcpy(argv[succeedingOperandIndex], "\0");
      }
      break;
    default:
      break;
    }
  }
}

int succeedingString(int index, int argc, char** argv)
{
  int i;
  for(i=index; i<argc; i += 2)
  {
    if(strcmp(argv[i+1], "\0"))
    {
      return i+1;
    }
  }
  exit(4);
}

int empty(int argc, char** argv)
{
  int i;
  for(i=1; i<argc; i++)
  {
    if(!strcmp(argv[i], "+") || !strcmp(argv[i], "*") || !strcmp(argv[i], "-"))
    {
      return 1;
    }
  }
  return 0;
}

char operatorType(int index, char** argv)
{
  if(!strcmp(argv[index], "*"))
    return '*';
  if(!strcmp(argv[index], "-"))
    return '-';
  if(!strcmp(argv[index], "+"))
    return '+';
  return '+';
}

int precedenceIndex(int argc,char** argv)
{
  int i;
  for(i=1; i<argc; i++)
  {
    if(!strcmp(argv[i], "*"))
      return i;
  }
  for(i=1; i<argc; i++)
  {
    if(!strcmp(argv[i], "-") || !strcmp(argv[i], "+"))
      return i;
  }
  return -1;
}

void validityChecks(int argc, char** argv)
{
  argumentCountCheck(argc);
  argumentOperatorCheck(argc, argv);
  operandAtStringPlaceCheck(argc, argv);
}

void operandAtStringPlaceCheck(int argc, char** argv)
{
  int i;
  for(i=1; i<argc; i=i+2)
  {
    if(!strcmp(argv[i], "*") || !strcmp(argv[i], "+") || !strcmp(argv[i], "-"))
      operandAtStringPlaceCheckAndExit();
    else
      continue;
  }
}

void argumentOperatorCheck(int argc, char** argv)
{
  int i;
  for(i=2; i<argc; i=i+2)
  {
    if(!strcmp(argv[i], "*") || !strcmp(argv[i], "+") || !strcmp(argv[i], "-"))
      continue;
    else
      invalidOperandPrintAndExit();
  }
}

void operandAtStringPlaceCheckAndExit()
{
  printf("\nOperand used at string place.\nUsage\n./<Program name> <String> + <String>\n");
  printf("./<Program name> <String> - <String>\n");
  printf("./<Program name> <String> * <Constant>\n");
  printf("Example run\n./main Hello + you - loy\nOutput: Hlo\n");
  exit(3);
}

void invalidOperandPrintAndExit()
{
  printf("\nInvalid operands used.\nAllowed operands are \" * \", \" + \" and \" - \" only.\n");
  exit(2);
}

void usagePrintAndExit()
{
  printf("\nInvalid number of arguments provided.\nUsage\n./<Program name> <String> + <String>\n");
  printf("./<Program name> <String> - <String>\n");
  printf("./<Program name> <String> * <Constant>\n");
  printf("Example run\n./main Hello + you - loy\nOutput: Hlo\n");
  exit(1);
}

void argumentCountCheck(int args)
{
  if(args < 4 || args % 2 != 0)
  {
    usagePrintAndExit();
  }
}

char *stringSubtraction(char *string, char *subString)
{
  char *temp1, *temp2, *temp3;
  if ((temp2 = temp3 = strstr(string, subString)) != NULL) 
  {
    size_t length = strlen(subString);
    while ((temp3 = strstr(temp1 = temp3 + length, subString)) != NULL) 
    {
      while (temp1 < temp3)
        *temp2++ = *temp1++;
    }
    while ((*temp2++ = *temp1++) != '\0')
      continue;
  }
  return string;
}


#endif