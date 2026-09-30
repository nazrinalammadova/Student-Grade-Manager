#include "Student.h"

#include <stdexcept>

Student::Student(int id, const std::string& name) : id(id), name(name) {}

int Student::getId() const {
    return id;
}

const std::string& Student::getName() const {
    return name;
}

const std::vector<double>& Student::getGrades() const {
    return grades;
}

void Student::addGrade(double grade) {
    if (grade < 0 || grade > 100) {
        throw std::invalid_argument("Grade must be between 0 and 100.");
    }
    grades.push_back(grade);
}

double Student::getAverage() const {
    if (grades.empty()) {
        return 0.0;
    }
    double sum = 0.0;
    for (double grade : grades) {
        sum += grade;
    }
    return sum / grades.size();
}

char Student::getLetterGrade() const {
    double average = getAverage();
    if (average >= 91) return 'A';
    if (average >= 81) return 'B';
    if (average >= 71) return 'C';
    if (average >= 61) return 'D';
    if (average >= 51) return 'E';
    return 'F';
}
