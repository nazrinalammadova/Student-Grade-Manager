#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

#include "GradeManager.h"

const std::string DATA_FILE = "students.txt";

int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Please enter a whole number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double readDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Please enter a number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string readName(const std::string& prompt) {
    std::string name;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, name);
        if (name.empty()) {
            std::cout << "Name cannot be empty.\n";
        } else if (name.find(';') != std::string::npos) {
            std::cout << "The ';' character is not allowed.\n";
        } else {
            return name;
        }
    }
}

void printMenu() {
    std::cout << "\n1. Add student\n"
              << "2. Add grade to student\n"
              << "3. Show all students\n"
              << "4. Show student details\n"
              << "5. Show ranking\n"
              << "6. Show class statistics\n"
              << "7. Remove student\n"
              << "0. Save and exit\n";
}

void addGrade(GradeManager& manager) {
    int id = readInt("Student ID: ");
    Student* student = manager.findStudent(id);
    if (student == nullptr) {
        std::cout << "Student not found.\n";
        return;
    }

    double grade = readDouble("Grade (0-100): ");
    try {
        student->addGrade(grade);
        std::cout << "Grade added to " << student->getName() << ".\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << '\n';
    }
}

void showDetails(GradeManager& manager) {
    int id = readInt("Student ID: ");
    Student* student = manager.findStudent(id);
    if (student == nullptr) {
        std::cout << "Student not found.\n";
        return;
    }

    std::cout << "Name:    " << student->getName() << '\n';
    std::cout << "Grades:  ";
    for (double grade : student->getGrades()) {
        std::cout << grade << ' ';
    }
    std::cout << "\nAverage: " << student->getAverage()
              << " (" << student->getLetterGrade() << ")\n";
}

int main() {
    GradeManager manager;
    if (manager.loadFromFile(DATA_FILE)) {
        std::cout << "Data loaded from " << DATA_FILE << ".\n";
    }

    std::cout << "=== Student Grade Manager ===\n";

    bool running = true;
    while (running) {
        printMenu();
        int choice = readInt("Choose an option: ");

        switch (choice) {
            case 1: {
                std::string name = readName("Student name: ");
                Student& student = manager.addStudent(name);
                std::cout << "Student added with ID " << student.getId() << ".\n";
                break;
            }
            case 2:
                addGrade(manager);
                break;
            case 3:
                manager.printAll();
                break;
            case 4:
                showDetails(manager);
                break;
            case 5:
                manager.printRanking();
                break;
            case 6:
                manager.printStatistics();
                break;
            case 7: {
                int id = readInt("Student ID: ");
                std::cout << (manager.removeStudent(id) ? "Student removed.\n" : "Student not found.\n");
                break;
            }
            case 0:
                running = false;
                break;
            default:
                std::cout << "Unknown option.\n";
        }
    }

    if (manager.saveToFile(DATA_FILE)) {
        std::cout << "Data saved to " << DATA_FILE << ". Goodbye!\n";
    } else {
        std::cout << "Error: could not save data.\n";
    }
    return 0;
}
