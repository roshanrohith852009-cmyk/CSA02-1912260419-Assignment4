#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int day, month, year;
} Date;

typedef struct {
    int systolic, diastolic;
} BloodPressure;

typedef struct {
    char name[50];
    int age;
    char phone[16];
    BloodPressure bp;
    Date visitDate;
} Patient;

int addPatient(Patient patients[], int *count, const Patient *p) {
    if (*count >= MAX) return 0;
    patients[*count] = *p;
    (*count)++;
    return 1;
}

int main(void) {
    Patient patients[MAX] = {0};
    int count = 0;

    Patient p = {"Ravi", 45, "9876543210",
                 {120, 80}, {23, 11, 2026}};

    if (addPatient(patients, &count, &p)) {
        printf("Patient registered successfully\n");
        printf("Name: %s\nAge: %d\nPhone: %s\n",
               patients[0].name, patients[0].age,
               patients[0].phone);
        printf("BP: %d/%d\n",
               patients[0].bp.systolic,
               patients[0].bp.diastolic);
        printf("Visit: %02d/%02d/%04d\n",
               patients[0].visitDate.day,
               patients[0].visitDate.month,
               patients[0].visitDate.year);
    } else {
        printf("Patient limit reached\n");
    }
    return 0;
}
