#include <iostream>
#include <stdlib.h>
using namespace std;

struct Course {
    int ID;
    struct Course* course;
    struct Course* students;
};

struct Course* start = NULL;


void insertCourse() {
    struct Course* temp = (struct Course*)malloc(sizeof(struct Course));
    cout << "Enter Course ID: ";
    cin >> temp->ID;
    temp->course = NULL;
    temp->students = NULL;
    if (start == NULL) {
        start = temp;
    }
    else {
        struct Course* current = start;
        while (current->course != NULL) {
            current = current->course;
        }
        current->course = temp;
    }
}

void insertStudent() {
    struct Course* temp = (struct Course*)malloc(sizeof(struct Course));
    cout << "Enter Course ID you want to enroll in : ";
    cin >> temp->ID;
    temp->course = NULL;
    temp->students = NULL;
    struct Course* current1 = start;
    while (current1 != NULL)
    {
        if (temp->ID == current1->ID)
        {
            struct Course* temp2 = (struct Course*)malloc(sizeof(struct Course));
            cout << "Enter Student ID: ";
            cin >> temp2->ID;
            temp2->course = NULL;
            temp2->students = NULL;
            struct Course* current = current1;
            while (current->students != NULL) {
                current = current->students;
            }
            current->students = temp2;
            cout << "Student enrolled." << endl;
            break;
        }

        current1 = current1->course;
    }
    if (current1 == NULL) {
        cout << "Course not found " << endl;
    }
}

void printCourse() {
    struct Course* current = start;
    if (current == NULL) {
        cout << "Linked List is empty";
    }
    else {
        while (current != NULL) {
            cout << "Course ID : " << current->ID << endl;
            struct Course* StuCurr = current->students;
            while (StuCurr != NULL)
            {
                cout << "Student ID: " << StuCurr->ID << endl;
                StuCurr = StuCurr->students;
            }

            current = current->course;
        }
    }
}

void delete_Student(int C_id) {
    int S_id;
    struct Course* current = start;
    while (current != NULL)
    {
        if (C_id == current->ID)
        {
            break;
        }
        current = current->course;
    }
    if (current == NULL)
    {
        cout << "course not found!" << endl;
        return;
    }
    cout << "Enter student no.: ";
    cin >> S_id;
    Course* prev = current;
    current = current->students;
    while (current != NULL)
    {
        if (S_id == current->ID) {
            break;
        }
        prev = current;
        current = current->students;
    }
    if (current == NULL)
    {
        cout << "Student Not found!" << endl;
        return;
    }
    prev->students = current->students;
    free(current);
    cout << "Student Deleted" << endl;
}

void Drop_student(int S_id) {
    int a = 0;
    Course* current = start;
    Course* temp = start;
    while (current != NULL)
    {
        temp = temp->course;
        Course* prev = current;
        current = current->students;
        while (current != NULL)
        {
            if (S_id == current->ID) {
                break;
            }
            prev = current;
            current = current->students;
        }
        if (current == NULL)
        {
            continue;
        }
        prev->students = current->students;
        free(current);
        a = 1;
        cout << "Student Deleted" << endl;

        current = temp;
    }
    if (a == 0)
    {
        cout << "Student not found in any course!" << '\n';
    }
}

Course* delete_students(Course* current) {
    Course* temp = current;
    Course* prev = current;
    while (current->students != NULL)
    {
        while (current->students != NULL) {
            prev = current;
            current = current->students;
        }
        prev->students = NULL;
        free(current);
        current = temp;
    }
    return current;
}

void delete_Course(int C_id) {
    Course* prev = start;
    Course* current = start;
    if (C_id == start->ID)
    {
        start = start->course;
        current = delete_students(current);
        free(current);
        cout << "Course deleted..." << endl;
        return;
    }
    while (current != NULL)
    {
        if (C_id == current->ID)
        {
            break;
        }
        prev = current;
        current = current->course;
    }
    if (current == NULL)
    {
        cout << "Course not found!";
        return;
    }
    current = delete_students(current);
    prev->course = current->course;
    free(current);
    cout << "Course deleted..." << '\n';
    
}


int main() {
    while (true) {
        int choice;
        int course;
        int student;
        cout << "Enter your choice (1: Insert Course, 2: Insert Student, 3: Print, 4: delete course, 5: delete student, 6: drop student, 7: exit ): ";
        cin >> choice;

        switch (choice) {
        case 1:
            insertCourse();
            break;
        case 2:
            insertStudent();
            break;
        case 3:
            printCourse();
            break;
        case 4:
            cout << "Enter course no.: ";
            cin >> course;
            delete_Course(course);
            break;
        case 5:
            cout << "Enter course no.: ";
            cin >> course;
            delete_Student(course);
            break;
        case 6:
            cout << "Enter student no.: ";
            cin >> student;
            Drop_student(student);
            break;
        case 7:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice. Please enter a valid choice.\n";
            break;
        }
    }
}