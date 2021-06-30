#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transcript.h"

Course *read_course_info()
{
  struct Course *newCourse = malloc(sizeof(struct Course));
  scanf(" %[^\n]", newCourse->course_id);
  scanf(" %[^\n]", newCourse->course_name);
  scanf("%d", &newCourse->credit_hours);
  scanf("%f", &newCourse->grade);
  return newCourse;
}

struct Transcript *read_transcript()
{
  struct Transcript *newTranscript = malloc(sizeof(struct Transcript));
  scanf("%d", &newTranscript->student_id);
  scanf(" %[^\n]", newTranscript->student_name);
  scanf("%d", &newTranscript->courses_count);
  newTranscript->courses = malloc(newTranscript->courses_count * sizeof(struct Course *));
  int i;
  for (i = 0; i < newTranscript->courses_count; i++)
  {
    newTranscript->courses[i] = *read_course_info();
  }
  return newTranscript;
}

float calc_gpa(struct Transcript *t)
{
  float gSum = 0.0;
  float hSum = 0.0;
  int i;
  for (i = 0; i < t->courses_count; i++)
  {
    gSum += (t->courses[i].grade * t->courses[i].credit_hours);
    hSum += t->courses[i].credit_hours;
  }
  return (float)gSum / hSum;
}

void save_transcript(char *fn, struct Transcript *t)
{
  FILE *outFile = fopen(fn, "w");
  if (outFile == NULL)
  {
    printf("Error! Could not open file\n");
    exit(-1);
  }
  char cc[] = "Course Code";
  char cn[] = "Course Name";
  char ch[] = "Hours";
  char cg[] = "Grade";
  fprintf(outFile, "Transcript of <%s> (%d)\n", t->student_name, t->student_id);
  fprintf(outFile, "*********************************************************\n");
  fprintf(outFile, "%-20s%-20s%-10s%-10s\n", cc, cn, ch, cg);
  fprintf(outFile, "---------------------------------------------------------\n");
  int i;
  for(i=0; i<t->courses_count; i++)
  {
    fprintf(outFile, "%-20s%-20s%-10d%-10.0f\n", t->courses[i].course_id, t->courses[i].course_name, t->courses[i].credit_hours, t->courses[i].grade);
  }
  fprintf(outFile, "---------------------------------------------------------\n");
  fprintf(outFile, "GPA = %c%2.2f\n", '%', calc_gpa(t));
  fclose(outFile);
}

int main()
{
  struct Transcript *test = read_transcript();
  char fName[14];
  snprintf(fName, sizeof(fName), "%d", test->student_id);
  strcat(fName, ".txt");
  save_transcript(fName, test);
  free(test->courses);
  free(test);
  return 0;
}