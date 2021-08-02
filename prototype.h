#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>
using namespace std;
// Struct that stores subject data
struct Subject {
    std::string name;
    std::string difficulty;
    std::string variability;

};
// Struct that stores student data
struct Student {
    std::string name;
    std::string Sub_code;
    std::string ability;
    std::string consistency;
    std::string programName;
    std::vector<std::string> subjectList;
};
