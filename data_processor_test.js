// JavaScript version to test the complete application logic
// Run with: node data_processor_test.js

const fs = require('fs');

class Course {
    constructor(courseCode = "", test1 = 0.0, test2 = 0.0, test3 = 0.0, finalExam = 0.0) {
        this.courseCode = courseCode;
        this.test1 = test1;
        this.test2 = test2;
        this.test3 = test3;
        this.finalExam = finalExam;
    }

    calculateFinalGrade() {
        // Formula: (Test1+Test2+Test3) × 20% + FinalExam × 40%
        const testTotal = (this.test1 + this.test2 + this.test3) * 0.20;
        const examPortion = this.finalExam * 0.40;
        return testTotal + examPortion;
    }

    getCourseCode() { return this.courseCode; }
}

class Student {
    constructor(studentID = "", studentName = "") {
        this.studentID = studentID;
        this.studentName = studentName;
        this.courses = [];
    }

    addCourse(course) {
        this.courses.push(course);
    }

    getStudentID() { return this.studentID; }
    getStudentName() { return this.studentName; }
    getCourses() { return this.courses; }
}

function readNameFile(filename) {
    try {
        const data = fs.readFileSync(filename, 'utf8');
        const lines = data.split('\n');
        const students = new Map();
        
        console.log(`Reading ${filename}...`);
        
        for (let i = 0; i < lines.length; i++) {
            const line = lines[i].trim();
            if (!line) continue;
            
            const parts = line.split(',').map(part => part.trim());
            if (parts.length !== 2) {
                console.log(`Warning: Invalid format in ${filename} at line ${i + 1}: ${line}`);
                continue;
            }
            
            const [studentID, studentName] = parts;
            if (!studentID || !studentName) {
                console.log(`Warning: Empty ID or name at line ${i + 1}`);
                continue;
            }
            
            students.set(studentID, new Student(studentID, studentName));
        }
        
        console.log(`Successfully read ${students.size} students`);
        return students;
    } catch (error) {
        console.error(`Error reading ${filename}:`, error.message);
        return null;
    }
}

function readCourseFile(filename, students) {
    try {
        const data = fs.readFileSync(filename, 'utf8');
        const lines = data.split('\n');
        let coursesAdded = 0;
        
        console.log(`Reading ${filename}...`);
        
        for (let i = 0; i < lines.length; i++) {
            const line = lines[i].trim();
            if (!line) continue;
            
            const parts = line.split(',').map(part => part.trim());
            if (parts.length !== 6) {
                console.log(`Warning: Invalid format in ${filename} at line ${i + 1}: expected 6 fields, got ${parts.length}`);
                continue;
            }
            
            const [studentID, courseCode, test1Str, test2Str, test3Str, finalExamStr] = parts;
            
            try {
                const test1 = parseFloat(test1Str);
                const test2 = parseFloat(test2Str);
                const test3 = parseFloat(test3Str);
                const finalExam = parseFloat(finalExamStr);
                
                if (students.has(studentID)) {
                    const course = new Course(courseCode, test1, test2, test3, finalExam);
                    students.get(studentID).addCourse(course);
                    coursesAdded++;
                } else {
                    console.log(`Warning: Student ID ${studentID} not found in NameFile.txt (line ${i + 1})`);
                }
            } catch (parseError) {
                console.log(`Warning: Error parsing grades at line ${i + 1}: ${parseError.message}`);
            }
        }
        
        console.log(`Added ${coursesAdded} courses to students`);
        return coursesAdded > 0;
    } catch (error) {
        console.error(`Error reading ${filename}:`, error.message);
        return false;
    }
}

function writeOutputFile(filename, students) {
    try {
        const records = [];
        
        // Collect all student-course records
        for (const [id, student] of students) {
            const courses = student.getCourses();
            for (const course of courses) {
                records.push({
                    studentID: student.getStudentID(),
                    studentName: student.getStudentName(),
                    courseCode: course.getCourseCode(),
                    finalGrade: course.calculateFinalGrade()
                });
            }
        }
        
        // Sort by student ID (requirement #7)
        records.sort((a, b) => a.studentID.localeCompare(b.studentID));
        
        // Write to file
        const output = records.map(record => 
            `${record.studentID}, ${record.studentName}, ${record.courseCode}, ${record.finalGrade.toFixed(1)}`
        ).join('\n');
        
        fs.writeFileSync(filename, output);
        console.log(`Wrote ${records.length} records to ${filename}`);
        
        // Also display first few records
        console.log(`\nFirst 10 records in ${filename}:`);
        for (let i = 0; i < Math.min(10, records.length); i++) {
            const r = records[i];
            console.log(`${r.studentID}, ${r.studentName}, ${r.courseCode}, ${r.finalGrade.toFixed(1)}`);
        }
        
        return true;
    } catch (error) {
        console.error(`Error writing ${filename}:`, error.message);
        return false;
    }
}

function main() {
    console.log("=== CP317 Data Analysis Project (JavaScript Test) ===");
    
    // Read students from NameFile.txt
    const students = readNameFile('NameFile.txt');
    if (!students) {
        console.error("Failed to read NameFile.txt");
        return;
    }
    
    // Read courses from CourseFile.txt
    if (!readCourseFile('CourseFile.txt', students)) {
        console.error("Failed to read CourseFile.txt");
        return;
    }
    
    // Write output
    if (!writeOutputFile('Output.txt', students)) {
        console.error("Failed to write Output.txt");
        return;
    }
    
    console.log("\n✓ Processing complete!");
    
    // Show some statistics
    let totalCourses = 0;
    for (const [id, student] of students) {
        totalCourses += student.getCourses().length;
    }
    
    console.log(`\nStatistics:`);
    console.log(`- Students: ${students.size}`);
    console.log(`- Total course records: ${totalCourses}`);
    
    // Verify grade calculation with an example
    console.log(`\nGrade Calculation Verification:`);
    for (const [id, student] of students) {
        const courses = student.getCourses();
        if (courses.length > 0) {
            const course = courses[0];
            const calculated = course.calculateFinalGrade();
            const manual = (course.test1 + course.test2 + course.test3) * 0.20 + course.finalExam * 0.40;
            console.log(`Student: ${student.getStudentName()}`);
            console.log(`Course: ${course.getCourseCode()}`);
            console.log(`Tests: ${course.test1}, ${course.test2}, ${course.test3}, Exam: ${course.finalExam}`);
            console.log(`Calculated: ${calculated.toFixed(1)}, Manual: ${manual.toFixed(1)}`);
            break;
        }
    }
}

main();
