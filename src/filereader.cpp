#include "filereader.h"
#include "exceptions.h"
#include <iostream>
#include <vector>
#include <sstream>

extern std::string trim(const std::string&);
extern std::vector<std::string> split(const std::string&, char);

FileReader::FileReader() : fileName(""), inputFile() {}

FileReader::FileReader(const std::string& name){
    fileName = name;
    FileExceptionCheck(fileName);           
    inputFile.open(fileName);            
    if (!inputFile.is_open()) {
        throw FileAccessException(fileName);
    }
}

std::string FileReader::getFileName() const{
    return fileName;
}

std::ifstream& FileReader::getFile() {
    return inputFile;
}

void FileReader::setFileName(const std::string& name){
    fileName = name;
}

void FileReader::setFile(const std::string& filename) {
    fileName = filename;
    FileExceptionCheck(filename);
    if (inputFile.is_open()){
        inputFile.close();
    }
    inputFile.open(filename);
    if (!inputFile.is_open()) {
        throw FileAccessException(filename);
    }
}

bool FileReader::readNameFile(std::map<std::string, Student>& students) {
    if (!inputFile.is_open()) {
        std::cerr << "Cannot open file: " << fileName << std::endl;
        return false;
    }
    
    std::string line;
    int lineNumber = 0;
    
    while (std::getline(inputFile, line)) {
        lineNumber++;
        
        if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) {
            continue; // Skip empty lines
        }
        
        try {
            std::vector<std::string> parts = split(line, ',');
            if (parts.size() != 2) {
                std::cerr << "Warning: Invalid format in NameFile.txt at line " << lineNumber 
                         << ": " << line << std::endl;
                continue;
            }
            
            std::string studentID = trim(parts[0]);
            std::string studentName = trim(parts[1]);
            
            if (studentID.empty() || studentName.empty()) {
                std::cerr << "Warning: Empty ID or name in NameFile.txt at line " << lineNumber << std::endl;
                continue;
            }
            
            Student student(studentID, studentName);
            students[studentID] = student;
            
        } catch (const std::exception& e) {
            std::cerr << "Warning: Error processing line " << lineNumber 
                     << " in NameFile.txt: " << e.what() << std::endl;
            continue;
        }
    }
    
    inputFile.close();
    return !students.empty();
}

bool FileReader::readCourseFile(std::map<std::string, Student>& students) {
    if (!inputFile.is_open()) {
        std::cerr << "Cannot open file: " << fileName << std::endl;
        return false;
    }
    
    std::string line;
    int lineNumber = 0;
    int coursesAdded = 0;
    
    while (std::getline(inputFile, line)) {
        lineNumber++;
        
        if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) {
            continue; // Skip empty lines
        }
        
        try {
            std::vector<std::string> parts = split(line, ',');
            if (parts.size() != 6) {
                std::cerr << "Warning: Invalid format in CourseFile.txt at line " << lineNumber 
                         << ": expected 6 fields, got " << parts.size() << std::endl;
                continue;
            }
            
            std::string studentID = trim(parts[0]);
            std::string courseCode = trim(parts[1]);
            float test1 = std::stof(trim(parts[2]));
            float test2 = std::stof(trim(parts[3]));
            float test3 = std::stof(trim(parts[4]));
            float finalExam = std::stof(trim(parts[5]));
            
            // Check if student exists
            auto it = students.find(studentID);
            if (it != students.end()) {
                Course course(courseCode, test1, test2, test3, finalExam);
                it->second.addCourse(course);
                coursesAdded++;
            } else {
                std::cerr << "Warning: Student ID " << studentID 
                         << " not found in NameFile.txt (line " << lineNumber << ")" << std::endl;
            }
            
        } catch (const std::exception& e) {
            std::cerr << "Warning: Error processing line " << lineNumber 
                     << " in CourseFile.txt: " << e.what() << std::endl;
            continue;
        }
    }
    
    inputFile.close();
    std::cout << "Added " << coursesAdded << " courses to students" << std::endl;
    return coursesAdded > 0;
}