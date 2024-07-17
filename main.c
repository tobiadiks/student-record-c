#include <stdio.h>
#include <string.h>

struct gradeStructure
{
    char student_name[20];
    int student_row_number;
    int student_grade;
    char student_remark[5];
};

struct gradeStructure students[100];
int table_length = 0;
int passing_threshold = 40;

void add_student()
{
    struct gradeStructure student;

    printf("Enter student name: ");
    scanf("%s", student.student_name);

    student.student_row_number = table_length + 1;
    printf("Enter student grade: ");
    scanf("%d", &student.student_grade);
    if (student.student_grade >= passing_threshold)
    {
        strcpy(student.student_remark, "Pass");
    }
    else
    {
        strcpy(student.student_remark, "Fail");
    }
    students[table_length] = student;
}

// Function for removing student record
void remove_student(int row_number)
{
    
            if (row_number > table_length+1)
            {
                printf("Student not found\n");
            }
            else
            {
                for (int i = row_number; i < table_length; i++)
                {
                    students[i] = students[i + 1];
                }
                table_length--;
            }
}


// List students
void list_students()
{
    if (table_length == 0) {
        printf("No students listed.\n");
    } else {
        printf("Listing students:\n");
        for (int i = 0; i < table_length; i++) {
            printf("Row: %d, Name: %s, Grade: %d, Remark: %s\n",
                   students[i].student_row_number,
                   students[i].student_name,
                   students[i].student_grade,
                   students[i].student_remark);
        }
    }
}

// Load file
void load_students() {
    FILE *fptr = fopen("student_record.txt", "r");
    // Print some text if the file does not exist
    if(fptr == NULL) {
        printf("Not able to open the file.");
    }

    // Store the content of the file
    char loadedString[100];

    // Read the content and store it inside myString
    fgets(loadedString, 100, fptr);

    // Print the file content
    printf("%s\n", loadedString);

    // Close the file
    fclose(fptr);
}

// Main Program
int main()
{
    FILE *fptr = fopen("student_record.txt", "w");
    char firstname[100];
    int choice;
    char save_choice;

    printf("Hello, kindly enter your firstname\n");

    scanf("%s", firstname);

    printf("Hello %s\n", firstname);

    printf("Enter passing threshold: ");

    scanf("%d", &passing_threshold);
    do
    {
        printf("Menu\n 1. Add Student\n 2. Remove Student\n 3. List Students\n 4. Load From File\n 5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        /* add  student option */
        if (choice == 1)
        {
            printf("Add Student\n");

            add_student();
            printf("\nStudent added: ROW %d\n", table_length + 1);

            fprintf(fptr, "%s\t%d\t%d\t%s\n", students[table_length].student_name, students[table_length].student_row_number, students[table_length].student_grade, students[table_length].student_remark);
            table_length++;
        }
        /* remove student option */
        else if (choice == 2)
        {
            printf("Remove Student\n");
            int row_number;
            printf("Enter row number of student to remove: ");
            scanf("%d", &row_number);
            remove_student(row_number);
        }
        /* list students action */
        else if (choice == 3) {
            list_students();
        }
        /* load students action */
        else if (choice == 4) {
            load_students();
        }

    } while (choice != 5);

    printf("Do you want to save as file? (y/n)\n");
    scanf(" %c", &save_choice);
    if (save_choice == 'y')
    {
        fclose(fptr);
        printf("File saved\n");
    }
    else
    {
        printf("File not saved\n");
    }

    printf("Thank you %s\n", firstname);
    return 0;
}
