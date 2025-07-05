#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <sys/stat.h>
#include "filewriter.h"
#include "filereader.h"
#include "exceptions.h"
#include "student.h"
#include "course.h"

// Function prototypes
std::vector<std::string> split(const std::string& str, char delimiter);
std::string trim(const std::string& str);

void testFileExceptionCheck(){
    std::cout<<"--------TESTING FILE EXCEPTION CHECK--------"<<std::endl;
    std::cout<<"\n";

    try{
        std::cout<<"--------Testing Empty File--------"<<std::endl;
        FileExceptionCheck("");
    }
    catch (const FileEmpty& e){
        std::cout<<"PASS: Caught expect FileEmpty " << e.what()<<std::endl;
    }
    catch(...){
        std::cout<<"FAIL: Caught unexpected error"<<std::endl;
    }
    
    std::cout<<"\n";

    try{
        std::cout<<"--------Testing Non-existent File--------"<<std::endl;
        FileExceptionCheck("non_existent.txt");
    }
    catch(const FileNotFoundException& e){
        std::cout<<"PASS: Caught expected FileNotFoundException "<<e.what()<<std::endl;
    }
    catch(...){
         std::cout<<"FAIL: Caught unexpected error"<<std::endl;
    }

    std::cout<<"\n";

    std::string filename = "protected.txt";

    // Simulate protected file
    std::ofstream outfile(filename);
    outfile << "This file will be locked.";
    outfile.close();
    chmod(filename.c_str(), 0000);

    try{
        std::cout<<"--------Testing Not Accessible File--------"<<std::endl;
        FileExceptionCheck(filename);
    }
    catch(const FileAccessException& e){
        std::cout<<"PASS: Caught expected FileAccessException " <<e.what()<<std::endl;
    }
    catch(...){
        std::cout<<"FAIL: Caught unexpected error"<<std::endl;
    }

    std::cout<<"\n";
    std::cout<<"\n";

}

void testCourseCodeExceptionCheck(std::string codes[], int length){
    std::cout<<"--------TESTING COURSE CODE EXCEPTION CHECK--------"<<std::endl;
    std::cout<<"\n";

    try{
        std::cout<<"--------Testing Bad Length--------"<<std::endl;
        CourseCodeExceptionCheck("CP31");
    }
    catch (const CourseExceptionError& e){
        std::cout<<"PASS: Caught expected CourseExceptionError " << e.what() <<std::endl;
    }
    catch(...){
        std::cout<<"FAIL: Caught unexpected error"<<std::endl;
    }

    std::cout<<"\n";
    std::cout<<"--------Testing Incorrect Char--------"<<std::endl;
    for (int x=0;x<length;x++){
        std::cout<<"Code: " <<codes[x]<<std::endl;
        try{
            CourseCodeExceptionCheck(codes[x]);
        }
        catch (const CourseExceptionError& e){
            std::cout<<"\tPASS: Caught expected CourseExceptionError " << e.what() <<std::endl;
        }
        catch(...){
            std::cout<<"\tFAIL: Caught unexpected error"<<std::endl;
        }
    }

    std::cout<<"\n";
    std::cout<<"\n";
}

void testCourseStudentExceptionCheck(std::string codes[]){
    std::cout<<"--------TESTING COURSE STUDENT EXCEPTION CHECK--------"<<std::endl;
    std::cout<<"\n";

    std::cout<<"--------Testing Over Max Courses--------"<<std::endl;
    Student student ("123456789","Alice King");

    try{
        for (int x = 0;x<11;x++){
            Course course (codes[x],90,90,90,90);
            student.addCourse(course);
        }
    }
    catch(const CheckMaxCourses& e){
         std::cout<<"PASS: Caught expected CheckMaxCourses "<< e.what() <<std::endl;
    }
    catch(...){
        std::cout<<"FAIL: Caught unexpected error"<<std::endl;
    }

    std::cout<<"\n";

    std::cout<<"--------Testing Duplicate Courses Added--------"<<std::endl;
    Student s ("123456789", "Freddie Mercury");
    Course c ("CP317", 34.5,50,98,70);
    s.addCourse(c);
    try{
        s.addCourse(c);
        std::cout<<"Number of Courses: "<<s.getCourseCount()<<std::endl;
    }
    catch(const CourseAlreadyExists& e){
        std::cout<<"PASS: Caught expected CourseAlreadyExists "<< e.what() <<std::endl;
    }
    catch(...){
        std::cout<<"FAIL: Caught unexpected error"<<std::endl;
    }

    std::cout<<"\n";

}

void testGradeExceptionCheck(){
    std::cout<<"--------TESTING GRADE EXCEPTION CHECK--------"<<std::endl;
    std::cout<<"\n";

    std::cout<<"--------Testing Invalid t1--------"<<std::endl;
    try{
        GradeExceptionCheck(-1,200,-90,101);
    }
    catch(const ValidTest1Grade& e){
        std::cout<<"PASS: Caught expected ValidTest1Grade "<< e.what() <<std::endl;
    }
    catch(...){
        std::cout<<"FAIL: Caught unexpected error"<<std::endl;
    }

    std::cout<<"\n";
    std::cout<<"--------Testing Invalid t2--------"<<std::endl;
    try{
        GradeExceptionCheck(100,200,-90,101);
    }
    catch(const ValidTest2Grade& e){
        std::cout<<"PASS: Caught expected ValidTest2Grade "<< e.what() <<std::endl;
    }
    catch(...){
        std::cout<<"FAIL: Caught unexpected error"<<std::endl;
    }


    std::cout<<"\n";
    std::cout<<"--------Testing Invalid t3--------"<<std::endl;
    try{
        GradeExceptionCheck(0,6,-90,101);
    }
    catch(const ValidTest3Grade& e){
        std::cout<<"PASS: Caught expected ValidTest3Grade "<< e.what() <<std::endl;
    }
    catch(...){
        std::cout<<"FAIL: Caught unexpected error"<<std::endl;
    }

    std::cout<<"\n";
    std::cout<<"--------Testing Invalid exam--------"<<std::endl;
    try{
        GradeExceptionCheck(50,60,90,101);
    }
    catch(const ValidFinalExamGrade& e){
        std::cout<<"PASS: Caught expected ValidExamGrade "<< e.what() <<std::endl;
    }
    catch(...){
        std::cout<<"FAIL: Caught unexpected error"<<std::endl;
    }


}

int main() {
    //create student objects
    Student students1 [] = {
        {"123456789", "Alice"},
        {"987654321", "Bob"},
        {"555666777", "Charlie"}
    };

    std::string maxCodes[]={
        "CP317", "CP264", "CP164", "CP212", "CP104", "ST230", "PS101", "PS102", "ST259", "CC100", "FS102"
    };


    std::string incorrectCodes[]= {
        "SPP12", "12345", "CP12E", "C1324", "CP3Q1"
    };
    int length = sizeof(incorrectCodes) / sizeof(incorrectCodes[0]);

    testFileExceptionCheck();
    testCourseCodeExceptionCheck(incorrectCodes, length);
    testCourseStudentExceptionCheck(maxCodes);
    testGradeExceptionCheck();


    return 0;
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