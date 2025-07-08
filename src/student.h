#ifndef STUDENT_H
#define STUDENT_H


#include <string>
#include <vector>
#include <memory>
#include "course.h"
#include "exceptions.h"


class Student {

    private:
        std::string studentID;
        std::string studentName;
        std::vector<Course> courses;

        static const size_t MAX_COURSES = 10;


        bool studentIdCheck(const std::string& id) const;
        bool studentNameCheck(const std::string& name) const;
        void validateStudentData(const std::string& id, const std::string& name) const;
        std::string sanitizeName(const std::string& name) const;

    public:

    Student();
    Student(const std::string& id, const std::string& name);

    Student(const Student& other);
    Student& operator=(const Student& other);

    ~Student() = default;

   
    std::string getStudentID() const;
    std::string getStudentName() const;
    const std::vector<Course>& getCourses() const;
    size_t getCourseCount() const;
    
    void setStudentID(const std::string& id);
    void setStudentName(const std::string& name);
    
    bool addCourse(const Course& course);
    bool removeCourse(const std::string& courseCode);
    const Course* findCourse(const std::string& courseCode) const;
    Course* findCourse(const std::string& courseCode);
    bool hasCourse(const std::string& courseCode) const;
    
    float getOverallAverage() const;
    
    bool operator==(const Student& other) const;
    bool operator!=(const Student& other) const;
    bool operator<(const Student& other) const; 
    
    std::string toString() const;
    std::string getGradeSummary() const;
    
    bool isValid() const;
    void validate() const;
};

#endif


