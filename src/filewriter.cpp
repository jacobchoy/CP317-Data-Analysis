#include "filewriter.h"
#include "exceptions.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

extern std::string trim(const std::string&);
extern std::vector<std::string> split(const std::string&, char);

FileWriter::FileWriter() : fileName(""), outputFile() {}

FileWriter::FileWriter(const std::string& name){
    fileName = name;
    FileExceptionCheck(fileName);           
    outputFile.open(fileName);            
    if (!outputFile.is_open()) {
        throw FileAccessException(fileName);
    }
}

std::string FileWriter::getFileName() const{
    return fileName;
}

std::ofstream& FileWriter::getFile() {
    return outputFile;
}

void FileWriter::setFileName(const std::string& name){
    fileName = name;
}

void FileWriter::setFile(const std::string& name) {
    fileName = name;
    FileExceptionCheck(fileName);

    outputFile.open(fileName);
    if (!outputFile.is_open()) {
        throw FileAccessException(fileName);
    }
}

bool FileWriter::writeOutputFile(const std::map<std::string, Student>& students) {
    if (!outputFile.is_open()) {
        std::cerr << "Cannot create output file: " << fileName << std::endl;
        return false;
    }
    
    //write students to output file
    for (const auto& [id, student] : students) {
        const std::vector<Course>& courses = student.getCourses(); 
        for (const auto& course : courses) {
            double final = course.calculateFinalGrade();
            outputFile << student.getStudentID() << ", " << student.getStudentName() << ", " << course.getCourseCode() << ", " << std::fixed << std::setprecision(1) << final << std::endl;
        }
    }
    
    outputFile.close();
    std::cout << "Wrote records to " << fileName << std::endl;
    return true;
}