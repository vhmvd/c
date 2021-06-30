#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

FILE *fileHandle;
long nRows, nCols;

/**
 * @brief Reads the maze file data
 * 
 * @return int 
 */
void readMaze()
{
  char  identifier[LENGTH],
        eq,
        co,
        un,
        c;
  int i = 0,
      j = 0;

  if ((fileHandle = fopen("input/maze.in", "r")) == NULL)
  {
    perror("This file can't be opened.");
  }

  fscanf(fileHandle, "%s %c %d %c %d", identifier, &eq, &currentPos.x, &co, &currentPos.y);
  printf("%s %c %d%c%d", identifier, eq, currentPos.x, co, currentPos.y);

  identifier == '\0';
  printf("\n");

  fscanf(fileHandle, "%s %c %d %c %d", identifier, &eq, &exitPos.x, &co, &exitPos.y);
  printf("%s %c %d%c%d", identifier, eq, exitPos.x, co, exitPos.y);

  printf("\n");

  fscanf(fileHandle, "%s %c %s", identifier, &eq, numOfCols);
  printf("%s %c %s", identifier, eq, numOfCols);

  printf("\n");

  fscanf(fileHandle, "%s %c %s", identifier, &eq, numOfRows);
  printf("%s %c %s", identifier, eq, numOfRows);

  c = fgetc(fileHandle);
  nRows = atoi(numOfRows);
  nCols = atoi(numOfCols);

  while (c == ' ' || c == '\n' || c == '|' || c == '-')
  {
    if (c != '\n')
    {
      mazeStorage[i][j] = c;
      j++;
      if (j > nCols - 1)
      {
        i++;
        j = 0;
      }
    }
    c = fgetc(fileHandle);
    printf("%c", c);
  }
  printf("\n");
  for (i = 0; i < nRows; i++)
  {
    for (j = 0; j < nCols; j++)
    {
      printf("%c", mazeStorage[i][j]);
    }
    printf("\n");
  }
}

/**
 * @brief Reads the instruction file
 * 
 */
void readInst()
{
  printf("Hello world");
  t = 0;
  n = 0;
  int i;
  char word[10];
  FILE *inFileInst;

  if ((inFileInst = fopen("input/inst.in", "r")) == NULL)
  { 
    perror("This file can't be opened.");
  }
  fscanf(inFileInst, "%s", word);
  printf("%s", word);
  fscanf(inFileInst, "%d", &n);
  fscanf(inFileInst, "%d", &t);
  i = 0;
  while (!feof(inFileInst))
  {
    fscanf(inFileInst, "%s", word);
    printf("\n%s", word);

    if (strcmp(word, "MVF") == 0)
    {
      intelligence[i] = MVF;
    }
    else if (strcmp(word, "MVB") == 0)
    {
      intelligence[i] = MVB;
    }
    else if (strcmp(word, "MVL") == 0)
    {
      intelligence[i] = MVL;
    }

    else if (strcmp(word, "CWL") == 0)
    {
      intelligence[i] = CWL;
    }
    else if (strcmp(word, "MWR") == 0)
    {
      intelligence[i] = MWR;
    }
    else if (strcmp(word, "CWR") == 0)
    {
      intelligence[i] = CWR;
    }
    else if (strcmp(word, "CWF") == 0)
    {
      intelligence[i] = CWF;
    }
    else if (strcmp(word, "CWB") == 0)
    {
      intelligence[i] = CWB;
    }
    else if (strcmp(word, "PUSH") == 0)
    {
      intelligence[i] = PUSH;
    }
    else if (strcmp(word, "POP") == 0)
    {
      intelligence[i] = POP;
    }
    else if (strcmp(word, "PEEK") == 0)
    {
      intelligence[i] = PEEK;
    }
    else if (strcmp(word, "CLEAR") == 0)
    {
      intelligence[i] = CLEAR;
    }
    else if (strcmp(word, "BJPI") == 0)
    {
      intelligence[i] = BJPI;
    }
    else if (strcmp(word, "CJPI") == 0)
    {
      intelligence[i] = CJPI;
    }
    i++;
  }
}
