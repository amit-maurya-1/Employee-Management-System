CC = gcc
CFLAGS = -Wall

SRCS = login.c emp_admin.c emp_employee.c attendance.c complaint.c leave_management.c
OBJS = $(SRCS:.c=.o)
TARGET = employee_mgmt

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	$(RM) $(OBJS)     

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o $(TARGET)
