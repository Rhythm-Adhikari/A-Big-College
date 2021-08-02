#include "prototype.h"
#include "iostream"
using namespace std;

// Function declarations
Student getStudents(string);
Subject getSubjects(string);
double determineMark(double, double);
string determineGrade(double);
void printStudents(vector<Student>);
void printSubjects(vector<Subject>);

int main(int argc, char* argv[]) {
    // input and output file
    ifstream studentFile;
    ifstream subjectFile;
    ofstream outputFile;
    // open input file and output file
    studentFile.open(argv[1]);
    subjectFile.open(argv[2]);
    outputFile.open(argv[3]);
    // check for the correct argument(3)
    if (argc != 4) {
        cerr << "Incorrect number of arguments" << endl;
        exit(EXIT_FAILURE);
    }
    // check if the file opend correctly
    if (!studentFile.is_open()) {
        cerr << "Student file failed to open" << endl;
        exit(EXIT_FAILURE);
    }
    if (!subjectFile.is_open()) {
        cerr << "Subject file failed to open" << endl;
        exit(EXIT_FAILURE);
    }
    // Create vectors of structs student and subject
    vector<Student> students;
    vector<Subject> subjects;
    string Data;
    while (getline(studentFile, Data)) {
        students.push_back(getStudents(Data));
    }

    while (getline(subjectFile, Data)) {
        subjects.push_back(getSubjects(Data));
    }
    // cout students and subject data from input file
    cout <<"                                                         "<< endl;
    cout <<"###############################################################"<<endl;
    cout <<"###############################################################"<<endl;
    cout << "#########################STUDENTS#############################"<< endl;
    cout <<"                                                         "<< endl;
    printStudents(students);
    cout <<"#########################################################################"<<endl;
    cout << "####################################SUBJECTS############################"<< endl;
    cout <<"                                                         "<< endl;
    printSubjects(subjects);
    cout << "###############################################################################"<< endl;
//runs for each student
    for (int i=0; i < students.size(); i++) {

        // add student to outputfile
        outputFile << "Student: " + students[i].name << endl;

        // cout student name on consol
        cout << "Next student: " + students[i].name << ", " << students[i].programName  << endl;

        // Assume that the student has failed the subject until they have met the criteria to pass
        bool failed = false;
//runs for each subject
        for (int j=0; j < students[i].subjectList.size(); j++) {
            if (failed == false) { // If they have not yet passed the subject

            //initial variable for calculation
                int studentAbility = stoi(students[i].ability);
                int studentConsistency = stoi(students[i].consistency);
                int subjectID = stoi(students[i].subjectList[j]) + 1;
                int subjectDifficulty = stoi(subjects[subjectID].difficulty);
                int subjectVariability = stoi(subjects[subjectID].variability);
                // Calculate mean
                int mean = studentAbility - subjectDifficulty;
                // Calcualte standard deviation
                int standardDeviation = ((studentConsistency) + (subjectVariability));
                // Determine Mark and Grade
                string grade = "Fail";
                int attempts = 0;
                while ((grade == "Fail") && attempts < 3) { // While the subject is failed and the attempt is less than 3
                double mark = determineMark(mean, standardDeviation);
                    // Determine grade from mark.
                    grade = determineGrade(mark);
                    // Print this subject attempt to standard out
                    if (attempts>0) {
                        cout << "    Attempting subject again: " << subjects[subjectID].name << endl;
                    } else {
                        cout << "    Next student subject: " << subjects[subjectID].name << endl;
                    }
                    // Increment subject attempts
                    attempts++;
                    // Add data to output file
                    outputFile << "    Subject: " << subjects[subjectID].name << endl;
                   outputFile << "    Performance: " << round(mark) << "-" << grade << endl;
                    // Output distribution parameters to the output file
                    outputFile << "    Mean: " << mean << endl;
                    outputFile << "    Standard Deviation: " << standardDeviation << endl;
                    outputFile << endl;
                    // If the student has failed 3 times print the following
                    if (attempts > 2 && grade == "Fail") {
                        outputFile << "    Subject failed too many times. Student did not graduate." << endl << endl;
                        cout << "    Subject failed too many times. Student did not graduate." << endl << endl;
                        failed = true;
                    }
                }
            }
        }
        // If the subject has been passed
        if (failed == false) {
            outputFile << "    Successfully graduated." << endl;
            outputFile << endl;
            cout << "    Successfully graduated." << endl;
            cout << endl;
        }
    }
    return 0;
}
