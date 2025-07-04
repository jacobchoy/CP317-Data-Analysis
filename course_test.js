// JavaScript simulation of C++ Course class for local testing
// Run with: node course_test.js

class CourseException extends Error {
    constructor(message) {
        super(`Course Error: ${message}`);
        this.name = 'CourseException';
    }
}

class Course {
    constructor(courseCode = "", test1 = 0.0, test2 = 0.0, test3 = 0.0, finalExam = 0.0) {
        if (arguments.length > 1) {
            this.validateInputs(courseCode, test1, test2, test3, finalExam);
        }
        this.courseCode = courseCode;
        this.test1 = test1;
        this.test2 = test2;
        this.test3 = test3;
        this.finalExam = finalExam;
    }

    isValidScore(score) {
        if (isNaN(score)) return false;
        return score >= 0.0 && score <= 100.0;
    }

    isValidCourseCode(code) {
        if (!code || code.length < 3 || code.length > 10) {
            return false;
        }

        let hasLetter = false;
        let hasDigit = false;

        for (let i = 0; i < code.length; i++) {
            const c = code[i];
            
            if (/[A-Za-z]/.test(c)) {
                hasLetter = true;
            } else if (/[0-9]/.test(c)) {
                hasDigit = true;
            } else if (c === '-' || c === '_' || c === ' ') {
                continue;
            } else {
                return false;
            }
        }

        return hasLetter && hasDigit;
    }

    validateInputs(code, t1, t2, t3, exam) {
        if (!this.isValidCourseCode(code)) {
            throw new CourseException(`Invalid course code format: ${code}`);
        }

        if (!this.isValidScore(t1)) {
            throw new CourseException(`Invalid Test 1 score: ${t1}`);
        }

        if (!this.isValidScore(t2)) {
            throw new CourseException(`Invalid Test 2 score: ${t2}`);
        }

        if (!this.isValidScore(t3)) {
            throw new CourseException(`Invalid Test 3 score: ${t3}`);
        }

        if (!this.isValidScore(exam)) {
            throw new CourseException(`Invalid Final Exam score: ${exam}`);
        }
    }

    calculateFinalGrade() {
        const testTotal = (this.test1 + this.test2 + this.test3) * 0.20;
        const examPortion = this.finalExam * 0.40;
        return testTotal + examPortion;
    }

    getCourseCode() { return this.courseCode; }
    getTest1() { return this.test1; }
    getTest2() { return this.test2; }
    getTest3() { return this.test3; }
    getFinalExam() { return this.finalExam; }

    toString() {
        return `Course: ${this.courseCode} | Tests: ${this.test1}, ${this.test2}, ${this.test3} | Exam: ${this.finalExam} | Final Grade: ${this.calculateFinalGrade().toFixed(1)}`;
    }
}

// Test functions
function runTest(testName, testFunction) {
    try {
        const result = testFunction();
        if (result) {
            console.log(`✓ PASS: ${testName}`);
            return true;
        } else {
            console.log(`✗ FAIL: ${testName}`);
            return false;
        }
    } catch (error) {
        console.log(`✗ FAIL: ${testName} - ${error.message}`);
        return false;
    }
}

function main() {
    console.log("=== Course Class JavaScript Test ===\n");
    
    let passCount = 0;
    let totalTests = 0;

    // Test 1: Valid course creation
    if (runTest("Valid course creation", () => {
        const course1 = new Course("CS101", 85.0, 90.0, 78.0, 88.0);
        console.log(`  ${course1.toString()}`);
        return course1.getCourseCode() === "CS101";
    })) passCount++;
    totalTests++;

    // Test 2: Grade calculation
    if (runTest("Grade calculation correct", () => {
        const course2 = new Course("MATH200", 80.0, 85.0, 90.0, 75.0);
        const expected = (80.0 + 85.0 + 90.0) * 0.20 + 75.0 * 0.40;
        const actual = course2.calculateFinalGrade();
        const correct = Math.abs(actual - expected) < 0.01;
        console.log(`  Expected: ${expected}, Got: ${actual}`);
        return correct;
    })) passCount++;
    totalTests++;

    // Test 3: Empty course code should fail
    if (runTest("Empty course code rejection", () => {
        try {
            new Course("", 80.0, 85.0, 90.0, 75.0);
            return false; // Should have thrown
        } catch (error) {
            return error instanceof CourseException;
        }
    })) passCount++;
    totalTests++;

    // Test 4: Negative score should fail
    if (runTest("Negative score rejection", () => {
        try {
            new Course("CS101", -10.0, 85.0, 90.0, 75.0);
            return false; // Should have thrown
        } catch (error) {
            return error instanceof CourseException;
        }
    })) passCount++;
    totalTests++;

    // Test 5: Score too high should fail
    if (runTest("High score rejection", () => {
        try {
            new Course("CS101", 110.0, 85.0, 90.0, 75.0);
            return false; // Should have thrown
        } catch (error) {
            return error instanceof CourseException;
        }
    })) passCount++;
    totalTests++;

    // Test 6: Valid course codes
    if (runTest("Valid course codes accepted", () => {
        try {
            new Course("CS101", 80, 80, 80, 80);
            new Course("MATH200", 80, 80, 80, 80);
            new Course("ENG-101", 80, 80, 80, 80);
            return true;
        } catch (error) {
            return false;
        }
    })) passCount++;
    totalTests++;

    // Test 7: Course code validation details
    if (runTest("Course code validation logic", () => {
        const testCourse = new Course();
        return testCourse.isValidCourseCode("CS101") === true &&
               testCourse.isValidCourseCode("MATH200") === true &&
               testCourse.isValidCourseCode("") === false &&
               testCourse.isValidCourseCode("AB") === false &&
               testCourse.isValidCourseCode("ABC") === false &&
               testCourse.isValidCourseCode("123") === false;
    })) passCount++;
    totalTests++;

    console.log("\n=== Test Results ===");
    console.log(`Passed: ${passCount}/${totalTests} tests`);
    
    if (passCount === totalTests) {
        console.log("🎉 All tests passed!");
    } else {
        console.log("❌ Some tests failed. Check your C++ implementation.");
    }

    // Show some manual calculation examples
    console.log("\n=== Manual Verification Examples ===");
    const example1 = new Course("CS101", 80, 85, 90, 75);
    console.log(`${example1.toString()}`);
    console.log(`Manual calc: (80+85+90)*0.20 + 75*0.40 = ${(80+85+90)*0.20 + 75*0.40}`);
    
    const example2 = new Course("MATH200", 95, 88, 92, 85);
    console.log(`${example2.toString()}`);
    console.log(`Manual calc: (95+88+92)*0.20 + 85*0.40 = ${(95+88+92)*0.20 + 85*0.40}`);
}

main();
