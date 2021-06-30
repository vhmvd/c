/* File "transcript.h" */
#if !defined TRANSCRIPT
#define TRANSCRIPT

typedef struct Course
{
   char course_id[8];
   char course_name[100];
   int credit_hours;
   float grade;
} Course;

struct Transcript
{
   int student_id;
   char student_name[100];
   int courses_count;
   Course *courses;
};

/* read_course_info reads from the keybard all the information of one course
   and returns a pointer to the read structure */
Course *read_course_info();

/* read_ transcript reads from the keyboard all the information of student's
   transcript including the student's id, name, number of courses he/she studied
   and then the information of all his/her courses in a dynamically allocated
   array: courses. The function returns a pointer to the transcript structure */
struct Transcript *read_transcript();

/* calc_gpa takes a pointer to a transcript structure and calculates the GPA
   according to the formula: sum(hours_i*grade_i)/sum(hours_i)
   The GPA should be returned as a float. */
float calc_gpa(struct Transcript *t);

/* save_transcript saves all transcript information to text the file fn in the
   following format:

      Transcript of <Student's name> (Student's id) 
      *********************************************** 
      Course Code      Course Name             Hours   Grade
      ------------------------------------------------------
      Code_1           Course_Name_1               4      95
      Code_2           Course_Name_2               4      93
      Code_3           Course_Name_3               3      85
      Code_4           Course_Name_4               3      87
      Code_5           Course_Name_5               3      91
      ------------------------------------------------------
      GPA = %90.95 
*/
void save_transcript(char *fn, struct Transcript *t);

/* main function should read from the keyboard all the information of the transcript 
   of the student with id # 425107125 (provided in the file test.txt) and saves it 
   to the text file "425107125.txt" */
int main();

#endif