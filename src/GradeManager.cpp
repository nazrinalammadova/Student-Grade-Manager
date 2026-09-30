#include "GradeManager.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

Student& GradeManager::addStudent(const std::string& name) {
    students.emplace_back(nextId++, name);
    return students.back();
}

bool GradeManager::removeStudent(int id) {
    auto it = std::find_if(students.begin(), students.end(),
                           [id](const Student& s) { return s.getId() == id; });
    if (it == students.end()) {
        return false;
    }
    students.erase(it);
    return true;
}

Student* GradeManager::findStudent(int id) {
    for (Student& student : students) {
        if (student.getId() == id) {
            return &student;
        }
    }
    return nullptr;
}

void GradeManager::printTableHeader() {
    std::cout << std::left << std::setw(5) << "ID"
              << std::setw(25) << "Name"
              << std::setw(10) << "Grades"
              << std::setw(10) << "Average"
              << "Letter" << '\n';
    std::cout << std::string(56, '-') << '\n';
}

void GradeManager::printStudentRow(const Student& student) {
    std::cout << std::left << std::setw(5) << student.getId()
              << std::setw(25) << student.getName()
              << std::setw(10) << student.getGrades().size()
              << std::setw(10) << std::fixed << std::setprecision(2) << student.getAverage()
              << student.getLetterGrade() << '\n';
}

void GradeManager::printAll() const {
    if (students.empty()) {
        std::cout << "No students yet.\n";
        return;
    }
    printTableHeader();
    for (const Student& student : students) {
        printStudentRow(student);
    }
}

void GradeManager::printRanking() const {
    if (students.empty()) {
        std::cout << "No students yet.\n";
        return;
    }

    std::vector<Student> sorted = students;
    std::sort(sorted.begin(), sorted.end(), [](const Student& a, const Student& b) {
        return a.getAverage() > b.getAverage();
    });

    printTableHeader();
    for (const Student& student : sorted) {
        printStudentRow(student);
    }
}

void GradeManager::printStatistics() const {
    if (students.empty()) {
        std::cout << "No students yet.\n";
        return;
    }

    double total = 0.0;
    int passed = 0;
    const Student* best = &students[0];

    for (const Student& student : students) {
        total += student.getAverage();
        if (student.getLetterGrade() != 'F') {
            passed++;
        }
        if (student.getAverage() > best->getAverage()) {
            best = &student;
        }
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Number of students: " << students.size() << '\n';
    std::cout << "Class average:      " << total / students.size() << '\n';
    std::cout << "Passed (A-E):       " << passed << '\n';
    std::cout << "Failed (F):         " << students.size() - passed << '\n';
    std::cout << "Best student:       " << best->getName()
              << " (" << best->getAverage() << ")\n";
}

bool GradeManager::saveToFile(const std::string& fileName) const {
    std::ofstream file(fileName);
    if (!file) {
        return false;
    }

    for (const Student& student : students) {
        file << student.getId() << ';' << student.getName() << ';';
        const std::vector<double>& grades = student.getGrades();
        for (size_t i = 0; i < grades.size(); i++) {
            if (i > 0) {
                file << ',';
            }
            file << grades[i];
        }
        file << '\n';
    }
    return true;
}

bool GradeManager::loadFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        return false;
    }

    students.clear();
    nextId = 1;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream lineStream(line);
        std::string idText, name, gradesText;
        std::getline(lineStream, idText, ';');
        std::getline(lineStream, name, ';');
        std::getline(lineStream, gradesText);

        int id = std::stoi(idText);
        Student student(id, name);

        std::stringstream gradeStream(gradesText);
        std::string gradeText;
        while (std::getline(gradeStream, gradeText, ',')) {
            if (!gradeText.empty()) {
                student.addGrade(std::stod(gradeText));
            }
        }

        students.push_back(student);
        nextId = std::max(nextId, id + 1);
    }
    return true;
}
