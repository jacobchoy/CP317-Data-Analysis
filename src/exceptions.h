#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

// Forward declaration to avoid circular dependency
class Student;

//BASE 

class ProjectException : public std::runtime_error { //main class for exceptions (not files) 
    public: 
        explicit ProjectException(const std::string& message): std:: runtime_error("Project Error: " + message) {}
};

//FILE STUFF 

class FileException : public ProjectException { //file exception main 
    public: 
        explicit FileException(const std::string& message): ProjectException("File Error: " + message) {}
};

class FileEmpty : public ProjectException { //file is empty 
    public: 
        explicit FileEmpty(const std::string& message): ProjectException("File Error: " + message) {}
};

class FileNotFoundException  : public FileException {  //file not found exception 
    public: 
        explicit FileNotFoundException(const std::string& filename): FileException("File Not Found: " + filename) {}
};

class FileAccessException : public FileException { //cannot access file 
    public: 
        explicit FileAccessException(const std::string& filename): FileException("Cannot access file: " + filename) {}
};

//COURSE EXCEPTIONS 

class CourseExceptionError : public ProjectException { //Invalid Course 
    public: 
        explicit CourseExceptionError(const std::string& message): ProjectException("Course is invalid: " + message) {}
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

class CourseException : public ProjectException { //General course exception 
    public:
        explicit CourseException(const std::string& message): ProjectException("Course Error: " + message) {}
};

//GRADE EXCEPTIONS 
class ValidGrade: public ProjectException{
    public:
        explicit ValidGrade(const std::string& message): ProjectException("Grade is invalid: " + message) {}
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

//STUDENT EXCEPTIONS 

class ValidateStudentID : public ProjectException { //invalid student id 
    public: 
        explicit ValidateStudentID(const std::string& message): ProjectException("This is an invalid student ID: " + message) {}
};

class ValidateName : public ProjectException { //invalid student name 
    public:
        explicit ValidateName(const std::string& message): ProjectException("This is an invalid student name: " + message) {}
};

void FileExceptionCheck(const std::string& filename);
void CourseCodeExceptionCheck(const std::string& code);
void CourseStudentExceptionCheck(const Student& student);
void GradeExceptionCheck(const float t1, float t2, float t3, float exam);
void SingleGradeExceptionCheck(const float score);

#endif