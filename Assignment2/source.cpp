// Assignment 2 - Debugging vs. Release Coding Practice
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Pre-release switch: keep this line to build the pre-release version,
// comment it out to build the standard version.
#define PRE_RELEASE

// Holds one student's information.
struct STUDENT_DATA
{
    std::string firstName;
    std::string lastName;
#ifdef PRE_RELEASE
    std::string email;
#endif
};

int main()
{
#ifdef PRE_RELEASE
    std::cout << "Running PRE-RELEASE version" << std::endl;
#else
    std::cout << "Running STANDARD version" << std::endl;
#endif

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

#ifdef PRE_RELEASE
    // Pre-release only: read the email addresses (Last, First,email).
    std::ifstream emailFile("StudentData_Emails.txt");
    students.clear();
    while (std::getline(emailFile, line))
    {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        size_t firstComma = line.find(',');
        size_t secondComma = line.find(',', firstComma + 1);
        if (firstComma == std::string::npos || secondComma == std::string::npos)
            continue;

        STUDENT_DATA student;
        student.lastName = line.substr(0, firstComma);
        student.firstName = line.substr(firstComma + 1, secondComma - firstComma - 1);
        if (!student.firstName.empty() && student.firstName[0] == ' ')
            student.firstName.erase(0, 1);
        student.email = line.substr(secondComma + 1);

        students.push_back(student);
    }
#endif

#ifdef _DEBUG
    // Debug builds only: show what was loaded.
    for (const STUDENT_DATA& s : students)
    {
        std::cout << s.firstName << " " << s.lastName;
#ifdef PRE_RELEASE
        std::cout << " " << s.email;
#endif
        std::cout << std::endl;
    }
#endif

    return 0;
}
