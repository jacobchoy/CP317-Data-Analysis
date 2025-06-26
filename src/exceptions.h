#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>


class ProjectException : public std:: runtime_error { //main class for exception 
    public: 
        explicit ProjectException(const std::string& message): std:: runtime_error("Project Error: " + message) {}
};

class FileException : public ProjectException { //file exception main 
    public: 
        explicit FileException(const std::string& message): ProjectException("File Error: " + message) {}
};

class CourseException : public ProjectException { //Invalid Course 
    public: 
        explict CourseException(const std::string& message): ProjectException("Course is invalid: " + message) {}
};

class GradeException : public ProjectException { //Invalid Grade 
    public: 
        explicit GradeException(const std::string& message): ProjectException("This is an invalid grade: " + message) {}
};

class FileNotFoundException  : public FileException {  //file not found exception 
    public: 
        explicit FileNotFoundException(const std::string& filename): FileException("File Not Found: " + filename) {}
};

class FileAccessException : public FileException { //cannot access file 
    public: 
        explicit FileAccessException(const std::string& filename): FileException("Cannot access file: " + filename) {}
};

class ValidateStudentID : public ProjectException { //valid student id 
    public: 
        explicit ValidateStudentID(const std::string& message): ProjectException("This is an invalid student ID: " + message) {}
};

class ValidateName : public ProjectException { //valid student name 
    public:
        explicit ValidateName(const std::string& message): ProjectException("This is an invalid student name: " + message) {}
};

class CheckMaxCourses : public ProjectException { //Too many courses per student max=10
    public:
        explicit CheckMaxCourses(const std::string& message): ProjectException("Too many courses for student: " + message) {}
};

class CourseAlreadyExists : public ProjectException { //This course already exists 
    public:
        explicit CourseAlreadyExists(const std::string& message): ProjectException("This course already exists: " + message) {}
};

class CourseInvalidGrade : public ProjectException { //Course has an invalid grade 
    public:
        explicit CourseInvalidGrade(const std::string& message): ProjectException("This course has an invalid grade: " + message) {}
};

class ValidCourseCode : public ProjectException { //Course code is invalid 
    public:
        explicit ValidCourseCode(const std::string& message): ProjectException("This course code is invalid: " + message) {}
};

class ValidTest1Grade : public ProjectException { //Test grade 1 is invalid 
    public:
        explicit ValidTest1Grade(const std::string& message): ProjectException("Test grade 1 is invalid: " + message) {}
};

class ValidTest2Grade : public ProjectException { //Test grade 2 is invalid 
    public:
        explicit ValidTest2Grade(const std::string& message): ProjectException("Test grade 2 is invalid: " + message) {}
};

class ValidTest3Grade : public ProjectException { //Test grade 3 is invalid 
    public:
        explicit ValidTest3Grade(const std::string& message): ProjectException("Test grade 3 is invalid: " + message) {}
};

class ValidFinalExamGrade : public ProjectException { //Exam grade is invalid 
    public:
        explicit ValidFinalExamGrade(const std::string& message): ProjectException("Exam grade is invalid: " + message) {}
};

#endif 