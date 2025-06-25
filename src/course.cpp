// course.cpp - Simplified version with all errors fixed
#include "course.h"
#include <sstream>
#include <iomanip>
#include <string>

// Default constructor
Course::Course() : courseCode(""), test1(0.0f), test2(0.0f), test3(0.0f), finalExam(0.0f) {}

// Parameterized constructor
Course::Course(const std::string& code, float t1, float t2, float t3, float exam)
    : courseCode(code), test1(t1), test2(t2), test3(t3), finalExam(exam) {
    validateInputs(code, t1, t2, t3, exam);
}

// Copy constructor
Course::Course(const Course& other)
    : courseCode(other.courseCode), test1(other.test1), 
      test2(other.test2), test3(other.test3), finalExam(other.finalExam) {}

// Assignment operator
Course& Course::operator=(const Course& other) {
    if (this != &other) {
        courseCode = other.courseCode;
        test1 = other.test1;
        test2 = other.test2;
        test3 = other.test3;
        finalExam = other.finalExam;
    }
    return *this;
}

void Course::validateInputs(const std::string& code, float t1, float t2, float t3, float exam) const {
    if (!isValidCourseCode(code)) {
        throw CourseException("Invalid course code format: " + code);
    }
    
    if (!isValidScore(t1)) {
        std::ostringstream oss;
        oss << t1;
        throw CourseException("Invalid Test 1 score: " + oss.str());
    }
    
    if (!isValidScore(t2)) {
        std::ostringstream oss;
        oss << t2;
        throw CourseException("Invalid Test 2 score: " + oss.str());
    }
    
    if (!isValidScore(t3)) {
        std::ostringstream oss;
        oss << t3;
        throw CourseException("Invalid Test 3 score: " + oss.str());
    }
    
    if (!isValidScore(exam)) {
        std::ostringstream oss;
        oss << exam;
        throw CourseException("Invalid Final Exam score: " + oss.str());
    }
}

bool Course::isValidScore(float score) const {
    // Simple validation 
    if (score != score) return false;  // NaN check (NaN != NaN is always true)
    return score >= 0.0f && score <= 100.0f;
}

bool Course::isValidCourseCode(const std::string& code) const {
    // Check basic length requirements
    if (code.empty() || code.length() < 3 || code.length() > 10) {
        return false;
    }
    
    // Must contain at least one letter and one digit
    bool hasLetter = false;
    bool hasDigit = false;
    
    for (int i = 0; i < static_cast<int>(code.length()); i++) {
        char c = code[i];
        
        // Check if character is a letter (A-Z, a-z)
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            hasLetter = true;
        }
        // Check if character is a digit (0-9)
        else if (c >= '0' && c <= '9') {
            hasDigit = true;
        }
        // If you want to allow some special characters, modify this part
        else if (c == '-' || c == '_' || c == ' ') {
            // Allow these special characters
            continue;
        }
        else {
            return false;  // Reject other special characters
        }
    }
    
    // Final check: must have at least one letter and one digit
    return hasLetter && hasDigit;
}

float Course::calculateFinalGrade() const {
    // CP317 PROJECT REQUIREMENT: (Test1 + Test2 + Test3) × 20% + FinalExam × 40%
    float testTotal = (test1 + test2 + test3) * 0.20f;
    float examPortion = finalExam * 0.40f;
    float finalGrade = testTotal + examPortion;
    
    // Validate result (simple NaN check)
    if (finalGrade != finalGrade) {
        throw GradeException("Grade calculation resulted in invalid value for course: " + courseCode);
    }
    
    // Clamp to valid range [0, 100]
    if (finalGrade < 0.0f) return 0.0f;
    if (finalGrade > 100.0f) return 100.0f;
    return finalGrade;
}

// Getters
std::string Course::getCourseCode() const {
    return courseCode;
}

float Course::getTest1() const {
    return test1;
}

float Course::getTest2() const {
    return test2;
}

float Course::getTest3() const {
    return test3;
}

float Course::getFinalExam() const {
    return finalExam;
}

// Setters with validation
void Course::setCourseCode(const std::string& code) {
    if (!isValidCourseCode(code)) {
        throw CourseException("Invalid course code: " + code);
    }
    courseCode = code;
}

void Course::setTest1(float score) {
    if (!isValidScore(score)) {
        std::ostringstream oss;
        oss << score;
        throw CourseException("Invalid Test 1 score: " + oss.str());
    }
    test1 = score;
}

void Course::setTest2(float score) {
    if (!isValidScore(score)) {
        std::ostringstream oss;
        oss << score;
        throw CourseException("Invalid Test 2 score: " + oss.str());
    }
    test2 = score;
}

void Course::setTest3(float score) {
    if (!isValidScore(score)) {
        std::ostringstream oss;
        oss << score;
        throw CourseException("Invalid Test 3 score: " + oss.str());
    }
    test3 = score;
}

void Course::setFinalExam(float score) {
    if (!isValidScore(score)) {
        std::ostringstream oss;
        oss << score;
        throw CourseException("Invalid Final Exam score: " + oss.str());
    }
    finalExam = score;
}

// Utility methods
float Course::getTestAverage() const {
    return (test1 + test2 + test3) / 3.0f;
}

bool Course::hasValidGrades() const {
    return isValidScore(test1) && isValidScore(test2) && 
           isValidScore(test3) && isValidScore(finalExam);
}

// Comparison operators
bool Course::operator==(const Course& other) const {
    return courseCode == other.courseCode;
}

bool Course::operator!=(const Course& other) const {
    return !(*this == other);
}

// String representation
std::string Course::toString() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1);
    oss << "Course: " << courseCode 
        << " | Tests: " << test1 << ", " << test2 << ", " << test3
        << " | Exam: " << finalExam
        << " | Final Grade: " << calculateFinalGrade();
    return oss.str();
}