#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX = 200;

class Student {
public:
    int id;
    string name;
    float marks;

    Student() {
        id = 0;
        name = "";
        marks = 0;
    }

    Student(int id, string name, float marks) {
        this->id = id;
        this->name = name;
        this->marks = marks;
    }

    void display() {
        cout << "ID: " << id
             << " | Name: " << name
             << " | Marks: " << marks
             << endl;
    }
};

Student students[MAX];
int count = 0;
void addStudent() {
    if (count >= MAX) {
        cout << "Storage full. Cannot add more students." << endl;
        return;
    }

    int id;
    string name;
    float marks;

    cout << "Enter ID: ";
    cin >> id;

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            cout << "ID already exists." << endl;
            return;
        }
    }

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Marks: ";
    cin >> marks;

    students[count] = Student(id, name, marks);
    count++;

    cout << "Student added successfully." << endl;
}

void displayAll() {
    if (count == 0) {
        cout << "No records found." << endl;
        return;
    }

    cout << " --- All Students --- " << endl;
    for (int i = 0; i < count; i++) {
        students[i].display();
    }
    cout << "--------------------" << endl;
}

void searchStudent() {
    int id;
    cout << "Enter ID to search: ";
    cin >> id;

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            cout << " Student found:" << endl;
            students[i].display();
            return;
        }
    }

    cout << "Student with ID " << id << " not found." << endl;
}

void deleteStudent() {
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }
            count--;
            cout << "Student deleted successfully." << endl;
            return;
        }
    }

    cout << "Student with ID " << id << " not found." << endl;
}

void saveToFile() {
    ofstream file("students.txt");

    for (int i = 0; i < count; i++) {
        file << students[i].id << "\n"
             << students[i].name << "\n"
             << students[i].marks << "\n";
    }

    file.close();
    cout << "Data saved." << endl;
}

void loadFromFile() {
    ifstream file("students.txt");

    if (!file) return; 

    count = 0;
    while (file >> students[count].id) {
        file.ignore();
        getline(file, students[count].name);
        file >> students[count].marks;
        count++;
    }

    file.close();
}

int main() {
    loadFromFile();

    int choice;

    do {
        cout << " === Student Record System ===" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Display All" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Delete Student" << endl;
        cout << "5. Save & Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent();    break;
            case 2: displayAll();    break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: saveToFile();    break;
            default: cout << "Invalid choice." << endl;
        }

    } while (choice != 5);

    return 0;
}