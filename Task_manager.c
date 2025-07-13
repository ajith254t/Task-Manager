#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Task {
    int id;
    char desc[100];
    int done;
};

void addTask() {
    struct Task t;
    FILE *fptr = fopen("tasks.txt", "a");

    printf("Enter task ID: ");
    scanf("%d", &t.id);
    printf("Enter task description: ");
    scanf(" %[^\n]", t.desc);
    t.done = 0;

    fwrite(&t, sizeof(t), 1, fptr);
    fclose(fptr);
}

void viewTasks() {
    struct Task t;
    FILE *fptr = fopen("tasks.txt", "r");

    printf("\n--- All Tasks ---\n");
    while (fread(&t, sizeof(t), 1, fptr)) {
        printf("ID: %d | %s | Status: %s\n", t.id, t.desc, t.done ? "Done" : "Pending");
    }
    fclose(fptr);
}

void markDone() {
    struct Task t;
    int id;
    FILE *fptr = fopen("tasks.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    printf("Enter task ID to mark as done: ");
    scanf("%d", &id);

    while (fread(&t, sizeof(t), 1, fptr)) {
        if (t.id == id) {
            t.done = 1;
        }
        fwrite(&t, sizeof(t), 1, temp);
    }

    fclose(fptr);
    fclose(temp);
    remove("tasks.txt");
    rename("temp.txt", "tasks.txt");
}

void deleteDone() {
    struct Task t;
    FILE *fptr = fopen("tasks.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    while (fread(&t, sizeof(t), 1, fptr)) {
        if (!t.done) {
            fwrite(&t, sizeof(t), 1, temp);
        }
    }

    fclose(fptr);
    fclose(temp);
    remove("tasks.txt");
    rename("temp.txt", "tasks.txt");
}

int main() {
    int choice;
    while (1) {
        printf("\n--- TASK MENU ---\n");
        printf("1. Add Task\n2. View Tasks\n3. Mark as Done\n4. Delete Done Tasks\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: markDone(); break;
            case 4: deleteDone(); break;
            case 5: exit(0);
            default: printf("Invalid choice.\n");
        }
    }

    return 0;
}
