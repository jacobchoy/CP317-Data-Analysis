#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>


class ProjectException : public std:: runtime_error { //main class for exception 
    public: 
        explicit ProjectException(const std::string& message): std:: runtime_error("Project Error: " + message) {}
};

class FileException : public FileException { //file exception main 
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
        explict ValidateStudentID(const std::string& message): ProjectException("This is an invalid student ID: " + message) {}
};

class ValidateName : public ProjectException { //valid student name 
    public:
        explict ValidateName(const std::string& message): ProjectException("This is an invalid student name: " + message) {}
};

class CheckMaxCourses : public ProjectException { //Too many courses per student max=10
    public:
        explict CheckMaxCourses(const std::string& message): ProjectException("Too many courses for student: " + message) {}
};

class CourseAlreadyExists : public ProjectException { //This course already exists 
    public:
        explict CourseAlreadyExists(const std::string& message): ProjectException("This course already exists: " + message) {}
};

class CourseInvalidGrade : public ProjectException { //Course has an invalid grade 
    public:
        explict CourseInvalidGrade(const std::string& message): ProjectException("This course has an invalid grade: " + message) {}
};

#endif 