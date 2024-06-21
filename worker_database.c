#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "workers.dat"
#define MAX_NAME_LENGTH 100

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    char position[MAX_NAME_LENGTH];
    float salary;
} Worker;

void addWorker() {
    FILE *file = fopen(FILENAME, "ab");
    if (file == NULL) {
        printf("Could not open file for appending.\n");
        return;
    }

    Worker worker;
    printf("Enter Worker ID: ");
    scanf("%d", &worker.id);
    printf("Enter Worker Name: ");
    scanf("%s", worker.name);
    printf("Enter Worker Age: ");
    scanf("%d", &worker.age);
    printf("Enter Worker Position: ");
    scanf("%s", worker.position);
    printf("Enter Worker Salary: ");
    scanf("%f", &worker.salary);

    fwrite(&worker, sizeof(Worker), 1, file);
    fclose(file);

    printf("Worker added successfully.\n");
}

void displayWorkers() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Could not open file for reading.\n");
        return;
    }

    Worker worker;
    while (fread(&worker, sizeof(Worker), 1, file)) {
        printf("ID: %d\n", worker.id);
        printf("Name: %s\n", worker.name);
        printf("Age: %d\n", worker.age);
        printf("Position: %s\n", worker.position);
        printf("Salary: %.2f\n", worker.salary);
        printf("\n");
    }

    fclose(file);
}

void updateWorker() {
    FILE *file = fopen(FILENAME, "rb+");
    if (file == NULL) {
        printf("Could not open file for updating.\n");
        return;
    }

    int id;
    printf("Enter Worker ID to update: ");
    scanf("%d", &id);

    Worker worker;
    int found = 0;
    while (fread(&worker, sizeof(Worker), 1, file)) {
        if (worker.id == id) {
            found = 1;
            fseek(file, -sizeof(Worker), SEEK_CUR);
            printf("Enter new Worker Name: ");
            scanf("%s", worker.name);
            printf("Enter new Worker Age: ");
            scanf("%d", &worker.age);
            printf("Enter new Worker Position: ");
            scanf("%s", worker.position);
            printf("Enter new Worker Salary: ");
            scanf("%f", &worker.salary);
            fwrite(&worker, sizeof(Worker), 1, file);
            printf("Worker updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Worker with ID %d not found.\n", id);
    }

    fclose(file);
}

void deleteWorker() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Could not open file for deleting.\n");
        return;
    }

    FILE *tempFile = fopen("temp.dat", "wb");
    if (tempFile == NULL) {
        printf("Could not open temporary file.\n");
        fclose(file);
        return;
    }

    int id;
    printf("Enter Worker ID to delete: ");
    scanf("%d", &id);

    Worker worker;
    int found = 0;
    while (fread(&worker, sizeof(Worker), 1, file)) {
        if (worker.id == id) {
            found = 1;
        } else {
            fwrite(&worker, sizeof(Worker), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename("temp.dat", FILENAME);

    if (found) {
        printf("Worker deleted successfully.\n");
    } else {
        printf("Worker with ID %d not found.\n", id);
    }
}

int main() {
    int choice;
    while (1) {
        printf("1. Add Worker\n");
        printf("2. Display Workers\n");
        printf("3. Update Worker\n");
        printf("4. Delete Worker\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addWorker();
                break;
            case 2:
                displayWorkers();
                break;
            case 3:
                updateWorker();
                break;
            case 4:
                deleteWorker();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

