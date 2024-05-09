
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_DISTRICT_LENGTH 50
#define MAX_PROVINCE_LENGTH 50
#define MAX_ID_LENGTH 20
#define MAX_VOTERS 1000

// Structure to store voter information
struct Voter_26517_E {
    char ID[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char province[MAX_PROVINCE_LENGTH];
    char district[MAX_DISTRICT_LENGTH];
};

// Function to record data from users and store them in a file
void record_data_26517_E(char* filename) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Voter_26517_E voter;

    printf("Enter voter details:\n");
    printf("ID: ");
    scanf("%s", voter.ID);
    printf("Name: ");
    scanf("%s", voter.name);
    printf("Province: ");
    scanf("%s", voter.province);
    printf("District: ");
    scanf("%s", voter.district);

    fprintf(file, "%s,%s,%s,%s\n", voter.ID, voter.name, voter.province, voter.district);
    fclose(file);
    printf("Voter details recorded successfully.\n");
}

// Function to read from the file and display all registered voters
void display_registered_voters_26517_E(char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Voter_26517_E voter;

    printf("Registered Voters:\n");
    while (fscanf(file, "%[^,],%[^,],%[^,],%[^\n]\n", voter.ID, voter.name, voter.province, voter.district) != EOF) {
        printf("ID: %s, Name: %s, Province: %s, District: %s\n", voter.ID, voter.name, voter.province, voter.district);
    }

    fclose(file);
}

// Function to display the list of districts with the total number of voters in each district
void display_district_voters_26517_E(char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Voter_26517_E voter;
    int count = 0;
    char prev_district[MAX_DISTRICT_LENGTH] = "";

    printf("District-wise Voters:\n");
    while (fscanf(file, "%[^,],%[^,],%[^,],%[^\n]\n", voter.ID, voter.name, voter.province, voter.district) != EOF) {
        if (strcmp(voter.district, prev_district) != 0) {
            if (count > 0) {
                printf("%s: %d voters\n", prev_district, count);
            }
            strcpy(prev_district, voter.district);
            count = 1;
        } else {
            count++;
        }
    }
    printf("%s: %d voters\n", prev_district, count);

    fclose(file);
}

// Function to display a user-friendly menu
void menu_26517_E(char* filename) {
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Record Voter Data\n");
        printf("2. Display Registered Voters\n");
        printf("3. Display District-wise Voters\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                record_data_26517_E(filename);
                break;
            case 2:
                display_registered_voters_26517_E(filename);
                break;
            case 3:
                display_district_voters_26517_E(filename);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    } while (choice != 4);
}

int main() {
    char filename[] = "voters_list.txt";
    menu_26517_E(filename);
    return 0;
}
