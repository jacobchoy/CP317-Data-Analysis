#include "student.h"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cctype>
#include "exceptions.h"

// Default constructor
Student::Student() : studentID(""), studentName("") {}

// Parameterized constructor
Student::Student(const std::string& id, const std::string& name) 
    : studentID(id), studentName(name) {
    
    // Sanitize the name
    studentName = sanitizeName(name);

    // Validate inputs
    ValidStudentExceptionCheck(*this);
}

// Copy constructor
Student::Student(const Student& other)
    : studentID(other.studentID), studentName(other.studentName), courses(other.courses) {}

// Assignment operator
Student& Student::operator=(const Student& other) {
    if (this != &other) {
        studentID = other.studentID;
        studentName = other.studentName;
        courses = other.courses;
    }
    return *this;
}

std::string Student::sanitizeName(const std::string& name) const {
    std::string result = name;
    
    // Remove leading/trailing whitespace
    result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    
    result.erase(std::find_if(result.rbegin(), result.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), result.end());
    
    // Replace multiple spaces with single space
    auto new_end = std::unique(result.begin(), result.end(), [](char a, char b) {
        return std::isspace(a) && std::isspace(b);
    });
    result.erase(new_end, result.end());
    
    return result;
}

// Getters
std::string Student::getStudentID() const {
    return studentID;
}

std::string Student::getStudentName() const {
    return studentName;
}

const std::vector<Course>& Student::getCourses() const {
    return courses;
}

size_t Student::getCourseCount() const {
    return courses.size();
}

// Setters
void Student::setStudentID(const std::string& id) {
    try {
        ValidStudentExceptionCheck(Student(id, studentName));  // validate new ID 
        studentID = id;
    } catch (const ValidateStudentID& e) {}
}

void Student::setStudentName(const std::string& name) {
    try {
        ValidStudentExceptionCheck(Student(studentID, name)); // validate new Name
        studentName = sanitizeName(name);
    } catch (const ValidateName& e) {}
}

// Course management
bool Student::addCourse(const Course& course) {
    try {
        CourseStudentExceptionCheck(*this);
        GradeExceptionCheck(course.getTest1(), course.getTest2(), course.getTest3(), course.getFinalExam());
        
        courses.push_back(course);
        return true;
    } catch (const std::exception& e) {return false;}
}

bool Student::removeCourse(const std::string& courseCode) {
    auto it = std::find_if(courses.begin(), courses.end(),
        [&courseCode](const Course& course) {
            return course.getCourseCode() == courseCode;
        });
    
    if (it != courses.end()) {
        courses.erase(it);
        return true;
    }
    
    return false;
}

const Course* Student::findCourse(const std::string& courseCode) const {
    auto it = std::find_if(courses.begin(), courses.end(),
        [&courseCode](const Course& course) {
            return course.getCourseCode() == courseCode;
        });
    
    return (it != courses.end()) ? &(*it) : nullptr;
}

Course* Student::findCourse(const std::string& courseCode) {
    auto it = std::find_if(courses.begin(), courses.end(),
        [&courseCode](const Course& course) {
            return course.getCourseCode() == courseCode;
        });
    
    return (it != courses.end()) ? &(*it) : nullptr;
}

bool Student::hasCourse(const std::string& courseCode) const {
    return findCourse(courseCode) != nullptr;
}

// Grade calculations
float Student::getOverallAverage() const {
    if (courses.empty()) {
        return 0.0f;
    }
    
    float totalGrade = 0.0f;
    for (const auto& course : courses) {
        totalGrade += course.calculateFinalGrade();
    }
    
    return totalGrade / courses.size();
}



// Comparison operators
bool Student::operator==(const Student& other) const {
    return studentID == other.studentID;
}

bool Student::operator!=(const Student& other) const {
    return !(*this == other);
}

bool Student::operator<(const Student& other) const {
    return studentID < other.studentID;
}

// String representation
std::string Student::toString() const {
    std::ostringstream oss;
    oss << "Student ID: " << studentID << "\n"
        << "Name: " << studentName << "\n"
        << "Courses: " << courses.size() << "\n";
    
    if (!courses.empty()) {
        oss << std::fixed << std::setprecision(1);
        oss << "Overall Average: " << getOverallAverage() << "%\n";
    }
    
    return oss.str();
}

std::string Student::getGradeSummary() const {
    if (courses.empty()) {
        return "No courses enrolled";
    }
    
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1);
    
    for (const auto& course : courses) {
        oss << course.getCourseCode() << ": " << course.calculateFinalGrade() << "%\n";
    }
    
    oss << "Overall Average: " << getOverallAverage() << "%";
    return oss.str();
}