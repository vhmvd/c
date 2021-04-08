#include <stdio.h>
#include <string.h>

char  line[256];
char* name = NULL;
char* building = NULL;
char* date = NULL;
char* time = NULL;
int   i = 0;
char* array[25] = {NULL};

int main()
{
  printf("Enter line: ");
  
  fgets(line,256,stdin);
  char *p = strtok(line," ");
  while(p != NULL)
  {
    array[i++] = p;
    p = strtok(NULL, " ");
  }
  array[--i][strlen(array[i])-1] = '\0';
  i = 0;
  while(array[i] != NULL)
  {
    if(strlen(array[i])>=3)
      for(int j=0; j< strlen(array[i]); j++)
      {
        if((int)array[i][0] >= 65 && (int)array[i][0] <= 90)
        {
          if((int)array[i][1] >= 97 && (int)array[i][1] <= 122)
          {
            name = array[i];
          }
          else if((int)array[i][1] >= 65 && (int)array[i][1] <= 90 && strlen(array[i]) >= 6)
          {
            building = array[i];
          }
        }
        else if(array[i][2] == '-')
        {
          date = array[i];
        }
        else if((array[i][1] == 'a' || array[i][1] == 'p') && array[i][2] == 'm')
        {
          time = array[i];
        }
      }
    i++;
  }
  printf("Appointment with ");
  if(name == NULL)
  {
    printf("<not provided> ");
  }
  else
  {
    printf("%s ", name);
  }
  printf("is on ");
  if(date == NULL)
  {
    printf("<not provided> ");
  }
  else
  {
    printf("%s ", date);
  }
  printf("at ");
  if(time == NULL)
  {
    printf("<not provided> ");
  }
  else
  {
    printf("%s ", time);
  }
  printf("in ");
  if(building == NULL)
  {
    printf("<not provided>\n");
  }
  else
  {
    printf("%s\n", building);
  }
}