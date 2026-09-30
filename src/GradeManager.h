#ifndef GRADE_MANAGER_H
#define GRADE_MANAGER_H

#include <string>
#include <vector>

#include "Student.h"

class GradeManager {
public:
    Student& addStudent(const std::string& name);
    bool removeStudent(int id);

    Student* findStudent(int id);

    void printAll() const;
    void printRanking() const;
    void printStatistics() const;

    bool saveToFile(const std::string& fileName) const;
    bool loadFromFile(const std::string& fileName);

private:
    std::vector<Student> students;
    int nextId = 1;

    static void printTableHeader();
    static void printStudentRow(const Student& student);
};

#endif
