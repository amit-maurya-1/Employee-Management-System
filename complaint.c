#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    char gender[10];
    float salary;
    long long int mobile;
    char address[50];
    int leave;
    char complaint[300]; // increased size for multiple complaints
};

// Add complaint to an employee
void addComplaint() {
    int searchId;
    char newComplaint[100];
    int found = 0;

    FILE *fp = fopen("emp.txt", "r");
    FILE *ft = fopen("temp.txt", "w");

    if (fp == NULL || ft == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter Employee ID to add complaint: ");
    scanf("%d", &searchId);
    while (getchar() != '\n'); // flush buffer

    struct Employee emp;
    char line[500];

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d,%[^,],%[^,],%f,%lld,%[^,],%d,%[^\n]",
               &emp.id, emp.name, emp.gender, &emp.salary, &emp.mobile,
               emp.address, &emp.leave, emp.complaint);

        if (emp.id == searchId) {
            found = 1;
            printf("\n--- Employee Found ---\n");
            printf("ID: %d\nName: %s\nGender: %s\nSalary: %.2f\nMobile: %lld\nAddress: %s\nLeave: %d\nComplaints: %s\n",
                   emp.id, emp.name, emp.gender, emp.salary, emp.mobile,
                   emp.address, emp.leave, emp.complaint);

            printf("\nEnter new complaint: ");
            fgets(newComplaint, sizeof(newComplaint), stdin);
            newComplaint[strcspn(newComplaint, "\n")] = '\0'; // Remove trailing newline

            if (strlen(emp.complaint) > 0) {
                strcat(emp.complaint, " , "); // add separator
            }
            strcat(emp.complaint, newComplaint); // Append new complaint
        }

        fprintf(ft, "%d,%s,%s,%.2f,%lld,%s,%d,%s\n",
                emp.id, emp.name, emp.gender, emp.salary, emp.mobile,
                emp.address, emp.leave, emp.complaint);
    }

    fclose(fp);
    fclose(ft);

    remove("emp.txt");
    rename("temp.txt", "emp.txt");

    if (found) {
        printf("\nComplaint added successfully to Employee ID %d.\n", searchId);
    } else {
        printf("\nEmployee with ID %d not found.\n", searchId);
    }
}

// View single employee report
void viewReport() {
    FILE *fp = fopen("emp.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Employee emp;
    char line[500];
    int searchId, found = 0;

    printf("\nEnter Employee ID to search: ");
    scanf("%d", &searchId);

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d,%[^,],%[^,],%f,%lld,%[^,],%d,%[^\n]",
               &emp.id, emp.name, emp.gender, &emp.salary, &emp.mobile,
               emp.address, &emp.leave, emp.complaint);

        if (emp.id == searchId) {
            found = 1;
            printf("\n---------------------------------------------------------------------------------------------------------------------------------\n");
            printf("| ID  | Name                | Gender | Salary     | Mobile       | Address       | Leave | Complaints                          |\n");
            printf("---------------------------------------------------------------------------------------------------------------------------------\n");

            printf("| %-3d | %-19s | %-6s | %-10.2f | %-12lld | %-13s | %-5d | %-35s |\n",
                   emp.id, emp.name, emp.gender, emp.salary, emp.mobile,
                   emp.address, emp.leave, emp.complaint);

            printf("---------------------------------------------------------------------------------------------------------------------------------\n");
            break;
        }
    }

    if (!found) {
        printf("\nEmployee with ID %d not found.\n", searchId);
    }

    fclose(fp);
}

int complaint_menu() {
    int choice;
    int flag = 1;
    while (flag == 1) {
        printf("\n--- Employee Complaint System ---\n");
        printf("1. Add Complaint\n");
        printf("2. View Report (Search by ID)\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addComplaint();
                break;
            case 2:
                viewReport();
                break;
            case 3:
                // printf("\nReturning Back\n");
                flag = 0;
                break;
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
