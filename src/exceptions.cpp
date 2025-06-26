#include "exceptions.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cctype>
#include <student.h>

void FileExcepitonCheck(const std::string& filename) { //handles all file exceptions 
    if (filename.empty()) 
        throw FileEmpty(filename);

    struct stat buffer;
    if (stat(filename.c_str(), &buffer) != 0) //checking the metadata to see if the file exists 
        throw FileNotFoundException(filename);

    std::ifstream file(filename);
    if (!file) //file cannot be opened 
        throw FileAccessException(filename);

    std:: cout << "File has been verified and opened successfully. \n";
};

void CourseCodeExceptionCheck(const std::string& code) { //handles all main course exceptions
    if (code.length() != 5) 
        throw CourseExceptionError(code);
    
    if(!(isalpha(code[0]) && isalpha(code[1]) && isdigit(code[2]) && isdigit(code[3]) && isdigit(code[4]))) 
        throw (CourseExceptionError(code));

    std:: cout << "Course is valid and has been checked successfully. \n";
};

void CourseStudentExceptionCheck(const Student& student) { //handles student course exceptions
    if (student.getCourseCount() > 10)
        throw CheckMaxCourses("Limit Reached for student (" + student.getStudentID() + ")");

    //Once student has implemented an array of courses for a student you can chekc for dupes
    /* Need To-Do: 
    CourseAlreadyExists
    CourseInvalidGrade
    */
};

void GradeExceptionCheck(const float t1, float t2, float t3, float exam) { //checks for valid grades 
    if (t1 > 100 || t1 < 0) 
        throw ValidTest1Grade("Out of Range: " + std::to_string(t1));
    if (t2 > 100 || t2 < 0) 
        throw ValidTest2Grade("Out of Range: " + std::to_string(t2));
    if (t3 > 100 || t3 < 0) 
        throw ValidTest3Grade("Out of Range: " + std::to_string(t3));
    if (exam > 100 || exam < 0) 
        throw ValidFinalExamGrade("Out of Range: " + std::to_string(exam));

    std:: cout << "The grades been checked and verified successfully. \n";
};

void ValidStudentExceptionCheck(const Student& student) { //handles student id exceptions
    if (student.getStudentID().length() > 9) 
        throw ValidateStudentID("The student " + student.getStudentName());

    if (student.getStudentName().empty() || student.getStudentName().length() > 100) 
        throw ValidateName("Student name of (" + student.getStudentID() + ")");

    std:: cout << "The student has been checked and verified successfully. \n";
};