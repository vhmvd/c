#include <stdio.h>

#define TRUE 1
#define EMPTY 0
#define LONG_MONTH 31
#define SHORT_MONTH 30
#define LEAP 29
#define NOT_LEAP 28
#define DAYS_IN_WEEK 7

/* Functions declerations*/
int calculateDay(int);
int checkLeapYear(int);
void printCalendar(int, int);
void printCalendarInFile(int, int);

int daysInMonth[] = {EMPTY, LONG_MONTH, NOT_LEAP, LONG_MONTH, SHORT_MONTH, LONG_MONTH, SHORT_MONTH,
                     LONG_MONTH, LONG_MONTH, SHORT_MONTH, LONG_MONTH, SHORT_MONTH, LONG_MONTH};

char *monthsName[] =
    {
        " ",
        "\n\n\nJanuary",
        "\n\n\nFebruary",
        "\n\n\nMarch",
        "\n\n\nApril",
        "\n\n\nMay",
        "\n\n\nJune",
        "\n\n\nJuly",
        "\n\n\nAugust",
        "\n\n\nSeptember",
        "\n\n\nOctober",
        "\n\n\nNovember",
        "\n\n\nDecember"};

/*Find first day of the year*/
int calculateDay(int year)
{
  int day;
  int day1, day2, day3;

  day1 = (year - 1.) / 4.0;
  day2 = (year - 1.) / 100.;
  day3 = (year - 1.) / 400.;
  day = (year + day1 - day2 + day3) % DAYS_IN_WEEK;
  return day;
}

/*determine leap year or not*/
int checkLeapYear(int year)
{
  if (((year % 4 == EMPTY) && (year % 100 != EMPTY)) || (year % 400 == EMPTY))
  {
    daysInMonth[2] = LEAP;
    return TRUE;
  }
  else
  {
    daysInMonth[2] = NOT_LEAP;
    return EMPTY;
  }
}

/*display calendar*/
void printCalendar(int year, int day)
{
  int month, days;
  for (month = 1; month <= 12; month++)
  {
    printf("%s", monthsName[month]);
    printf("\n\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n");

    /* Correct the position for the first date*/
    for (days = 1; days <= 1 + day * 5; days++)
      printf(" ");

    /* Print all the dates for one month*/
    for (days = 1; days <= daysInMonth[month]; days++)
    {
      printf("%2d", days);

      /* Is day before Sat? Else start next line Sun.*/
      if ((days + day) % DAYS_IN_WEEK > 0)
        printf("   ");
      else
        printf("\n ");
    }
    /* Set position for next month*/
    day = (day + daysInMonth[month]) % DAYS_IN_WEEK;
  }
}

void printCalendarInFile(int year, int day)
{
  int month, days;
  freopen("Calendar.txt", "w", stdout);
  for (month = 1; month <= 12; month++)
  {
    printf("%s", monthsName[month]);
    printf("\n\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n");

    /* Correct the position for the first date*/
    for (days = 1; days <= 1 + day * 5; days++)
      printf(" ");

    /* Print all the dates for one month*/
    for (days = 1; days <= daysInMonth[month]; days++)
    {
      printf("%2d", days);

      /* Is day before Sat? Else start next line Sun.*/
      if ((days + day) % DAYS_IN_WEEK > 0)
        printf("   ");
      else
        printf("\n ");
    }
    /* Set position for next month*/
    day = (day + daysInMonth[month]) % DAYS_IN_WEEK;
  }
}

int main()
{
  int yearInput, day;
  char option = ' ';
  do
  {
    printf("\nNOTE: Valid year ranges from 1900 to 2100 and cannot be negative\n\n");
    printf("Please enter a year (yyyy format): ");
    scanf("%d", &yearInput);
  } while (yearInput < 1900 || yearInput > 2100);
  printf("\n\nDo you want to save the output in a text file? (y/n)> ");
  scanf(" %c", &option);
  day = calculateDay(yearInput);
  checkLeapYear(yearInput);
  if (option == 'Y' || option == 'y')
  {
    printCalendarInFile(yearInput, day);
  }
  else
    printCalendar(yearInput, day);
  printf("\n");
  return 0;
}