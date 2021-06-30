#if !defined(SCANNER_H_)
#define SCANNER_H_

#include "stack.h"
#include <string.h>
#define LENGTH 100

coordinates currentPos, exitPos;
char  numOfCols[LENGTH],
      numOfRows[LENGTH],
      mazeStorage[LENGTH][LENGTH];

int t,
    n;

typedef enum
{
  MVF,
  MVB,
  MVL,
  CWL,
  MWR,
  CWR,
  CWF,
  CWB,
  PUSH,
  POP,
  PEEK,
  CLEAR,
  BJPI,
  CJPI
} inst;

inst intelligence[LENGTH];

void readMaze();
void readInst();

#endif // SCANNER_H_
