#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include "student.h"
#include "course.h"
#include "exceptions.h"

// Function prototypes
bool readNameFile(const std::string& filename, std::map<std::string, Student>& students);
bool readCourseFile(const std::string& filename, std::map<std::string, Student>& students);
bool writeOutputFile(const std::string& filename, const std::map<std::string, Student>& students);
std::vector<std::string> split(const std::string& str, char delimiter);
std::string trim(const std::string& str);

int main() {
    std::cout << "=== CP317 Data Analysis Project ===" << std::endl;
    std::cout << "Reading student data files..." << std::endl;
    
    // Map to store students by ID for quick lookup
    std::map<std::string, Student> students;
    
    try {
        // Read NameFile.txt
        std::cout << "Reading NameFile.txt..." << std::endl;
        if (!readNameFile("NameFile.txt", students)) {
            std::cerr << "Error: Failed to read NameFile.txt" << std::endl;
            return 1;
        }
        std::cout << "Successfully read " << students.size() << " students" << std::endl;
        
        // Read CourseFile.txt and add courses to students
        std::cout << "Reading CourseFile.txt..." << std::endl;
        if (!readCourseFile("CourseFile.txt", students)) {
            std::cerr << "Error: Failed to read CourseFile.txt" << std::endl;
            return 1;
        }
        
        // Count total courses
        int totalCourses = 0;
        for (const auto& [id, student] : students) {
            totalCourses += student.getCourseCount();
        }
        std::cout << "Successfully processed " << totalCourses << " course records" << std::endl;
        
        // Write output file
        std::cout << "Writing Output.txt..." << std::endl;
        if (!writeOutputFile("Output.txt", students)) {
            std::cerr << "Error: Failed to write Output.txt" << std::endl;
            return 1;
        }
        
        std::cout << "✓ Successfully generated Output.txt" << std::endl;
        std::cout << "Processing complete!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

bool readNameFile(const std::string& filename, std::map<std::string, Student>& students) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return false;
    }
    
    std::string line;
    int lineNumber = 0;
    
    while (std::getline(file, line)) {
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
    
    file.close();
    return !students.empty();
}

bool readCourseFile(const std::string& filename, std::map<std::string, Student>& students) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return false;
    }
    
    std::string line;
    int lineNumber = 0;
    int coursesAdded = 0;
    
    while (std::getline(file, line)) {
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
    
    file.close();
    std::cout << "Added " << coursesAdded << " courses to students" << std::endl;
    return coursesAdded > 0;
}

bool writeOutputFile(const std::string& filename, const std::map<std::string, Student>& students) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot create output file: " << filename << std::endl;
        return false;
    }
    
    // Create a vector of all student-course combinations for sorting
    struct StudentCourseRecord {
        std::string studentID;
        std::string studentName;
        std::string courseCode;
        double finalGrade;
    };
    
    std::vector<StudentCourseRecord> records;
    
    // Collect all records
    for (const auto& [id, student] : students) {
        const std::vector<Course>& courses = student.getCourses();
        for (const auto& course : courses) {
            StudentCourseRecord record;
            record.studentID = student.getStudentID();
            record.studentName = student.getStudentName();
            record.courseCode = course.getCourseCode();
            record.finalGrade = course.calculateFinalGrade();
            records.push_back(record);
        }
    }
    
    // Sort by student ID (requirement #7)
    std::sort(records.begin(), records.end(), 
              [](const StudentCourseRecord& a, const StudentCourseRecord& b) {
                  return a.studentID < b.studentID;
              });
    
    // Write records to file
    file << std::fixed << std::setprecision(1);
    for (const auto& record : records) {
        file << record.studentID << ", " 
             << record.studentName << ", " 
             << record.courseCode << ", " 
             << record.finalGrade << std::endl;
    }
    
    file.close();
    std::cout << "Wrote " << records.size() << " records to " << filename << std::endl;
    return true;
}

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}