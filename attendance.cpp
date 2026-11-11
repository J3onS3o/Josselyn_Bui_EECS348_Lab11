/***
 * File:         attendance.cpp
 * Author:       Josselyn Bui
 * Date:         11/11/2026
 * Course:       EECS 348 - Software Engineering I
 * Assignment:   Lab 11 - Debugging and Testing
 *
 * Description:  
 * 1. Definition of fault, error state, and failure.
Fault: A fault is a defect, flaw, or mistake in the software’s code, design, or
specification. It represents an error introduced into the system before execution.
In other words, it is a problem caused by the programmer writing incorrect code.
Error (state): An error state occurs when the software enters an incorrect
internal state during execution because a fault has been activated.
Failure: A failure occurs when the software’s external behavior deviates from
the expected outcome, making the issue observable by users or other systems. In
other words, the software produces wrong output.
2. Program to debug
Suppose there is a class that records students’ attendance for each lecture.
Any student who misses three or more lectures will fail the course. There are 10
lectures in total, and for each lecture, attendance is recorded as 1 (present) or 0
(absent). Thus, each student’s attendance is represented by an array of 10 values.
We aim to write a program that checks whether a student fails the course based
on their attendance record.

Questions:
1. Is there a fault in the program? If so, locate it and explain.
2. Define a test case that does not execute the fault. Start from this ques-
tion, if it is possible, you should give the test case (the attendance record
with 10 values), the expected output and the actual output. If impossible,
explains the reason. Besides, you should implement the complete program,
including the functions under test, and verify your inputs along with their
corresponding outputs.
3. Define a test case that executes the fault but does not result in an error
state.
4. Define a test case that results in an error state but not a failure.
5. Define a test case that results in failure.
 *
 * Collaborators: None
 * Sources:       None
 * ***/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function under test
// Extra optional parameter lets main() read the actual absent_count.
bool fail_lecture(const vector<int>& attendance_records, int* count_out = nullptr) {
    int absent_count = 0;
    // FAULT: should start at i = 0, so lecture 1 is skipped
    for (int i = 1; i < attendance_records.size(); ++i) {
        absent_count += attendance_records[i] == 0;
    }
    if (count_out) *count_out = absent_count;
    return absent_count >= 3;
}

// Reference (correct) version, used only to compute expected values
int correct_absent_count(const vector<int>& records) {
    int count = 0;
    for (size_t i = 0; i < records.size(); ++i) {  // starts at 0
        if (records[i] == 0) ++count;
    }
    return count;
}

// run_test: runs one test case and prints the record, expected vs actual
// absence count, and expected vs actual output.
void run_test(const string& name, const vector<int>& records) {
    // Expected values come from the correct reference function
    int expected_count = correct_absent_count(records);
    bool expected_fail = expected_count >= 3;

    // Actual values come from the buggy function; actual_count captures
    // its internal absent_count so we can compare it
    int actual_count = 0;
    bool actual_fail = fail_lecture(records, &actual_count);

    cout << "=== " << name << " ===\n";
    cout << "Attendance record: ";
    for (int v : records) cout << v << ' ';
    cout << "\n";
    cout << "Absent count  - expected: " << expected_count
         << ", actual: " << actual_count << "\n";
    cout << "Output (fail?) - expected: " << (expected_fail ? "true" : "false")
         << ", actual: " << (actual_fail ? "true" : "false") << "\n";

    // Failure = the final output is wrong (expected_fail != actual_fail)
    cout << "absent_count matches: " << (expected_count == actual_count ? "yes" : "no")
        << ", Failure: " << (expected_fail != actual_fail ? "yes" : "no") << "\n\n";
}

int main() {
    // Q4: error state (i starts at 1) but no failure
    run_test("Test 1 (Q4: error state, no failure)", {1, 1, 1, 1, 1, 1, 1, 1, 1, 1});

    // Q5: failure (absence at index 0 is missed, count drops below 3)
    run_test("Test 2 (Q5: failure)", {0, 0, 0, 1, 1, 1, 1, 1, 1, 1});

    return 0;
}