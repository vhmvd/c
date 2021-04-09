#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char HEADERS[5][10];

struct StudentRecord
{
    long sid;
    char email[30];
    char lname[20];
    char fname[20];
    float cgpa;
    struct StudentRecord* next;
};


int main(int argc, char* argv[])
{
    HEADERS csvHeader = { '\0' };
    FILE* inFile;
    FILE* outFile = NULL;

    if (argc != 3)
    {
        printf("Usage ./topcgpas <sourcecsv> <outputcsv>\n");
        return 1;
    }

    inFile = fopen(argv[1], "r");
    if (inFile == NULL)
    {
        printf("Error! Unable to open the input file %s\n", argv[1]);
        return 1;
    }

    int len = strlen(argv[2]);
    if (len <= 4)
    {
        printf("Error! Invlid output CSV file %s name\n", argv[2]);
        return 1;
    }
    else if (argv[2][len - 1] != 'v' || argv[2][len - 2] != 's' || argv[2][len - 3] != 'c' || argv[2][len - 4] != '.')
    {
        printf("Error! Invlid output CSV file %s name\n", argv[2]);
        return 1;
    }
    else {}

    if (inFile != 0)
    {
        int rType = fscanf(inFile, " %[^,],%[^,],%[^,],%[^,],%s", csvHeader[0], csvHeader[1], csvHeader[2], csvHeader[3], csvHeader[4]);
        if (rType == EOF)
        {
            printf("Error! Input CSV file %s is empty\n", argv[1]);
            return 1;
        }
        else if (rType != 5)
        {
            printf("Error! Input CSV file %s format is incorrect\n", argv[1]);
            return 1;
        }
    }

    struct StudentRecord* head = NULL;
    struct StudentRecord* tail = NULL;
    struct StudentRecord* ptr = NULL;
    struct StudentRecord* temp = NULL;
    long sid;
    char email[30];
    char lname[20];
    char fname[20];
    float cgpa;
    int check = 1;
    while (fscanf(inFile, "%ld,%[^,],%[^,],%[^,],%f", &sid, email, lname, fname, &cgpa) != EOF)
    {
        check = 0;
        if (head == NULL)
        {
            head = (struct StudentRecord*)malloc(sizeof(struct StudentRecord));
            head->cgpa = cgpa;
            head->sid = sid;
            strcpy(head->email, email);
            strcpy(head->lname, lname);
            strcpy(head->fname, fname);
            head->next = NULL;
        }
        else if (head->next == NULL)
        {
            if (cgpa == head->cgpa || cgpa > head->cgpa)
            {
                ptr = head;
                head = (struct StudentRecord*)malloc(sizeof(struct StudentRecord));
                head->cgpa = cgpa;
                head->sid = sid;
                strcpy(head->email, email);
                strcpy(head->lname, lname);
                strcpy(head->fname, fname);
                head->next = ptr;
                ptr->next = NULL;
                ptr = NULL;
            }
            else
            {
                head->next = (struct StudentRecord*)malloc(sizeof(struct StudentRecord));
                ptr = head->next;
                ptr->cgpa = cgpa;
                ptr->sid = sid;
                strcpy(ptr->email, email);
                strcpy(ptr->lname, lname);
                strcpy(ptr->fname, fname);
                ptr->next = NULL;
                ptr = NULL;
            }
        }
        else
        {
            if (cgpa == head->cgpa || cgpa > head->cgpa)
            {
                ptr = head;
                head = (struct StudentRecord*)malloc(sizeof(struct StudentRecord));
                head->cgpa = cgpa;
                head->sid = sid;
                strcpy(head->email, email);
                strcpy(head->lname, lname);
                strcpy(head->fname, fname);
                head->next = ptr;
                ptr = NULL;
            }
            else
            {
                temp = head;
                tail = temp;
                while (temp != NULL)
                {
                    if (cgpa == temp->cgpa || cgpa > temp->cgpa)
                    {
                        ptr = tail->next;
                        tail->next = (struct StudentRecord*)malloc(sizeof(struct StudentRecord));
                        tail = tail->next;
                        tail->cgpa = cgpa;
                        tail->sid = sid;
                        strcpy(tail->email, email);
                        strcpy(tail->lname, lname);
                        strcpy(tail->fname, fname);
                        tail->next = temp;
                        tail = NULL;
                        break;
                    }
                    else if (temp->next == NULL)
                    {
                        temp->next = (struct StudentRecord*)malloc(sizeof(struct StudentRecord));
                        ptr = temp->next;
                        ptr->cgpa = cgpa;
                        ptr->sid = sid;
                        strcpy(ptr->email, email);
                        strcpy(ptr->lname, lname);
                        strcpy(ptr->fname, fname);
                        ptr->next = NULL;
                        ptr = NULL;
                        break;
                    }
                    else
                    {
                        tail = temp;
                        temp = temp->next;
                    }
                }
            }
        }
    }
    if (check)
    {
        printf("Error! Input CSV file %s is empty\n", argv[1]);
        return 1;
    }
    return 0;
}