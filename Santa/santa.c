/**
 * @file santa.c
 * @author your name (you@domain.com)
 * @date 2020-12-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define W_LENGTH 20

/* Function prototypes */
int   number_of_people        (FILE*);
int   number_of_nice_people   (FILE*);
int   number_of_naughty_people(FILE*);
int   number_of_neutral_people(FILE*);
int   calculate_sleighs_needed(FILE*);
int   calculate_time_needed   (FILE*);
float average_behaviourscore  (FILE*);
float total_weight            (FILE*);
void  furthest_south_child    (FILE*, char*, char*);
void  largest_gathering       (FILE*, double*, double*);
void  naughtiest_person       (FILE*, double*, double*);
/**
 * @brief Main program to drive
 * 
 * @return int 0 on successful execution
 */
int main(void)
{
  FILE* santaFile = fopen("satanslist.txt", "r");
  printf("Total number of people: %d\n", number_of_people(santaFile));
  fclose(santaFile);

  santaFile = fopen("satanslist.txt", "r");
  printf("Number of nice people: %d\n", number_of_nice_people(santaFile));
  fclose(santaFile);

  santaFile = fopen("satanslist.txt", "r");
  printf("Number of neutral people: %d\n", number_of_neutral_people(santaFile));
  fclose(santaFile);

  santaFile = fopen("satanslist.txt", "r");
  printf("Number of naughty people: %d\n", number_of_naughty_people(santaFile));
  fclose(santaFile);

  santaFile = fopen("satanslist.txt", "r");
  printf("Average behaviour score: %f\n", average_behaviourscore(santaFile));
  fclose(santaFile);

  santaFile = fopen("satanslist.txt", "r");
  printf("Total weight of gifts: %f\n", total_weight(santaFile));
  fclose(santaFile);

  santaFile = fopen("satanslist.txt", "r");
  double  longitude = 0.0,
          latitude  = 0.0;
  naughtiest_person(santaFile, &longitude, &latitude);
  printf("\nNaughtiest person live at\nLongitude: %.15lf\nLatitude : %.15lf\n\n", latitude, longitude);
  fclose(santaFile);

  santaFile = fopen("satanslist.txt", "r");
  printf("Sleighs needed: %d\n", calculate_sleighs_needed(santaFile));
  fclose(santaFile);

  santaFile = fopen("satanslist.txt", "r");
  printf("Time required to launch all sleighs: %dmin\n", calculate_time_needed(santaFile));
  fclose(santaFile);

  santaFile = fopen("satanslist.txt", "r");
  longitude = 0.0;
  latitude  = 0.0;
  largest_gathering(santaFile, &latitude, &longitude);
  printf("\nMost people live at\nLongitude: %.15lf\nLatitude : %.15lf\n\n", latitude, longitude);
  fclose(santaFile);

  santaFile = fopen("satanslist.txt", "r");
  char name[W_LENGTH],
        sname[W_LENGTH];
  furthest_south_child(santaFile, name, sname);
  printf("\nFurthest child in South is\nSurname: %s\nName: %s\n\n", sname, name);
  fclose(santaFile);

  return 0;
}

/**
 * @brief Modifies a referenced char* with name and surname of the most farthest
 *        living child in the south.
 * 
 * @param inFile File descriptor
 * @param name   Name
 * @param sname  Surname
 */
void furthest_south_child(FILE* inFile, char* name, char* sname)
{
  char    surname[W_LENGTH]    = {'\0'},
          firstname[W_LENGTH]  = {'\0'};
  int     behaviourScore = 0;
  double  latitude       = 0.0,
          longitude      = 0.0,
          southLat       = 90.0;
  float   giftWeight     = 0.0;
  while(fscanf(inFile, "%[^,],%[^,],%d,%lf,%lf,%f ", surname, firstname, &behaviourScore, &latitude, &longitude, &giftWeight) != EOF)
  {
    if(latitude < southLat)
    {
      southLat = latitude;
      strncpy(name, firstname, W_LENGTH);
      strncpy(sname, surname, W_LENGTH);
    }
  }
}

/**
 * @brief Counts the number of neutral people. Where neutral people have a 
 *        behaviourscore equal to zero
 * 
 * @param inFile File descriptor
 * @return int 
 */
int number_of_neutral_people(FILE* inFile)
{
  char    surname[W_LENGTH]    = {'\0'},
          firstname[W_LENGTH]  = {'\0'};
  int     behaviourScore = 0,
          neutral        = 0;
  double  latitude       = 0.0,
          longitude      = 0.0;
  float   giftWeight     = 0.0;
  while(fscanf(inFile, "%[^,],%[^,],%d,%lf,%lf,%f ", surname, firstname, &behaviourScore, &latitude, &longitude, &giftWeight) != EOF)
  {
    if(behaviourScore == 0)
      neutral++;
  }
  return neutral;
}

/**
 * @brief Modifies a referenced double with longitude and latitude most people that live there
 * 
 * @param inFile File descriptor
 * @param lon    Longitude
 * @param lat    Latitude
 */
void largest_gathering(FILE* inFile, double* lon, double* lat)
{
  FILE* santaFile = fopen("satanslist.txt", "r");
  int totalPeople = number_of_people(santaFile),
      peopleCount = 0,
      mostPeople  = 0,
      i           = 0,
      j           = 0;
  fclose(santaFile);

  char    surname[W_LENGTH]    = {'\0'},
          firstname[W_LENGTH]  = {'\0'};
  int     behaviourScore = 0,
          count          = 0;
  double  latitude       = 0.0,
          longitude      = 0.0;
  float   giftWeight     = 0.0;
  double* longArr        = (double*) malloc(totalPeople * sizeof(double));
  double* latArr         = (double*) malloc(totalPeople * sizeof(double));
  while(fscanf(inFile, "%[^,],%[^,],%d,%lf,%lf,%f ", surname, firstname, &behaviourScore, &latitude, &longitude, &giftWeight) != EOF)
  {
    longArr[count] = longitude;
    latArr [count] = latitude;
    count++;
  }
  for(i=0; i<totalPeople; i++)
  {
    peopleCount = 0;
    for(j=i+1; j<totalPeople; j++)
    {
      if(longArr[i] == longArr[j] && latArr[i] == latArr[j])
        peopleCount++;
    }
    if(peopleCount > mostPeople)
    {
      *lon = longArr[i];
      *lat = latArr [i];
    }
  }
  free(longArr);
  free(latArr);
}

/**
 * @brief Returns how long will it take to launch the required number of sleighs
 * 
 * @param inFile File descriptor
 * @return int Time
 */
int calculate_time_needed(FILE* inFile)
{
  int   sleighsNum = calculate_sleighs_needed(inFile);
  float time       = sleighsNum * 1.5;
  return (int)time;
}

/**
 * @brief Each sleigh can only carry a maximum of 1500Kg. 
 * 
 * @param inFile File descriptor
 * @return int   Returns the total number of sleighs Santa will have 
 *               to use to deliver gifts this Christmas
 */
int calculate_sleighs_needed(FILE* inFile)
{
  char    surname[W_LENGTH]    = {'\0'},
          firstname[W_LENGTH]  = {'\0'};
  int     behaviourScore = 0;
  double  latitude       = 0.0,
          longitude      = 0.0;
  float   giftWeight     = 0.0,
          totalWeight    = 0.0;
  while(fscanf(inFile, "%[^,],%[^,],%d,%lf,%lf,%f ", surname, firstname, &behaviourScore, &latitude, &longitude, &giftWeight) != EOF)
  {
    totalWeight += giftWeight;
  }
  int intWeight = (int)totalWeight/1500;
  return intWeight + 1;
}

/**
 * @brief Return the lat and long of the location of the naughtiest person on
 *        the list
 * 
 * @param inFile File descriptor
 * @param lat    Latitude
 * @param lon    Longitude
 */
void naughtiest_person(FILE* inFile, double* lat, double* lon)
{
  char    surname[W_LENGTH]    = {'\0'},
          firstname[W_LENGTH]  = {'\0'};
  int     behaviourScore = 0,
          baddest        = 10;
  double  latitude       = 0.0,
          longitude      = 0.0;
  float   giftWeight     = 0.0;
  while(fscanf(inFile, "%[^,],%[^,],%d,%lf,%lf,%f ", surname, firstname, &behaviourScore, &latitude, &longitude, &giftWeight) != EOF)
  {
    if(behaviourScore < baddest)
    {
      baddest = behaviourScore;
      *lat = latitude;
      *lon = longitude;
    }
  }
}

/**
 * @brief  Return the average behaviourscore for all entries in the file
 * 
 * @param inFile File descriptor
 * @return float 
 */
float average_behaviourscore(FILE* inFile)
{
  char    surname[W_LENGTH]    = {'\0'},
          firstname[W_LENGTH]  = {'\0'};
  int     behaviourScore = 0,
          lineNum        = 0;
  double  latitude       = 0.0,
          longitude      = 0.0;
  float   giftWeight     = 0.0,
          totalBehaviour = 0.0;
  while(fscanf(inFile, "%[^,],%[^,],%d,%lf,%lf,%f ", surname, firstname, &behaviourScore, &latitude, &longitude, &giftWeight) != EOF)
  {
    totalBehaviour += behaviourScore;
    lineNum++;
  }
  return totalBehaviour/lineNum;
}

/**
 * @brief Return the total weight of gifts Santa has to deliver
 * 
 * @param inFile File descriptor
 * @return float 
 */
float total_weight(FILE* inFile)
{
  char    surname[W_LENGTH]    = {'\0'},
          firstname[W_LENGTH]  = {'\0'};
  int     behaviourScore = 0;
  double  latitude       = 0.0,
          longitude      = 0.0;
  float   giftWeight     = 0.0,
          total_weight   = 0.0;
  while(fscanf(inFile, "%[^,],%[^,],%d,%lf,%lf,%f ", surname, firstname, &behaviourScore, &latitude, &longitude, &giftWeight) != EOF)
  {
    if(behaviourScore < 0)
      total_weight += giftWeight;
  }
  return total_weight;
}

/**
 * @brief  Counts the number of nice people. Where nice people have a
 *         behaviourscore greater than zero
 * 
 * @param inFile File descriptor
 * @return int 
 */
int number_of_nice_people(FILE* inFile)
{
  char    surname[W_LENGTH]    = {'\0'},
          firstname[W_LENGTH]  = {'\0'};
  int     behaviourScore = 0,
          nice           = 0;
  double  latitude       = 0.0,
          longitude      = 0.0;
  float   giftWeight     = 0.0;
  while(fscanf(inFile, "%[^,],%[^,],%d,%lf,%lf,%f ", surname, firstname, &behaviourScore, &latitude, &longitude, &giftWeight) != EOF)
  {
    if(behaviourScore > 0)
      nice++;
  }
  return nice;
}

/**
 * @brief  Counts the number of naughty people. Where naughty people have a 
 *         behaviourscore less than zero
 * 
 * @param inFile File descriptor
 * @return int 
 */
int number_of_naughty_people(FILE* inFile)
{
  char    surname[W_LENGTH]    = {'\0'},
          firstname[W_LENGTH]  = {'\0'};
  int     behaviourScore = 0,
          naughty        = 0;
  double  latitude       = 0.0,
          longitude      = 0.0;
  float   giftWeight     = 0.0;
  while(fscanf(inFile, "%[^,],%[^,],%d,%lf,%lf,%f ", surname, firstname, &behaviourScore, &latitude, &longitude, &giftWeight) != EOF)
  {
    if(behaviourScore < 0)
      naughty++;
  }
  return naughty;
}



/**
 * @brief Counts the lines in the files
 * 
 * @param inFile File descriptor
 * @return int Number of lines
 */
int number_of_people(FILE* inFile)
{
  char    surname[W_LENGTH]    = {'\0'},
          firstname[W_LENGTH]  = {'\0'};
  int     behaviourScore = 0,
          lineNum        = 0;
  double  latitude       = 0.0,
          longitude      = 0.0;
  float   giftWeight     = 0.0;
  while(fscanf(inFile, "%[^,],%[^,],%d,%lf,%lf,%f ", surname, firstname, &behaviourScore, &latitude, &longitude, &giftWeight) != EOF)
  {
    lineNum++;
  }
  return lineNum;
}