#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATIENT_FILE "patients.txt"
#define DOCTOR_FILE "doctors.txt"

typedef struct {
    char name[50];
    int age;
    char gender[10];
    char contact[15];
    int isInPatient; // 1 for inpatient, 0 for outpatient
} Patient;

typedef struct {
    int id;
    char name[50];
    char specialty[50];
} Doctor;

void printPatientSlip(Patient *p) {
    printf("\n--- Patient Registration Slip ---\n");
    printf("Name: %s\n", p->name);
    printf("Age: %d\n", p->age);
    printf("Gender: %s\n", p->gender);
    printf("Contact: %s\n", p->contact);
    printf("Inpatient: %s\n", p->isInPatient ? "Yes" : "No");
    printf("-----------------------------------\n");
}

void printDoctorSlip(Doctor *d) {
    printf("\n--- Doctor Registration Slip ---\n");
    printf("ID: %d\n", d->id);
    printf("Name: %s\n", d->name);
    printf("Specialty: %s\n", d->specialty);
    printf("-----------------------------------\n");
}

void registerPatient() {
    Patient *p = (Patient *)malloc(sizeof(Patient));
    FILE *file = fopen(PATIENT_FILE, "a");

    if (!file) {
        printf("Error opening patient file!\n");
        free(p);
        return;
    }

    printf("Enter patient name: ");
    scanf("%s", p->name);
    printf("Enter age: ");
    scanf("%d", &p->age);
    printf("Enter gender: ");
    scanf("%s", p->gender);
    printf("Enter contact number: ");
    scanf("%s", p->contact);
    printf("Is the patient an inpatient? (1 for Yes, 0 for No): ");
    scanf("%d", &p->isInPatient);

    fwrite(p, sizeof(Patient), 1, file);
    fclose(file);
    
    printPatientSlip(p); // Print the slip after registration
    free(p); // Free allocated memory
}

void registerDoctor() {
    Doctor *d = (Doctor *)malloc(sizeof(Doctor));
    FILE *file = fopen(DOCTOR_FILE, "a");

    if (!file) {
        printf("Error opening doctor file!\n");
        free(d);
        return;
    }

    printf("Enter doctor ID: ");
    scanf("%d", &d->id);
    printf("Enter doctor name: ");
    scanf("%s", d->name);
    printf("Enter specialty: ");
    scanf("%s", d->specialty);

    fwrite(d, sizeof(Doctor), 1, file);
    fclose(file);
    
    printDoctorSlip(d); // Print the slip after registration
    free(d); // Free allocated memory
}

void searchPatient() {
    char name[50];
    Patient p;
    FILE *file = fopen(PATIENT_FILE, "r");

    if (!file) {
        printf("Error opening patient file!\n");
        return;
    }

    printf("Enter patient name to search: ");
    scanf("%s", name);

    while (fread(&p, sizeof(Patient), 1, file)) {
        if (strcmp(p.name, name) == 0) {
            printf("Patient found:\n");
            printPatientSlip(&p);
            fclose(file);
            return;
        }
    }
    printf("Patient not found!\n");
    fclose(file);
}

void searchDoctor() {
    int id;
    Doctor d;
    FILE *file = fopen(DOCTOR_FILE, "r");

    if (!file) {
        printf("Error opening doctor file!\n");
        return;
    }

    printf("Enter doctor ID to search: ");
    scanf("%d", &id);

    while (fread(&d, sizeof(Doctor), 1, file)) {
        if (d.id == id) {
            printf("Doctor found:\n");
            printDoctorSlip(&d);
            fclose(file);
            return;
        }
    }
    printf("Doctor not found!\n");
    fclose(file);
}

int main() {
    int choice;
    while (1) {
        printf("\n--- Hospital Management System ---\n");
        printf("1. Register Patient\n");
        printf("2. Register Doctor\n");
        printf("3. Search Patient\n");
        printf("4. Search Doctor\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerPatient();
                break;
            case 2:
                registerDoctor();
                break;
            case 3:
                searchPatient();
                break;
            case 4:
                searchDoctor();
                break;
            case 5:
                printf("Exiting the system.\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}