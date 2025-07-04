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
#include "filereader.h"

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
        FileReader nameFile ("../NameFile.txt");
        if (!nameFile.readNameFile(students)){
            std::cerr << "Error: Failed to read NameFile.txt" << std::endl;
            return 1;
        }
        std::cout << "Successfully read " << students.size() << " students" << std::endl;
        
        // Read CourseFile.txt and add courses to students
        std::cout << "Reading CourseFile.txt..." << std::endl;
        FileReader courseFile ("../CourseFile.txt");
        if (!courseFile.readCourseFile(students)) {
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