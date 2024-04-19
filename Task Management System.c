//<!--  Author Name: Christophe Nshimiyimana.
                        // GigHub Link: https://github.com/Christophe210
                        // Visit My Website : tsindamedia.com -->


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define FILENAME "tasks.txt"

// Define structure for a task
struct Task {
    char title[50];
    char description[100];
    char due_date[20];
    int priority;
    int status; // 0 for incomplete, 1 for complete
};

// Function prototypes
void display_menu();
void create_task(struct Task tasks[], int *task_count);
void read_tasks(struct Task tasks[], int task_count);
void update_task(struct Task tasks[], int task_count);
void delete_task(struct Task tasks[], int *task_count);
void save_tasks_to_file(struct Task tasks[], int task_count);
void load_tasks_from_file(struct Task tasks[], int *task_count);

// Main function
int main() {
    struct Task tasks[MAX_TASKS]; // Array to store tasks
    int task_count = 0; // Variable to keep track of number of tasks

    // Load tasks from file
    load_tasks_from_file(tasks, &task_count);

    int choice;
    do {
        display_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                create_task(tasks, &task_count);
                break;
            case 2:
                read_tasks(tasks, task_count);
                break;
            case 3:
                update_task(tasks, task_count);
                break;
            case 4:
                delete_task(tasks, &task_count);
                break;
            case 5:
                save_tasks_to_file(tasks, task_count);
                printf("Tasks saved to file.\n");
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

// Function to display menu
void display_menu() {
    printf("\nTask Management System\n");
    printf("1. Create Task\n");
    printf("2. Read Tasks\n");
    printf("3. Update Task\n");
    printf("4. Delete Task\n");
    printf("5. Exit\n");
}

// Function to create a new task
void create_task(struct Task tasks[], int *task_count) {
    if (*task_count >= MAX_TASKS) {
        printf("Maximum number of tasks reached.\n");
        return;
    }

    struct Task new_task;

    printf("Enter title: ");
    fgets(new_task.title, sizeof(new_task.title), stdin);
    new_task.title[strcspn(new_task.title, "\n")] = '\0'; // Remove trailing newline

    printf("Enter description: ");
    fgets(new_task.description, sizeof(new_task.description), stdin);
    new_task.description[strcspn(new_task.description, "\n")] = '\0'; // Remove trailing newline

    printf("Enter due date: ");
    fgets(new_task.due_date, sizeof(new_task.due_date), stdin);
    new_task.due_date[strcspn(new_task.due_date, "\n")] = '\0'; // Remove trailing newline

    printf("Enter priority (1-5): ");
    scanf("%d", &new_task.priority);
    getchar(); // Consume newline character

    new_task.status = 0; // New task is incomplete

    tasks[*task_count] = new_task;
    (*task_count)++;
}

// Function to read and display all tasks
void read_tasks(struct Task tasks[], int task_count) {
    if (task_count == 0) {
        printf("No tasks found.\n");
        return;
    }

    printf("\nTasks:\n");
    for (int i = 0; i < task_count; i++) {
        printf("Task %d:\n", i + 1);
        printf("Title: %s\n", tasks[i].title);
        printf("Description: %s\n", tasks[i].description);
        printf("Due Date: %s\n", tasks[i].due_date);
        printf("Priority: %d\n", tasks[i].priority);
        printf("Status: %s\n", tasks[i].status ? "Complete" : "Incomplete");
        printf("\n");
    }
}

// Function to update an existing task
void update_task(struct Task tasks[], int task_count) {
    if (task_count == 0) {
        printf("No tasks found.\n");
        return;
    }

    printf("Enter task number to update (1-%d): ", task_count);
    int task_number;
    scanf("%d", &task_number);
    getchar(); // Consume newline character

    if (task_number < 1 || task_number > task_count) {
        printf("Invalid task number.\n");
        return;
    }

    struct Task *task = &tasks[task_number - 1];

    printf("Enter new title: ");
    fgets(task->title, sizeof(task->title), stdin);
    task->title[strcspn(task->title, "\n")] = '\0'; // Remove trailing newline

    printf("Enter new description: ");
    fgets(task->description, sizeof(task->description), stdin);
    task->description[strcspn(task->description, "\n")] = '\0'; // Remove trailing newline

    printf("Enter new due date: ");
    fgets(task->due_date, sizeof(task->due_date), stdin);
    task->due_date[strcspn(task->due_date, "\n")] = '\0'; // Remove trailing newline

    printf("Enter new priority (1-5): ");
    scanf("%d", &task->priority);
    getchar(); // Consume newline character
}

// Function to delete an existing task
void delete_task(struct Task tasks[], int *task_count) {
    if (*task_count == 0) {
        printf("No tasks found.\n");
        return;
    }

    printf("Enter task number to delete (1-%d): ", *task_count);
    int task_number;
    scanf("%d", &task_number);
    getchar(); // Consume newline character

    if (task_number < 1 || task_number > *task_count) {
        printf("Invalid task number.\n");
        return;
    }

    // Shift tasks to fill the gap
    for (int i = task_number - 1; i < *task_count - 1; i++) {
        tasks[i] = tasks[i + 1];
    }

    (*task_count)--;
}

// Function to save tasks to file
void save_tasks_to_file(struct Task tasks[], int task_count) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < task_count; i++) {
        fprintf(file, "%s\n%s\n%s\n%d\n%d\n",
                tasks[i].title, tasks[i].description, tasks[i].due_date,
                tasks[i].priority, tasks[i].status);
    }

    fclose(file);
}

// Function to load tasks from file
void load_tasks_from_file(struct Task tasks[], int *task_count) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No tasks found.\n");
        return;
    }

    while ((*task_count) < MAX_TASKS && fscanf(file, "%49[^\n]\n%99[^\n]\n%19[^\n]\n%d\n%d\n",
            tasks[*task_count].title, tasks[*task_count].description,
            tasks[*task_count].due_date, &tasks[*task_count].priority,
            &tasks[*task_count].status) == 5) {
        (*task_count)++;
    }

    fclose(file);
}


//<!--  Author Name: Christophe Nshimiyimana.
                        // GigHub Link: https://github.com/Christophe210
                        // Visit My Website : tsindamedia.com -->
