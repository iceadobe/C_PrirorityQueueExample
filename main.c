#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// PATIENT DATA TYPE
typedef struct Patient
{
    int age;
    char name[30];
    char patient_id[7];
    struct Patient *next;
} Patient;

// GLOBAL VARIABLE
Patient *head = NULL;
Patient *tail = NULL;
Patient *temp;

// Algorithm to create patient ID based on patient's AGE.
char *generateIDForNewPatient(int age)
{
    static int ID_COUNT = 1001;
    char ageString[3];
    char idString[5];
    char * patient_id = malloc(7);
    // convert int ID and AGE into String.
    sprintf(idString, "%d", ID_COUNT++);
    sprintf(ageString, "%d", age);

    strcpy(patient_id, idString);
    strcat(patient_id, ageString);
    return patient_id;
}

// Create a New Patient Structure.
struct Patient *createPatient(char name[30], int age, char *patient_id)
{
    struct Patient *newPerson = (struct Patient *)malloc(sizeof(struct Patient));
    strcpy(newPerson->name, name);
    strcpy(newPerson->patient_id, patient_id);
    newPerson->age = age;
    newPerson->next = NULL;
    return newPerson;
}

// Adds an already created Patient into Priority Queue.
// Older patients have higher priority.
void addPatient(Patient *new_patient)
{
    // If Queue is Empty
    if (head == NULL && tail == NULL)
    {
        head = new_patient;
        tail = new_patient;
    }
    else
    {
        // If Age is Higher than the Head's Age.
        if (new_patient->age >= head->age)
        {
            temp = head;
            head = new_patient;
            new_patient->next = temp;
            return;
        }
        // If Age is lower than the Tail's Age.
        if (new_patient->age <= tail->age)
        {
            tail->next = new_patient;
            tail = new_patient;
        }
        //General Algorithm for implementing Priority Queue (based on AGE).
        temp = head;
        while (temp->next != NULL)
        {
            if (new_patient->age > temp->next->age)
            {
                struct Patient *newy;
                newy = temp->next;
                temp->next = new_patient;
                new_patient->next = newy;
                break;
            }
            temp = temp->next;
        }
    }
}

// Removes the priority Node from the Queue. i.e. Eldest Patient.
void removePriorityPatient()
{
    temp = head;
    if (head == NULL)
    {
        printf("Patient List EMPTY.\n");
        return;
    }

    if (head == tail)
    {
        head = NULL;
        tail = NULL;
        return;
    }

    head = temp->next;
    free(temp);
}

// Returns the Details of Eldest patient.
struct Patient *callPriorityPatient()
{
    if (head != NULL)
        return head;
    else
        printf("Patient List EMPTY.\n");
    return NULL;
}

// Prints the List of patients currently in waiting list/queue.
void printWaitingList()
{
    if (head == NULL)
    {
        printf("Patient List EMPTY.\n");
        return;
    }
    else
    {
        // formatting
		printf("\n----------------------------------\n");
		printf("%5s\t%10s\t%5s","ID","NAME","AGE");
        printf("\n----------------------------------\n");
		temp = head;
        while (temp->next != NULL)
        {
            printf(" %-7s\t%-15s\t%3d\n", temp->patient_id, temp->name, temp->age);
            temp = temp->next;
        }
        printf(" %-7s\t%-15s\t%3d\n", temp->patient_id, temp->name, temp->age);
    }
}

// Utility Method for Printing Dispensary Menu.
void printMenu()
{
    printf("\n--------------------------\n");
    printf("1. Register New Patient. \n");
    printf("2. Print Patient List.\n");
    printf("3. Call Priority Patient.\n");
    printf("4. Exit Application.\n");
    printf("--------------------------\n");
    printf("Please Enter a choice: ");
}

// Registers the Patient, and adds them to the Priority Queue, and returns their ID.
char *registerPatient(char name[30], int age)
{
    char *new_patient_id = malloc(7);
    Patient *newPatient;

    strcpy(new_patient_id, generateIDForNewPatient(age));
    newPatient = createPatient(name, age, new_patient_id);
    addPatient(newPatient);

    return new_patient_id;
}

// Clerk uses the Function to call for the top Patient and Remove him/her  from Queue.
void nextPatient()
{
    // finding the most priority patient
    Patient *priorityPatient = callPriorityPatient();
    if(priorityPatient!=NULL){
        printf("Patient-%s: DISCHARGED\n", priorityPatient->patient_id);
        removePriorityPatient();
    }
}


// MAIN CODE STARTS HERE.
int main()
{
    int choice = 0;
    char name[30];
    int age;
    char *patient_id;
    printf("*******************************************\n");
    printf("      Welcome to Dr. Saxena labs           \n");
    printf("*******************************************");

    while (choice != 4)
    {
        printMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            // User Input
            printf("\nEnter patient's name: ");
            scanf("%s", name);
            printf("Enter patient's age: ");
            scanf("%d", &age);
            // Validating user Input.
            if(age <10 || age >99) {
                printf("Only AGE 10-99 allowed");
                break;
            }
            // Registering Patient
            patient_id = registerPatient(name, age);
            printf("\nPatient: \"%s\" registered with ID: |%s|\n", name, patient_id);
            break;
        case 2:
            printWaitingList();
            break;
        case 3:
            nextPatient();
            break;
        case 4:
            printf("Closing Application. All the Patient Data will be lost.\n");
            break;
        default:
            // Handling Invalid Choice entered by user.
            printf("Invalid Choice Registered. Please Try Again\n\n");
            break;
        }
    }
    return 0;
}// Program END.
