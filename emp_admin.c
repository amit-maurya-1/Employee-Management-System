#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "leave_management.h"
#include "complaint.h"

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

struct Employee emp;
FILE *fp, *ft;

int recsize = sizeof(struct Employee);
int admin_panel();      //admin(main) function declaration

void add()
{
    fp = fopen("emp.txt", "a+");  
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter ID = ");
    scanf("%d", &emp.id);

    while(getchar() != '\n');  // Clear input buffer

    printf("Enter name = ");
    fgets(emp.name, sizeof(emp.name), stdin);
    emp.name[strcspn(emp.name, "\n")] = 0;  // Remove the trailing newline character

    printf("Enter Gender = ");
    fgets(emp.gender, sizeof(emp.gender), stdin);
    emp.gender[strcspn(emp.gender, "\n")] = 0;  // Remove the trailing newline character

    printf("Enter salary = ");
    scanf("%f", &emp.salary);

    printf("Enter mobile = ");
    scanf("%d", &emp.mobile);
    while(getchar() != '\n');

    printf("Enter address = ");
    fgets(emp.address, sizeof(emp.address), stdin);
    emp.address[strcspn(emp.address, "\n")] = 0;  // Remove the trailing newline character

    printf("Enter leaves = ");
    scanf("%d", &emp.leave);
    // Write to file
    fprintf(fp, "%d,%s,%s,%.2f,%d,%s,%d\n", emp.id, emp.name, emp.gender, emp.salary, emp.mobile, emp.address, emp.leave);
    fclose(fp);  // Close the file

    printf("Record Inserted Successfully\n");
}

void search()
{
    char string[15];
    int flag = 0;

    fp = fopen("emp.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter Employee ID or Mobile Number = ");
    fgets(string, sizeof(string), stdin);
    string[strcspn(string, "\n")] = 0;
    printf("\n%-5s %-15s %-10s %-10s %-12s %-15s %-5s", "ID", "Name", "Gender", "Salary", "Mobile", "Address", "Leave");
    printf("\n-------------------------------------------------------------------------------------------");  

while(fscanf(fp, "%d,%[^,],%[^,],%f,%d,%[^,],%d\n",&emp.id,emp.name,emp.gender,&emp.salary,&emp.mobile,emp.address,&emp.leave) == 7)
{
    if (emp.mobile == atoi(string) || emp.id == atoi(string)) {
        flag = 1;
                    //printf("\nID\tName\tGender\tSalary\tMobile\tAddress\tLeaves\n");
      printf("\n%-5d %-15s %-10s %-10.2f %-12d %-15s %-5d",emp.id,emp.name,emp.gender,emp.salary,emp.mobile,emp.address,emp.leave);
       printf("\n-------------------------------------------------------------------------------------------");  
     break;
    }
}
if (flag == 0) {
    printf("\nSorry! Employee ID or Mobile Number not found.\n");
}

fclose(fp);  // Close the file
}

void display()
{
fp = fopen("emp.txt", "a+");  
if (fp == NULL) {
    printf("Error opening file!\n");
    return;
}
rewind(fp);
printf("\n%-5s %-15s %-10s %-10s %-12s %-15s %-5s", "ID", "Name", "Gender", "Salary", "Mobile", "Address", "Leave");
printf("\n-------------------------------------------------------------------------------------------");  

while(fscanf(fp, "%d,%[^,],%[^,],%f,%d,%[^,],%d\n",&emp.id,emp.name,emp.gender,&emp.salary,&emp.mobile,emp.address,&emp.leave) == 7)
{
    printf("\n%-5d %-15s %-10s %-10.2f %-12d %-15s %-5d",emp.id,emp.name,emp.gender,emp.salary,emp.mobile,emp.address,emp.leave);
}
    printf("\n-------------------------------------------------------------------------------------------");  
    fclose(fp);
}

void edit() {
    FILE *fp, *temp;
    char string[15];
    int flag = 0;

    fp = fopen("emp.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Employee ID: ");
    fgets(string, sizeof(string), stdin);
    string[strcspn(string, "\n")] = 0;
    
    // int option;
    int option;
    printf("\n1.Name");
    printf("\n2.Gender");
    printf("\n3.Salary");
    printf("\n4.Mobile");
    printf("\n5.Address");
    printf("\n6.Leaves\n");
    scanf("%d",&option);
    getchar();

    while (fscanf(fp, "%d,%[^,],%[^,],%f,%d,%[^,],%d\n",
                  &emp.id, emp.name, emp.gender, &emp.salary,
                  &emp.mobile, emp.address, &emp.leave) == 7) {

        if (emp.id == atoi(string)) {
            flag = 1;
            if(option == 1){
                printf("Current Name: %s\n", emp.name);
                printf("Enter New Name: ");
                fgets(emp.name, sizeof(emp.name), stdin);
                emp.name[strcspn(emp.name, "\n")] = 0;}
            
            else if(option == 2){
                printf("Current Gender: %s\n", emp.gender);
                printf("Enter New Gender: ");
                fgets(emp.gender, sizeof(emp.gender), stdin);
                emp.gender[strcspn(emp.gender, "\n")] = 0;}
             
             else if(option == 3){
                printf("Current Salary: %.2f\n", emp.salary);
                printf("Enter New Salary: ");
                scanf("%f", &emp.salary);}

            else if (option == 4){ 
                printf("Current Mobile: %d\n", emp.mobile);
                printf("Enter New Mobile: ");
                scanf("%d", &emp.mobile);}

            else if (option == 5){
                printf("Current Address: %s\n", emp.address);
                getchar(); 
                printf("Enter New Address: ");
                fgets(emp.address, sizeof(emp.address), stdin);
                emp.address[strcspn(emp.address, "\n")] = 0;}
            
            else if(option == 6){
                printf("Current Leaves: %d\n", emp.leave);
                printf("Enter New Leaves: ");
                scanf("%d", &emp.leave);
                getchar();}

            // printf("Edited successfully.\n");
        }

        // write updated data into temp file
        fprintf(temp, "%d,%s,%s,%.2f,%d,%s,%d\n",
                emp.id, emp.name, emp.gender, emp.salary,
                emp.mobile, emp.address, emp.leave);
    }

    fclose(fp);
    fclose(temp);
    //deleting previous emp.txt & renaming temp.txt to emp.txt
    if (remove("emp.txt") != 0) {
        perror("Failed to remove original file");
    }
    else if (rename("temp.txt", "emp.txt") != 0) {
        perror("Failed to rename temp file");
    }
    else {
        printf("Employee data updated successfully.\n");
    }
    if (flag == 0) {
        printf("Sorry! Employee ID not found.\n");
    }
}


void delete() {
    FILE *fp, *temp;
    char string[15];
    int flag = 0;

    fp = fopen("emp.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Employee ID to delete: ");
    fgets(string, sizeof(string), stdin);
    string[strcspn(string, "\n")] = 0;

    while (fscanf(fp, "%d,%[^,],%[^,],%f,%d,%[^,],%d\n",
                  &emp.id, emp.name, emp.gender, &emp.salary,
                  &emp.mobile, emp.address, &emp.leave) == 7) {

        if (emp.id == atoi(string)) {
            flag = 1;
            printf("Employee with ID %d found and deleted.\n", emp.id);
            continue; // skip writing this record
        }

        // Write other records to temp file
        fprintf(temp, "%d,%s,%s,%.2f,%d,%s,%d\n",
                emp.id, emp.name, emp.gender, emp.salary,
                emp.mobile, emp.address, emp.leave);
    }

    fclose(fp);
    fclose(temp);

    // Replace the original file with the new one
    if (remove("emp.txt") != 0) {
        perror("Failed to remove emp.txt");
    } else if (rename("temp.txt", "emp.txt") != 0) {
        perror("Failed to rename temp.txt to emp.txt");
    } else if (!flag) {
        printf("Employee ID not found.\n");
    }
}

void admin_leave_menu() {
    int id;
    printf("Enter Employee ID to view leave details: ");
    scanf("%d", &id);
    getchar(); // clear newline
    viewLeaveHistory(id);
}

void leave_requests() {
    FILE *pending = fopen("pendingLeaves.txt", "r");
    if (!pending) {
        printf("No pending leave requests found.\n");
        // return;
    }

    // Display all pending leave requests
    int id, days;
    char from[11], to[11];
    printf("\nPending Leave Requests:\n");
    printf("---------------------------------------------------\n");
    printf("ID\tDays\tFrom\t\tTo\n");
    printf("---------------------------------------------------\n");

    // Store data temporarily in memory to reprocess later
    struct Leave {
        int id;
        int days;
        char from[11];
        char to[11];
    } leaves[100];  // Max 100 requests
    int count = 0;

    while (fscanf(pending, "%d %d %s %s", &id, &days, from, to) != EOF && count < 100) {
        leaves[count].id = id;
        leaves[count].days = days;
        strcpy(leaves[count].from, from);
        strcpy(leaves[count].to, to);
        printf("%d\t%d\t%s\t%s\n", id, days, from, to);
        count++;
    }
    fclose(pending);

    if (count == 0) {
        printf("No leave requests found.\n");
        return;
    }

    int target_id;
    char decision;

    printf("\nEnter the Employee ID to process: ");
    scanf("%d", &target_id);
    getchar(); // Clear newline

    int found = 0;

    FILE *temp = fopen("tempPending.txt", "w");
    FILE *approved = fopen("totalLeaves.txt", "a");

    for (int i = 0; i < count; i++) {
        if (leaves[i].id == target_id && !found) {
            found = 1;
            printf("Approve leave for ID %d (%d days, From: %s, To: %s)? (y/n): ",
                   leaves[i].id, leaves[i].days, leaves[i].from, leaves[i].to);
            scanf(" %c", &decision);

            if (decision == 'y' || decision == 'Y') {
                fprintf(approved, "%d %d %s %s\n", leaves[i].id, leaves[i].days, leaves[i].from, leaves[i].to);
                printf("Leave approved and moved to history.\n");
            } else {
                fprintf(temp, "%d %d %s %s\n", leaves[i].id, leaves[i].days, leaves[i].from, leaves[i].to);
                printf("Leave rejected. Kept in pending.\n");
            }
        } else {
            // Keep all other records as-is
            fprintf(temp, "%d %d %s %s\n", leaves[i].id, leaves[i].days, leaves[i].from, leaves[i].to);
        }
    }

    fclose(temp);
    fclose(approved);

    remove("pendingLeaves.txt");
    rename("tempPending.txt", "pendingLeaves.txt");

    if (!found) {
        printf("No request found for ID %d.\n", target_id);
    }
}

void leave_management()
{
    int choice;
    printf("\n Leave Management ");
    printf("\n1. Leave Requests");
    printf("\n2. View Leaves");
    printf("\n3. Exit\n");
    printf("Enter the choice: ");
    scanf("%d", &choice);

    if(choice == 1) leave_requests();
    else if (choice == 2)   admin_leave_menu();
    else if(choice == 3)    admin_panel();
    else    printf("Invalid choice! Please try again.\n");
}

int admin_panel()
{
    int choice;

    while (1) {
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. Search Employee\n");
        printf("3. View All\n");
        printf("4. Edit Data\n");
        printf("5. Remove Data\n");
        printf("6. Leave Management\n");
        printf("7. Complaints\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline left by scanf

        switch (choice) {
            case 1:
                add();
                break;
            case 2:
                search();
                break;
            case 3:
                display();
                break;    
            case 4:
                edit();
                break;
             case 5:
                delete();
                break;
            case 6:
                leave_management();
                break;
            case 7:
                complaint_menu();
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

return 0;
}