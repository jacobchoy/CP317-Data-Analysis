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

class FileNotFoundException  : public FileException {  //file not found exception 
    public: 
        explicit FileNotFoundException(const std::string& filename): FileException("File Not Found: " + filename) {}
};

class FileAccessException : public FileException { //cannot access file 
    public: 
        explicit FileAccessException(const std::string& filename): FileException("Cannot access file: " + filename) {}
};

class GradeException : public ProjectException {
    public: 
        explicit GradeException(const std::string& message): 
};

#endif 