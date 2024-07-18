#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct gradeStructure {
    char student_name[20];
    int student_row_number;
    int student_grade;
    char student_remark[5];
};

struct gradeStructure* students = NULL;
int table_length = 0;
int passing_threshold = 40;

void add_student() {
    struct gradeStructure student;

    printf("Enter student name: ");
    scanf("%s", student.student_name);

    student.student_row_number = table_length + 1;
    printf("Enter student grade: ");
    scanf("%d", &student.student_grade);

    if (student.student_grade >= passing_threshold) {
        strcpy(student.student_remark, "Pass");
    } else {
        strcpy(student.student_remark, "Fail");
    }

    students = realloc(students, (table_length + 1) * sizeof(struct gradeStructure));
    students[table_length] = student;
    table_length++;
}

void list_students() {
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

void save_students_to_file(const char *filename) {
    FILE *fptr = fopen(filename, "w");
    if (fptr == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < table_length; i++) {
        fprintf(fptr, "%s %d %d %s\n",
                students[i].student_name,
                students[i].student_row_number,
                students[i].student_grade,
                students[i].student_remark);
    }

    fclose(fptr);
    printf("File saved.\n");
}

void load_students_from_file(const char *filename) {
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    table_length = 0;
    struct gradeStructure temp_student;

    while (fscanf(fptr, "%s %d %d %s",
                  temp_student.student_name,
                  &temp_student.student_row_number,
                  &temp_student.student_grade,
                  temp_student.student_remark) != EOF) {
        students = realloc(students, (table_length + 1) * sizeof(struct gradeStructure));
        students[table_length] = temp_student;
        table_length++;
    }

    fclose(fptr);
    printf("Loaded %d students from file.\n", table_length);
}

void search_student_by_row_number(int row_number) {
    for (int i = 0; i < table_length; i++) {
        if (students[i].student_row_number == row_number) {
            printf("Student found: Row: %d, Name: %s, Grade: %d, Remark: %s\n",
                   students[i].student_row_number,
                   students[i].student_name,
                   students[i].student_grade,
                   students[i].student_remark);
            return;
        }
    }
    printf("Student with row number %d not found.\n", row_number);
}

double calculate_average_grade() {
    if (table_length == 0) {
        return 0.0;
    }
    int total_grades = 0;
    for (int i = 0; i < table_length; i++) {
        total_grades += students[i].student_grade;
    }
    return (double)total_grades / table_length;
}

int compare_grades_asc(const void *a, const void *b) {
    return ((struct gradeStructure *)a)->student_grade - ((struct gradeStructure *)b)->student_grade;
}

int compare_grades_desc(const void *a, const void *b) {
    return ((struct gradeStructure *)b)->student_grade - ((struct gradeStructure *)a)->student_grade;
}

void sort_students(int ascending) {
    if (ascending) {
        qsort(students, table_length, sizeof(struct gradeStructure), compare_grades_asc);
    } else {
        qsort(students, table_length, sizeof(struct gradeStructure), compare_grades_desc);
    }
}

void remove_student() {
    printf("Remove Student\n");
    int row_number;
    printf("Enter row number of student to remove: ");
    scanf("%d", &row_number);

    if (row_number > table_length || row_number < 1) {
        printf("Student not found\n");
    } else {
        for (int i = row_number - 1; i < table_length - 1; i++) {
            students[i] = students[i + 1];
        }
        table_length--;
        students = realloc(students, table_length * sizeof(struct gradeStructure));
        printf("Student removed\n");
    }
}

int main() {
    char firstname[100];
    int choice;
    char save_choice;

    printf("Hello, kindly enter your firstname\n");
    scanf("%s", firstname);
    printf("Hello %s\n", firstname);

    printf("Enter passing threshold: ");
    scanf("%d", &passing_threshold);

    do {
        printf("Menu\n 1. Add Student\n 2. Remove Student\n 3. List Students\n 4. Load From File\n 5. Save and Exit\n 6. Search by Row Number\n 7. Calculate Average Marks\n 8. Sort Students by Marks\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Add Student\n");
            add_student();
            printf("\nStudent added: ROW %d\n", table_length);
        } else if (choice == 2) {
            remove_student();
        } else if (choice == 3) {
            list_students();
        } else if (choice == 4) {
            printf("Loading students from file.\n");
            load_students_from_file("student_record.txt");
        } else if (choice == 6) {
            printf("Search by Row Number\n");
            int row_number;
            printf("Enter row number to search: ");
            scanf("%d", &row_number);
            search_student_by_row_number(row_number);
        } else if (choice == 7) {
            double average = calculate_average_grade();
            printf("Average marks of all students: %.2f\n", average);
        } else if (choice == 8) {
            int sort_choice;
            printf("Enter 1 for ascending order, 0 for descending order: ");
            scanf("%d", &sort_choice);
            sort_students(sort_choice);
            printf("Students sorted.\n");
        }

    } while (choice != 5);

    printf("Do you want to save the students to file? (y/n)\n");
    scanf(" %c", &save_choice);
    if (save_choice == 'y') {
        save_students_to_file("student_record.txt");
    } else {
        printf("Changes not saved.\n");
    }

    printf("Thank you %s\n", firstname);

    // Free dynamically allocated memory
    free(students);

    return 0;
}
