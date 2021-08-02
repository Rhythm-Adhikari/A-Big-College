#include "prototype.h"
using namespace std;





// Function that returns a single Subject struct from an individual line from the input file
Subject getSubjects(string lines) {
    Subject subject;
    subject.name = lines.substr(0, lines.find(","));
    lines = lines.substr(lines.find(",") + 1, lines.length());

    subject.difficulty = lines.substr(0, lines.find(","));
    lines = lines.substr(lines.find(",") + 1, lines.length());

    subject.variability = lines;

    return subject;
}
// Function that returns a student struct from an individual line from the input file
Student getStudents(string lines) {
    Student student;

    student.name = lines.substr(0, lines.find(","));
    lines = lines.substr(lines.find(",") + 1, lines.length());

    student.Sub_code = lines.substr(0, lines.find(","));
    lines = lines.substr(lines.find(",") + 1, lines.length());

    student.ability = lines.substr(0, lines.find(","));
    lines = lines.substr(lines.find(",") + 1, lines.length());

    student.consistency = lines.substr(0, lines.find(","));
    lines = lines.substr(lines.find(",") + 1, lines.length());

    student.programName = lines.substr(0, lines.find(":"));
    lines = lines.substr(lines.find(":") + 1, lines.length());

    while (lines.find(",") != string::npos) {
        student.subjectList.push_back(lines.substr(0, lines.find(",")));
        lines = lines.substr(lines.find(",") + 1, lines.length());
    }
    student.subjectList.push_back(lines);

    return student;
}

//print subject data stored

void printSubjects(vector<Subject> subjects) {
    for (int i=0;i<subjects.size();i++) {
        cout << subjects[i].name << " " << subjects[i].difficulty << " " << subjects[i].variability;

        cout << endl;
    }
}


// print studnet data stored
void printStudents(vector<Student> students) {
    for (int i=0;i<students.size();i++) {
        cout << students[i].name << " " << students[i].Sub_code << " " << students[i].ability << " " << students[i].consistency << " " << students[i].programName;

        for (int j=0;j<students[i].subjectList.size();j++) {
            cout << " " << students[i].subjectList[j];
        }

        cout << endl;
    }
}


// Generate a random mark based on given parameters
double determineMark(double mean, double standardDeviation) {
    normal_distribution<> normal(mean, standardDeviation);
    default_random_engine randEng;
    randEng.seed(random_device{}());
    double mark = normal(randEng);

    // Ensure mark is between 0 and 100
    if (mark > 100) {
        mark = 100;
    } else if (mark < 0) {
        mark = 0;
    }

    return mark;
}
// determine grade based on mark using the bellow criteria
string determineGrade(double mark) {
    string grade = "F"; // Assume the students are going to fail

    if (mark >= 0 && mark <= 50) {
        grade = "Fail";
    } else if (mark > 50 && mark <= 64) {
        grade = "PASS";
    } else if (mark > 64 && mark <= 85) {
        grade = "Good";
    } else if (mark >= 86 && mark <= 100) {
        grade = "Very Good";
    }

    return grade;
}

