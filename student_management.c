#include <stdio.h>
#include <string.h>

#define FILE_NAME "students.dat"
#define TEMP_FILE "temp.dat"

struct Student {
    int roll;
    char name[50];
    char course[30];
    float marks;
};

void clearBuffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void readLine(char *buf, int size) {
    fgets(buf, size, stdin);
    buf[strcspn(buf, "\n")] = '\0';
}

int readInt(const char *prompt) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1) {
        clearBuffer();
        printf("Invalid input. %s", prompt);
    }
    clearBuffer();
    return value;
}

float readFloat(const char *prompt) {
    float value;
    printf("%s", prompt);
    while (scanf("%f", &value) != 1) {
        clearBuffer();
        printf("Invalid input. %s", prompt);
    }
    clearBuffer();
    return value;
}

int rollExists(int roll) {
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) return 0;
    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.roll == roll) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void printStudent(const struct Student *s) {
    printf("%-8d %-25s %-20s %.2f\n", s->roll, s->name, s->course, s->marks);
}

void printHeader(void) {
    printf("\n%-8s %-25s %-20s %s\n", "Roll", "Name", "Course", "Marks");
    printf("-------------------------------------------------------------\n");
}

void addStudent(void) {
    struct Student s;
    s.roll = readInt("Enter roll number: ");
    if (rollExists(s.roll)) {
        printf("A student with this roll number already exists.\n");
        return;
    }
    printf("Enter name: ");
    readLine(s.name, sizeof(s.name));
    printf("Enter course: ");
    readLine(s.course, sizeof(s.course));
    s.marks = readFloat("Enter marks: ");

    FILE *fp = fopen(FILE_NAME, "ab");
    if (fp == NULL) {
        printf("Error: could not open file.\n");
        return;
    }
    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("Record added successfully.\n");
}

void displayStudents(void) {
    struct Student s;
    int count = 0;
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }
    printHeader();
    while (fread(&s, sizeof(s), 1, fp) == 1) {
        printStudent(&s);
        count++;
    }
    fclose(fp);
    if (count == 0)
        printf("No records found.\n");
    else
        printf("\nTotal records: %d\n", count);
}

void searchStudent(void) {
    struct Student s;
    int roll = readInt("Enter roll number to search: ");
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }
    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.roll == roll) {
            printHeader();
            printStudent(&s);
            fclose(fp);
            return;
        }
    }
    fclose(fp);
    printf("Student with roll number %d not found.\n", roll);
}

void updateStudent(void) {
    struct Student s;
    int roll = readInt("Enter roll number to update: ");
    FILE *fp = fopen(FILE_NAME, "r+b");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }
    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.roll == roll) {
            printf("Enter new name: ");
            readLine(s.name, sizeof(s.name));
            printf("Enter new course: ");
            readLine(s.course, sizeof(s.course));
            s.marks = readFloat("Enter new marks: ");

            fseek(fp, -(long)sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);
            fclose(fp);
            printf("Record updated successfully.\n");
            return;
        }
    }
    fclose(fp);
    printf("Student with roll number %d not found.\n", roll);
}

void deleteStudent(void) {
    struct Student s;
    int found = 0;
    int roll = readInt("Enter roll number to delete: ");
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }
    FILE *temp = fopen(TEMP_FILE, "wb");
    if (temp == NULL) {
        printf("Error: could not create temporary file.\n");
        fclose(fp);
        return;
    }
    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.roll == roll)
            found = 1;
        else
            fwrite(&s, sizeof(s), 1, temp);
    }
    fclose(fp);
    fclose(temp);

    if (found) {
        remove(FILE_NAME);
        rename(TEMP_FILE, FILE_NAME);
        printf("Record deleted successfully.\n");
    } else {
        remove(TEMP_FILE);
        printf("Student with roll number %d not found.\n", roll);
    }
}

int main(void) {
    int choice;
    do {
        printf("\n===== Student Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);

    return 0;
}
