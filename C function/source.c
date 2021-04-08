#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

void myprintf(char sentence[], char placeholder[])
{
  bool flag = true;
  char first[50] = {'\0'};
  char second[50] = {'\0'};
  int count = 0;
  for(int i=0; i<strlen(sentence); i++)
  {
    if(flag)
    {
      if(sentence[i] == '%')
      {
        flag = false;
        i += 1;
      }
      else
      {
        first[i] = sentence[i];
      }
    }
    else
    {
      second[count] = sentence[i];
      count++;
    }
  }
  write(0, first, strlen(first));
  write(1, placeholder, strlen(placeholder));
  write(2, second, strlen(second));
}

int main()
{
  char* food = "cookies";
  myprintf("I enjoy %s with my tea.\n", food);
  return 0;
}