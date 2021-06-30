#if !defined(VIRTUAL_ANT_H)
#define VIRTUAL_ANT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include <limits.h>
#define LEN 100

/**
 * @brief X cords fill
 * 
 */
void xFill(int, int, int);

/**
 * @brief Y cords fill
 * 
 */
void yFill(int, int, int);

/**
 * @brief Resets itch variables
 * 
 */
void itchReset();

/**
 * @brief Drives the code for input and output from file and stdout
 * 
 */
void driver();

#endif // VIRTUAL_ANT_H

