#include "ant.h"

/**
 * @brief MAX_ENERGY variable to set Micheal's energy level
 * 
 */
int MAX_ENERGY = 100;

/**
 * @brief Variables to store number of itches
 * 
 */
int itch_R,
    itch_L,
    itch_F,
    itch_B;

/**
 * @brief Number of rows and cols
 * 
 */
long  nRows,
      nCols;

/**
 * @brief Fills the x cords in loop
 * 
 * @param p1
 * @param p2 
 * @param y 
 */
void xFill(int p1, int p2, int y)
{
  int max = p2,
      min = p1,
      i;
  if (p1 > p2)
  {
    max = p1;
    min = p2;
  }
  for (i = min; i < max; i++)
  {
    mazeStorage[i][y] = 'v';
  }
}

/**
 * @brief Fills the y cords in loop
 * 
 * @param p1 
 * @param p2 
 * @param x 
 */
void yFill(int p1, int p2, int x)
{
  int max = p2,
      min = p1,
      i;
  if (p1 > p2)
  {
    max = p1;
    min = p2;
  }
  for (i = min; i < max; i++)
  {
    mazeStorage[x][i] = 'v';
  }
}

/**
 * @brief Resets the number of itches by assigning 0
 * 
 */
void itchReset()
{
  itch_R = 0;
  itch_L = 0;
  itch_F = 0;
  itch_B = 0;
}

/**
 * @brief Prints to screen and to file after reading the maze
 * 
 */
void driver()
{
  FILE *outFile;
  if ((outFile = fopen("output/maze.out", "w")) == NULL)
  {
    printf("This file can't be opened.");
  }
  readMaze();
  char word[10];
  inst action;
  int counter = 0,
      distance = 0,
      i = 0,
      j = 0,
      d = 0,
      twitch = 0,
      moved = 0,
      energy = MAX_ENERGY;

  printf("Start Position X = %d", currentPos.x);
  printf("\n Start Position Y = %d", currentPos.y);
  printf("\n Exit Position X = %d", exitPos.x);
  printf("\n Exit Position Y = %d\n", exitPos.y);

  readInst();

  printf("\nThis is t = %d\n", t);
  printf("This is n = %d", n);

  i = 0;
  j = 0;
  while (((currentPos.x != exitPos.x) || (currentPos.y != exitPos.y)) && (energy > 0) && j < t)
  {
    printf("\nPOSITION X = %d", currentPos.x);
    printf("\nPosition Y = %d\n", currentPos.y);
    action = intelligence[i];
    switch (action)
    {
    case MVF:
      if (itch_F && energy >= 3)
      {
        printf("FORWARD\n");
        fprintf(outFile, "MVF\n");
        mazeStorage[currentPos.x][currentPos.y] = 'v';
        currentPos.x += 1;
        energy -= 3;
        printf("%d", energy);
        itchReset();
        moved = 1;
        counter++;
      }
      break;

    case MVB:
      if (itch_B && energy >= 3)
      {
        printf("BACK\n");
        fprintf(outFile, "MVF\n");
        mazeStorage[currentPos.x][currentPos.y] = 'v';
        currentPos.x -= 1;
        energy -= 3;
        itchReset();
        moved = 1;
        counter++;
      }
      break;
    case MVL:
      if (itch_L && energy >= 3)
      {
        printf("LEFT\n");
        fprintf(outFile, "MVL\n");
        mazeStorage[currentPos.x][currentPos.y] = 'v';
        currentPos.y -= 1;
        energy -= 3;
        itchReset();
        moved = 1;
        counter++;
      }
      break;
    case MWR:
      if (itch_R && energy >= 3)
      {
        printf("RIGHT\n");
        fprintf(outFile, "MWR\n");
        mazeStorage[currentPos.x][currentPos.y] = 'v';
        currentPos.y += 1;
        energy -= 3;
        itchReset();
        moved = 1;
        counter++;
      }
      break;
    case CWL:
      if (energy >= 1)
      {
        printf("CHECK LEFT\n");
        fprintf(outFile, "CWL\n");
        d = currentPos.y - 1;
        distance = 0;
        while (mazeStorage[currentPos.x][d] == ' ')
        {
          d--;
          distance++;
          itch_L = 1;
        }
        moved = 0;
        energy--;
        counter++;
        break;
      }
    case CWR:
      if (energy >= 1)
      {
        printf("CHECK RIGHT\n");
        fprintf(outFile, "CWR\n");
        d = currentPos.y + 1;
        distance = 0;
        while (mazeStorage[currentPos.x][d] == ' ')
        {
          d++;
          distance++;
          itch_R = 1;
        }
        moved = 0;
        energy--;
        counter++;
        break;
      }
    case CWF:
      if (energy >= 1)
      {
        printf("CHECK FORWARD\n");
        fprintf(outFile, "CWF\n");
        d = currentPos.x + 1;
        distance = 0;
        while (mazeStorage[d][currentPos.y] == ' ')
        {
          d++;
          distance++;
          itch_F = 1;
        }
        moved = 0;
        energy--;
        counter++;
        break;
      }
    case CWB:
      if (energy >= 1)
      {
        printf("CHECK BACK\n");
        fprintf(outFile, "CWB\n");
        d = currentPos.x - 1;
        distance = 0;
        while (mazeStorage[d][currentPos.y] == ' ')
        {
          d--;
          distance++;
          itch_B = 1;
        }
        moved = 0;
        energy--;
        counter++;
        break;
      }
    case PUSH:
      if (energy >= 4)
      {

        if (itch_R + itch_L + itch_B + itch_F > 1)
        {
          push(currentPos);
          energy -= 4;
          counter++;
          fprintf(outFile, "PUSH\n");
          printf("PUSH\n");
        }
        break;
      }
    case POP:
      if (energy >= 4)
      {
        if (moved == 0)
        {
          printf("POP\n");
          fprintf(outFile, "POP\n");
          currentPos = pop();
          energy -= 4;
          counter++;
        }
        break;
      }
    case PEEK:
      if (energy >= 2)
      {
        printf("PEEK\n");
        fprintf(outFile, "PEEK\n");
        energy -= 2;
        counter++;
        break;
      }
    case CLEAR:
      if (energy >= 2)
      {
        printf("CLEAR\n");
        fprintf(outFile, "CLEAR\n");
        energy -= 2;
        counter++;
        break;
      }
    case BJPI:
      if (energy >= 5)
      {

        if (itch_R == 1)
        {
          currentPos.y += distance;
          energy -= 5;
          counter++;
          printf("BOLD JUMP\n");
          fprintf(outFile, "BOLD JUMP\n");
        }
        else if (itch_L == 1)
        {
          currentPos.y -= distance;
          energy -= 5;
          counter++;
          printf("BOLD JUMP\n");
          fprintf(outFile, "BOLD JUMP\n");
        }
        else if (itch_B == 1)
        {
          currentPos.x -= distance;
          energy -= 5;
          counter++;
          printf("BOLD JUMP\n");
          fprintf(outFile, "BOLD JUMP\n");
        }
        else if (itch_F == 1)
        {
          currentPos.x += distance;
          energy -= 5;
          counter++;
          printf("BOLD JUMP\n");
          fprintf(outFile, "BOLD JUMP\n");
        }
        break;
      }
    case CJPI:
      if (energy >= 3)
      {

        if (itch_R == 1 && distance >= 2)
        {
          currentPos.y += 2;
          energy -= 3;
          counter++;
          printf("CAUTIOUS JUMP\n");
          fprintf(outFile, "CAUTIOUS JUMP\n");
        }
        else if (itch_L == 1 && distance >= 2)
        {
          currentPos.y -= 2;
          energy -= 3;
          counter++;
          printf("CAUTIOUS JUMP\n");
          fprintf(outFile, "CAUTIOUS JUMP\n");
        }
        else if (itch_B == 1 && distance >= 2)
        {
          currentPos.x -= distance;
          energy -= 3;
          counter++;
          printf("CAUTIOUS JUMP\n");
          fprintf(outFile, "CAUTIOUS JUMP\n");
        }
        else if (itch_F == 1 && distance >= 2)
        {
          currentPos.x += distance;
          energy -= 3;
          counter++;
          printf("CAUTIOUS JUMP\n");
          fprintf(outFile, "CAUTIOUS JUMP\n");
        }
        break;
      }
    }

    i++;
    if (i == n)
    {
      i = 0;
      j++;
    }
    printf("i = %d", i);
    printf("\nj = %d", j);
    printf("\nEnergy right now equals to %d", energy);
  }

  if (energy <= 0)
  {
    printf("\nMichael ran out of energy.");
    fprintf(outFile, "\nMichael ran out of energy.");
  }
  if (currentPos.x == exitPos.x && currentPos.y == exitPos.y)
  {
    printf("\n\nMichael made it out!\nFinal Position = %d %d", currentPos.x, currentPos.y);
    printf("\nExit Position X = %d", exitPos.x);
    fprintf(outFile, "\nExit Position X = %d", exitPos.x);
    printf("\nExit Position Y = %d", exitPos.y);
    fprintf(outFile, "\nExit Position Y = %d", exitPos.y);
    fprintf(outFile, "\n\nMichael made it out!\nFinal Position = %d %d", currentPos.x, currentPos.y);
  }

  distance = 0;
  for (i = 0; i < nRows; i++)
  {
    for (j = 0; j < nCols; j++)
    {
      if (mazeStorage[i][j] == 'v')
        distance++;
    }
  }

  printf("\n\nThe distance travelled is %d", distance);
  fprintf(outFile, "\n\nThe distance travelled is %d", distance);
  printf("\nEnergy spent is %d", MAX_ENERGY - energy);
  fprintf(outFile, "\nEnergy spent is %d", MAX_ENERGY - energy);
  printf("\nThe amount of moves made was %d", counter);
  fprintf(outFile, "\nThe amount of moves made was %d", counter);
}
