
# Project Description
This is a linked-list implementation of Priority Queue in C programming language.

The program manages a list of Patients.

## Patient Data Type
```c
typedef struct Patient {
    char * patient_id;
    char * name;
    int age;
    struct Patient *next;
}
```

## Allowed Operation
```
User can apply following operation on the Patient priority Queue.
1. Register a Patient
2. Display the Patient Queue
3. Call Priority Patient.
4. Exit the application
```

## Running Guide
```bash
#compile the app
gcc main.c
#permission to the executable
chmod 777 ./a
#execute the application
.\a
```