#ifndef COURSE_H
#define COURSE_H

#include <string>
#include "exceptions.h"

// ENCAPSULATION: Course class with private data and controlled access
class Course {
private:
    std::string courseCode;
    float test1, test2, test3, finalExam;
    
public:
    // Constructors
    Course();
    Course(const std::string& code, float t1, float t2, float t3, float exam);
    
    // Copy constructor and assignment operator
    Course(const Course& other);
    Course& operator=(const Course& other);
    
    // Destructor
    ~Course() = default;
    
    // PROJECT REQUIREMENT: Grade calculation
    // Formula: (Test1 + Test2 + Test3) × 20% + FinalExam × 40%
    float calculateFinalGrade() const;
    
    // Getters with validation
    std::string getCourseCode() const;
    float getTest1() const;
    float getTest2() const;
    float getTest3() const;
    float getFinalExam() const;
    
    // Setters with validation
    void setCourseCode(const std::string& code);
    void setTest1(float score);
    void setTest2(float score);
    void setTest3(float score);
    void setFinalExam(float score);
    
    // Utility methods
    float getTestAverage() const;
    
    // Comparison operators
    bool operator==(const Course& other) const;
    bool operator!=(const Course& other) const;
    
    // String representation
    std::string toString() const;
    
private:
    // Validation methods
    void validateInputs(const std::string& code, float t1, float t2, float t3, float exam) const;
};

#endif