#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50
#define MAX_COURSE_LENGTH 50
#define FILE_NAME "students_data.txt"

struct Student {
    char name[MAX_NAME_LENGTH];
    char course[MAX_COURSE_LENGTH];
    float amount_paid;
    float exam_score;
};

// Function to record data from users and store them in a file
void record_data_A12345_A(struct Student students[], int *num_students) {
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter student name: ");
    scanf("%s", students[*num_students].name);

    printf("Enter course: ");
    scanf("%s", students[*num_students].course);

    printf("Enter amount paid: ");
    scanf("%f", &students[*num_students].amount_paid);

    printf("Enter exam score: ");
    scanf("%f", &students[*num_students].exam_score);

    fprintf(file, "%s %s %.2f %.2f\n", students[*num_students].name, students[*num_students].course,
            students[*num_students].amount_paid, students[*num_students].exam_score);

    fclose(file);
    (*num_students)++;
}

// Function to read from the file and display all students
void display_all_students_A12345_A(struct Student students[], int num_students) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Students:\n");
    printf("Name\t\tCourse\t\tAmount Paid\tExam Score\n");
    while (fscanf(file, "%s %s %f %f", students[num_students].name, students[num_students].course,
                  &students[num_students].amount_paid, &students[num_students].exam_score) != EOF) {
        printf("%s\t\t%s\t\t%.2f\t\t%.2f\n", students[num_students].name, students[num_students].course,
               students[num_students].amount_paid, students[num_students].exam_score);
    }

    fclose(file);
}

// Function to display students per course and total amount paid
void display_students_per_course_A12345_A(struct Student students[], int num_students) {
    char course[MAX_COURSE_LENGTH];
    float total_amount = 0;

    printf("Enter course to display students: ");
    scanf("%s", course);

    printf("Students in %s:\n", course);
    printf("Name\t\tAmount Paid\n");
    for (int i = 0; i < num_students; i++) {
        if (strcmp(students[i].course, course) == 0) {
            printf("%s\t\t%.2f\n", students[i].name, students[i].amount_paid);
            total_amount += students[i].amount_paid;
        }
    }

    printf("Total amount paid for %s: %.2f\n", course, total_amount);
}

// Function to display a user-friendly menu
void display_menu_A12345_A() {
    printf("Welcome to ADMI Training Center\n");
    printf("1. Record student data\n");
    printf("2. Display all students\n");
    printf("3. Display students per course\n");
    printf("4. Exit\n");
}

int main() {
    struct Student students[MAX_STUDENTS];
    int num_students = 0;
    int choice;

    do {
        display_menu_A12345_A();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                record_data_A12345_A(students, &num_students);
                break;
            case 2:
                display_all_students_A12345_A(students, num_students);
                break;
            case 3:
                display_students_per_course_A12345_A(students, num_students);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

