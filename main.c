#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Patient
{
    int age;
    char name[30];
    char patient_id[6];
    struct Patient *next;
} Patient;

Patient *head = NULL;
Patient *tail = NULL;
Patient *temp;
char *patient_id;

char *generateIDForNewPatient(int age)
{
    static int ID_COUNT = 1001;
    char ageString[3];
    char idString[5];
    patient_id = malloc(7);
    sprintf(idString, "%d", ID_COUNT++);
    sprintf(ageString, "%d", age);
    strcpy(patient_id, idString);
    strcat(patient_id, ageString);
    return patient_id;
}

struct Patient *createPatient(char name[30], int age, char *patient_id)
{
    struct Patient *newPerson = (struct Patient *)malloc(sizeof(struct Patient));
    strcpy(newPerson->name, name);
    strcpy(newPerson->patient_id, patient_id);
    newPerson->age = age;
    newPerson->next = NULL;
    return newPerson;
}

void addPatient(Patient *new_patient)
{
    //if we have no node, we create head and tail node here
    if (head == NULL && tail == NULL)
    {
        head = new_patient;
        tail = new_patient;
    }
    else
    {
        if (new_patient->age >= head->age)
        {
            temp = head;
            head = new_patient;
            new_patient->next = temp;
            return;
        }
        if (new_patient->age <= tail->age)
        {
            tail->next = new_patient;
            tail = new_patient;
        }

        //General Algorithm for implementing Priority Queue based on AGE.
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

struct Patient *callPriorityPatient()
{
    if (head != NULL)
        return head;
    else
        printf("Patient List EMPTY.\n");
    return 0;
}

void printWaitingList()
{
    if (head == NULL)
    {
        printf("Patient List EMPTY.\n");
        return;
    }
    else
    {
        temp = head;
        while (temp->next != NULL)
        {
            printf("%d: %s [ %d ]\n", temp->patient_id, temp->name, temp->age);
            temp = temp->next;
        }
        printf("%d. %s [ %d ]\n", temp->patient_id, temp->name, temp->age);
    }
}

void printMenu()
{
    printf("\nHow may I help you ? \n");
    printf("1. Register New Patient. \n");
    printf("2. Print Patient List.\n");
    printf("3. Call Priority Patient.\n");
    printf("4. Exit Application.\n");
    printf("\nPlease Enter a choice: ");
}

char *registerPatient(char name[30], int age)
{
    char *new_patient_id = malloc(7);
    Patient *newPatient;

    strcpy(new_patient_id, generateIDForNewPatient(age));
    newPatient = createPatient(name, age, new_patient_id);
    addPatient(newPatient);

    return new_patient_id;
}

void nextPatient()
{
    // finding the most priority patient
    Patient *priorityPatient = callPriorityPatient();
    printf("Patient-%s: %s [ %d ] DISCHARGED\n", priorityPatient->patient_id, priorityPatient->name, priorityPatient->age);
    removePriorityPatient();
}

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
            printf("Enter patient's name: ");
            scanf("%s", name);
            printf("Enter patient's age: ");
            scanf("%d", &age);
            patient_id = registerPatient(name, age);
            printf("Patient: %s been registered with ID: %s\n", name, age, patient_id);
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
            printf("Invalid Choice Registered. Please Try Again\n\n");
            break;
        }
    }
    return 0;
}
