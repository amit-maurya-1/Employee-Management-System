#include <stdio.h>
#include <string.h>

#include "emp_employee.h"

void leaveRequestFn(int id);
void writeTotalLeaves(int id);
void viewLeaveHistory(int id);
int totalLeaves = 0;
char fromDate[11], toDate[11]; // dd/mm/yyyy

void leave_menu(int id)
{
    int choice;
    printf("\n1. Take leave\n");
    printf("2. View leave history\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            leaveRequestFn(id);
            break;
        case 2:
            viewLeaveHistory(id);
            leave_menu(id);
            break;
        case 3:
            employee_panel(id);
            break;
        default:
            printf("Invalid choice\n");
            leave_menu(id);
            break;
    }
}

void writePendingLeave(int id) {
    FILE *file = fopen("pendingLeaves.txt", "a");
    if (file != NULL) {
        fprintf(file, "%d %d %s %s\n", id, totalLeaves, fromDate, toDate);
        fclose(file);
    } else {
        printf("Failed to open pendingLeaves.txt\n");
    }
}

void leaveRequestFn(int id)
{
    int leave;
    char ch;
    printf("Enter the number of days you want to take leave: ");
    scanf("%d", &leave);
    printf("From date (dd/mm/yyyy): ");
    scanf("%s", fromDate);
    printf("To date (dd/mm/yyyy): ");
    scanf("%s", toDate);
    totalLeaves = leave;

    if (leave > 0) {
        printf("Do you want to submit leave request for approval (y/n): ");
        scanf(" %c", &ch);
        if (ch == 'y' || ch == 'Y') {
            writePendingLeave(id);
            printf("Leave request submitted for admin approval.\n");
        }
    } else {
        printf("Invalid input\n");
        leaveRequestFn(id);
    }

    leave_menu(id);
}


void viewLeaveHistory(int id) {
    FILE *file = fopen("totalLeaves.txt", "r");
    if (file == NULL) {
        printf("No leave history found.\n");
    } else {
        int leave, record_id;
        char from[11], to[11];
        int found = 0;

        printf("\nYour Leave History:\n");
        while (fscanf(file, "%d %d %s %s", &record_id, &leave, from, to) != EOF) {
            if (record_id == id) {
                printf("Leaves taken: %d days, From: %s, To: %s\n", leave, from, to);
                found = 1;
            }
        }
        if (!found) {
            printf("No leave records found for your ID (%d).\n", id);
        }
        fclose(file);
    }
}