cpp
#include "student.h"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cctype>

// Default constructor
Student::Student() : studentID(""), studentName("") {}

// Parameterized constructor
Student::Student(const std::string& id, const std::string& name) 
    : studentID(id), studentName(name) {
    
    // ✅ Validate inputs - OFFENSIVE PROGRAMMING
    validateStudentData(id, name);
    
    // Sanitize the name
    studentName = sanitizeName(name);
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

void Student::validateStudentData(const std::string& id, const std::string& name) const {
    if (!isValidStudentID(id)) {
        throw StudentException("Invalid student ID format: " + id);
    }
    
    if (!isValidStudentName(name)) {
        throw StudentException("Invalid student name: " + name);
    }
}

bool Student::isValidStudentID(const std::string& id) const {
    // ✅ CP317 PROJECT: Accept numeric student IDs like 123456789
    if (id.empty() || id.length() < 3 || id.length() > 15) {
        return false;
    }
    
    // Must be all digits as per project examples
    return std::all_of(id.begin(), id.end(), ::isdigit);
}

bool Student::isValidStudentName(const std::string& name) const {
    if (name.empty() || name.length() > 100) {
        return false;
    }
    
    // Name can contain letters, spaces, apostrophes, and hyphens
    return std::all_of(name.begin(), name.end(), [](char c) {
        return std::isalpha(c) || std::isspace(c) || c == '\'' || c == '-';
    });
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
    if (!isValidStudentID(id)) {
        throw StudentException("Invalid student ID: " + id);
    }
    studentID = id;
}

void Student::setStudentName(const std::string& name) {
    if (!isValidStudentName(name)) {
        throw StudentException("Invalid student name: " + name);
    }
    studentName = sanitizeName(name);
}

// Course management
bool Student::addCourse(const Course& course) {
    try {
        // 🔒 Check limits - OFFENSIVE PROGRAMMING
        if (courses.size() >= MAX_COURSES) {
            throw StudentException("Cannot add more courses. Maximum limit (" + 
                                 std::to_string(MAX_COURSES) + ") reached for student " + studentID);
        }
        
        // ✅ Check for duplicates
        if (hasCourse(course.getCourseCode())) {
            throw StudentException("Course " + course.getCourseCode() + 
                                 " already exists for student " + studentID);
        }
        
        // Validate course before adding
        if (!course.hasValidGrades()) {
            throw StudentException("Cannot add course with invalid grades: " + course.getCourseCode());
        }
        
        courses.push_back(course);
        return true;
        
    } catch (const std::exception& e) {
        // Log error but don't throw - return false to indicate failure
        return false;
    }
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
        oss << "Overall Average: " << getOverallAverage() << "%\n"
            << "GPA: " << getGPA() << "/4.0";
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

// Validation
bool Student::isValid() const {
    return isValidStudentID(studentID) && isValidStudentName(studentName);
}

void Student::validate() const {
    validateStudentData(studentID, studentName);
}
