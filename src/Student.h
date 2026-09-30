#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

class Student {
public:
    Student(int id, const std::string& name);

    int getId() const;
    const std::string& getName() const;
    const std::vector<double>& getGrades() const;

    void addGrade(double grade);

    double getAverage() const;
    char getLetterGrade() const;

private:
    int id;
    std::string name;
    std::vector<double> grades;
};

#endif
