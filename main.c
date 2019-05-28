#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node* Position_S;
typedef struct node* List_S;
typedef struct node* Student;

typedef struct node_f* Faculty;
typedef struct node_f* List_F;
typedef struct node_f* Position_F;


struct node{
    char Name[20];
    char Faculty[20];
    double Tawjihi;
    double HighSchool;
    double PlaceTest;
    double AdMark;
    Student next;
};

struct node_f{
    int minRange;
    int maxRange;
    char Name[20];
    Faculty next;
};

double AdMarkCalc();
void ReadStudents();
void ReadData();
void AcceptStudents();
void PrintList_S(List_S L);
Student FindPrevious();

int StudentsNo = 0 ;
int FacultyNo = 0;
List_S* Lists;  /** Array of linked lists of students dynamically allocated and every list represents a Faculty */
List_S head_S = NULL; /** this is the list that has all the students at first and the rejected students will remain in */
List_F head_F = NULL; /** list of faculties read by the "rates.txt" file */

double TawjihiRate;
double HighSchoolRate;
double PlaceTestRate;

FILE *input, *output;

Student CreateStudent()
{
    /** if head_S is empty add the node to the first if not then traverse to the last element to insert it to the last
        this makes it easy for the ReadStudents() function */
    Student stu = (struct node*) malloc(sizeof(struct node));
    stu -> next = NULL;
    Position_S temp = head_S;
    if(temp == NULL)
        head_S = stu;
    else
    {
        while(temp -> next != NULL)
            temp = temp -> next;
        temp -> next = stu;
    }
    return stu;
}

Faculty CreateFaculty()
{
    /** if head_F is empty add the node to the first if not then traverse to the last element to insert it to the last
        and it makes it easy for the ReadData() function */
    Faculty fac = (struct node_f*) malloc(sizeof(struct node_f));
    fac -> next = NULL;
    Position_F temp = head_F;
    if(temp == NULL)
        head_F = fac;
    else
    {
        while(temp -> next != NULL)
            temp = temp -> next;
        temp -> next = fac;
    }
    return fac;
}

int menu(){
    int ch;
    system("cls");
    printf("\n1) Read The Files");
    printf("\n2) Accept New Students");
    printf("\n3) Print All Accepted Students By Faculties");
    printf("\n4) Print Rejected Students");
    printf("\n5) Write Accepted and Not Accepted Students To File");
    printf("\n6) Exit");
    printf("\n\nEnter your choice : ");
    scanf("%d",&ch);
    return ch;

}

int main()
{
    int choice;
    system("cls");
    while(1)
    {
        choice = menu();
        switch(choice)
        {
        case 1 :
            {
            ReadData();
            ReadStudents();
            printf("Students and Rates are read from Files !\n");
            break;
            }
        case 2 :
            AcceptStudents();
            printf("Students Accepted !\n");
            break;

        case 3 :{
                int index = 0;
                Faculty fac = head_F;
                while(fac != NULL){
                    printf("\n\n*%s* : \n",fac->Name);
                    PrintList_S(Lists[index]);
                    fac = fac->next;
                    index++;
                }
            break;
            }
        case 4 :
            printf("\nRejected Students : \n");
            PrintList_S(head_S);
            break;

        case 5 :
            WriteStudentsToFile();
            printf("Students are written on file!\n");
            break;

        case 6 :
            exit(0);

        default :
            printf("\nPlease Enter a value from the menu\n");
        }

    printf("\n\nPress any key to continue.\n");
        getch();
    }
    return 0;
}

void ReadData()
{
    input = fopen("rates.txt", "r");
    if(input == NULL)
        printf("Cannot open rates.txt");
    else
    {
        fscanf(input, "%lf %lf %lf %d", &TawjihiRate, &HighSchoolRate, &PlaceTestRate, &FacultyNo);
        Lists = malloc((FacultyNo)*sizeof(struct node)); //number of Lists needed for the students for all faculties

        int i = 0 ;
        for(i = 0 ; i < FacultyNo ; i ++)
            Lists[i] = NULL;

        while(!feof(input))
        {
            Faculty temp = CreateFaculty();
            fscanf(input,"%s %d %d", temp -> Name, &temp->maxRange, &temp->minRange);
        }
    }
    close(input);
}

void ReadStudents()
{
    int i = 0;
    input = fopen("students.txt", "r");

    if(input == NULL)
        printf("cannot open file students.txt");

    else{

        while(!feof(input))
        {
            Student temp = CreateStudent();
            fscanf(input, "%[^\t] %lf %lf %lf", temp -> Name, &temp->Tawjihi, &temp->HighSchool, &temp->PlaceTest);
            temp -> AdMark = AdMarkCalc(temp);
            i++;
        }

        StudentsNo = i;

    }

    close(input);
}
double AdMarkCalc(Student stu)
{
    return TawjihiRate*stu -> Tawjihi + HighSchoolRate*stu -> HighSchool + PlaceTestRate*stu -> PlaceTest;
}

void AcceptStudents()
{
    int index = 0;
    Position_S p = head_S, temp, inList, t = head_S;
    Position_F pf = head_F;
    if(p == NULL && pf == NULL){
        printf("There's no students or faculties");
        return;
    }
    else{
        while(pf != NULL)
        {
            p = head_S;
            while(p != NULL)
            {
                t = p -> next; /** to keep the next element pointed at and not lose tail
                    because if the condition is true then the node p is pointing at, will be moved to another list */
                if((p -> AdMark < pf -> maxRange) && (p->AdMark > pf-> minRange))
                {
                    if(Lists[index] == NULL)
                        Lists[index]= p;
                    else
                    {
                        inList = Lists[index];
                        while(inList -> next != NULL)
                            inList = inList -> next;
                        inList -> next = p;
                    } // if Lists[index] is not empty
                    /**
                    since we're moving the student node from the head_S
                    to the Lists[index] list so that the rejected students
                    remain in the head_S list so we need to check if the node
                    we're moving is the first/only node in the head_S in order to make
                    the head_S points to the next student or NULL
                     */

                    if(p == head_S){
                        head_S = p -> next;
                        p -> next = NULL;
                    }
                    else
                    {
                      temp = FindPrevious(p);
                      temp -> next = p -> next;
                      p -> next = NULL;
                    }
                } // AdMark Condition condition
                p = t ; /** p is now back pointing at the next student
                in the head_S list */
            } // Student while
            pf = pf -> next;
            index++; // index of the array
        } // Faculty while
    }
}

void WriteStudentsToFile()
{
    int index = 0;
    Faculty pf = head_F;
    Student p = Lists[index];
    output = fopen("allStudents.txt", "w");
    fprintf(output,"* Accepted Students * :");
    while(pf != NULL)
    {
        while(p != NULL)
        {
            fprintf(output,"%s",p->Name);
            p = p -> next;
        }
        index++;
        p = Lists[index];
        pf = pf->next;
    }

    p = head_S;
    fprintf(output,"\n\n* Rejected Students * :");
    while(p != NULL)
    {
        fprintf(output,"%s",p->Name);
        p = p-> next;
    }

    close(output);
}

void PrintList_S(List_S L)
{
    if(L == NULL)
        printf("There's no students!");
    else
    {
        Position_S temp = L;
        while(temp != NULL)
        {
            printf("%s",temp -> Name);
            temp = temp -> next;
        }
    }
}

Student FindPrevious(Student stu)
{
    Position_S temp = head_S;
    while(temp -> next != stu)
        temp = temp -> next;
    return temp;
}
