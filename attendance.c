#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "emp_employee.h"

#define MAX_LINE_LENGTH 200

void markAttendance(int id) {
    int choice;
    time_t currentTime = time(NULL);
    char *timeStr = ctime(&currentTime);

    printf("\n1. Log In\n2. Log Out\nEnter your choice: ");
    scanf("%d", &choice);

    FILE *file = fopen("attendance.txt", "a");
    if (!file) {
        printf("Error opening attendance file.\n");
        return;
    }

    fprintf(file, "Employee ID: %d\n", id);

    if (choice == 1) {
        fprintf(file, "Logged in at: %s", timeStr);
        printf("Login recorded at: %s", timeStr);
    } else if (choice == 2) {
        fprintf(file, "Logged out at: %s", timeStr);
        printf("Logout recorded at: %s", timeStr);
    } else {
        printf("Invalid choice.\n");
    }

    fprintf(file, "\n");
    fclose(file);
}

void searchAttendance(int target_id) {
    FILE *file = fopen("attendance.txt", "r");
    if (!file) {
        printf("Could not open attendance file.\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int id;
    int found = 0;

    printf("\n---- Attendance Record for ID: %d ----\n\n", target_id);
    while (fscanf(file, "Employee ID: %d\n", &id) != EOF) {
        if (!fgets(line, sizeof(line), file)) break;

        if (id == target_id && (strstr(line, "Logged in") || strstr(line, "Logged out"))) {
            found = 1;
            printf("%s", line);
            printf("---------------------------\n");
        }

        fgets(line, sizeof(line), file); // skip empty line
    }

    if (!found) {
        printf("No attendance records found for ID: %d.\n", target_id);
    }

    fclose(file);
}

void exportPersonalAttendance(int target_id) {
    FILE *file = fopen("attendance.txt", "r");
    FILE *outFile = fopen("personal_attendance.txt", "w");

    if (!file || !outFile) {
        printf("Error opening files.\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int id;
    int found = 0;

    while (fscanf(file, "Employee ID: %d\n", &id) != EOF) {
        fgets(line, sizeof(line), file);  // Read log line

        if (id == target_id) {
            found = 1;
            fprintf(outFile, "Employee ID: %d\n", id);
            fputs(line, outFile);
            fputs("\n", outFile);
        }

        fgets(line, sizeof(line), file); // skip extra newline
    }

    fclose(file);
    fclose(outFile);

    if (found)
        printf("All records for ID %d saved to personal_attendance.txt\n", target_id);
    else
        printf("No records found for ID %d.\n", target_id);
}

int att_menu(int id) {
    int choice;

    do {
        printf("\nAttendance Menu for ID: %d\n", id);
        printf("1. Mark Attendance (Login/Logout)\n");
        printf("2. View My Attendance\n");
        printf("3. Export My Attendance to File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                markAttendance(id);
                break;
            case 2:
                searchAttendance(id);
                break;
            case 3:
                exportPersonalAttendance(id);
                break;
            case 4:
                employee_panel(id);
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    return 0;
}
