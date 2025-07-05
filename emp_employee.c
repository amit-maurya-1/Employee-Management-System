#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "leave_management.h"
#include "attendance.h"

struct Employee
{
    int id;
    char name[20];
    char gender[10];
    float salary;
    int mobile;
    char address[20];
    int leave;
};

extern struct Employee emp; 
extern FILE *fp;

// Function for employee to view only their own data
void view_my_data(int id) {
    // char string[15];
    int flag = 0;

    fp = fopen("emp.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // printf("Enter your Employee ID or Mobile Number: ");
    // fgets(string, sizeof(string), stdin);
    // string[strcspn(string, "\n")] = 0;

    printf("\n%-5s %-15s %-10s %-10s %-12s %-15s %-5s", "ID", "Name", "Gender", "Salary", "Mobile", "Address", "Leave");
    printf("\n-------------------------------------------------------------------------------------------");  

    while(fscanf(fp, "%d,%[^,],%[^,],%f,%d,%[^,],%d\n",
                 &emp.id, emp.name, emp.gender, &emp.salary,
                 &emp.mobile, emp.address, &emp.leave) == 7)
    {
        if (emp.id == id) {
            flag = 1;
            printf("\n%-5d %-15s %-10s %-10.2f %-12d %-15s %-5d",
                   emp.id, emp.name, emp.gender, emp.salary, emp.mobile, emp.address, emp.leave);
            printf("\n-------------------------------------------------------------------------------------------");  
            break; // Only show own record
        }
    }
    if (flag == 0) {
        printf("\nSorry! No record found.\n");
    }

    fclose(fp);
}

int employee_panel(int id) {
    int choice;
    while (1) {
        printf("\n\nEmployee Panel");
        printf("\n1. View My Details");
        printf("\n2. Leave Management");
        printf("\n3. Mark Attendance");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear buffer

        switch (choice) {
            case 1:
                view_my_data(id);
                break;
            case 2:
                leave_menu(id);
            case 3:
                att_menu(id);
            case 4:
                printf("Exiting Employee Panel...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
