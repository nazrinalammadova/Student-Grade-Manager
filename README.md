# Student Grade Manager (C++)

A console application for teachers to manage student grades. It calculates averages and letter grades, shows a ranking and class statistics, and saves all data to a file.

I built this project to practice **C++ classes, the STL and file handling**.

## Features

- Add and remove students
- Add grades (0–100) with input validation
- Automatic average and letter grade (A–F)
- Ranking of students by average
- Class statistics: class average, number of passed/failed students, best student
- Data is saved to `students.txt` on exit and loaded on start

## Grading scale

| Average | Letter |
|---|---|
| 91–100 | A |
| 81–90 | B |
| 71–80 | C |
| 61–70 | D |
| 51–60 | E |
| 0–50 | F |

## Concepts used

- Classes, header (`.h`) and source (`.cpp`) files
- STL: `std::vector`, `std::sort`, `std::find_if`
- Lambda functions
- Pointers and references
- Exceptions (`std::invalid_argument`)
- File I/O with `fstream` and `stringstream`

## Project structure

```
src/
├── main.cpp          # Console menu and input handling
├── Student.h/.cpp    # Student class
└── GradeManager.h/.cpp  # List of students, statistics, saving
```

## How to build and run

Requires a C++17 compiler (g++, clang or MSVC).

```bash
g++ -std=c++17 -Wall -o grade_manager src/*.cpp
./grade_manager
```

## Example

```
Choose an option: 5
ID   Name                     Grades    Average   Letter
--------------------------------------------------------
2    Leyla Aliyeva            3         93.33     A
1    Murad Hasanov            4         78.50     C
3    Aysel Mammadova          2         45.00     F
```

## What I learned

- How to organize C++ code in several files
- How to use STL algorithms instead of writing everything by hand
- How to read and parse data from a text file

## Possible improvements

- Add subjects (each student has grades for different subjects)
- Export the report to a CSV file
