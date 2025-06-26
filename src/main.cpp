#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include "student.h"
#include "course.h"
#include "exceptions.h"

int main(){
    std::ifstream name_file("../NameFile.txt");
    FileExcepitonCheck("../NameFile.txt");  

    std::ifstream course_file("../CourseFile.txt");
    FileExcepitonCheck("../CourseFile.txt");

    std::ofstream output_file("../Output.txt"); 

    std:: map <std::string, Student> students;
    std:: string line;
    //read name file line by line
    while (std:: getline(name_file, line)){
        std:: stringstream ss(line);
        std:: string id, first, last;

        std:: getline(ss, id, ',');
        std:: getline(ss,first,',');
        std:: getline(ss,last,',');
        students[id] = Student(id,first + " " + last);
    }

    //read course file line by line
    while (std::getline(course_file, line)){
        std::stringstream ss (line);
        std:: string id, course, t1_str, t2_str, t3_str, exam_str;
        double t1,t2,t3,exam;

        std::getline(ss,id,',');
        std::getline(ss,course,',');
        std::getline(ss,t1_str, ',');
        std::getline(ss,t2_str, ',');
        std::getline(ss,t3_str, ',');
        std::getline(ss, exam_str, ',');

        //convert string to double
        t1 = std::stod(t1_str);
        t2 = std::stod(t2_str);
        t3 = std::stod(t3_str);
        exam = std::stod(exam_str);

        //create course object
        Course courseObj(course, t1, t2, t3, exam);

        //add course to the correct student
        if (students.find(id) != students.end()){
            students[id].addCourse(courseObj);
        }
    }

    for (const auto& [id, student] : students) {
        const std::vector<Course>& courses = student.getCourses(); 
        for (const auto& course : courses) {
            double final = course.calculateFinalGrade();
            output_file << student.getStudentID() << ", " << student.getStudentName() << ", " << course.getCourseCode() << ", " << final << std::endl;
        }
    }

}