#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emp_admin.h"
#include "emp_employee.h"

int login(const char *filename, const char *id, const char *password) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening %s\n", filename);
        return 0;
    }

    char file_id[50], file_password[50];
    while (fscanf(file, "%s %s", file_id, file_password) != EOF) {
        if (strcmp(file_id, id) == 0 && strcmp(file_password, password) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int main() {
    char login_id[50];
    char login_password[50];

    printf("===== Welcome to Employee Management System =====\n");
    printf("Enter your ID: ");
    fgets(login_id, sizeof(login_id), stdin);
    login_id[strcspn(login_id, "\n")] = 0;

    printf("Enter your Password: ");
    fgets(login_password, sizeof(login_password), stdin);
    login_password[strcspn(login_password, "\n")] = 0;

    if (login("admin_login.txt", login_id, login_password)) {
        printf("Admin login successful!\n");
        admin_panel();
    } else if (login("employee_login.txt", login_id, login_password)) {
        printf("Employee login successful!\n");
        int numeric_id = atoi(login_id);
        employee_panel(numeric_id);
    } else {
        printf("Invalid ID or Password! Access Denied.\n");
    }

    return 0;
}
