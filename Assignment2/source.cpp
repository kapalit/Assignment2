// Assignment 2 - Debugging vs. Release Coding Practice
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Holds one student's information.
struct STUDENT_DATA
{
    std::string firstName;
    std::string lastName;
};

int main()
{
    std::vector<STUDENT_DATA> students;

    // Each line of the file looks like: Last, First
    std::ifstream file("StudentData.txt");
    std::string line;
    while (std::getline(file, line))
    {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        size_t comma = line.find(',');
        if (comma == std::string::npos)
            continue; // skip blank or malformed lines

        STUDENT_DATA student;
        student.lastName = line.substr(0, comma);
        student.firstName = line.substr(comma + 1);
        if (!student.firstName.empty() && student.firstName[0] == ' ')
            student.firstName.erase(0, 1);

        students.push_back(student);
    }


    return 0;
}
