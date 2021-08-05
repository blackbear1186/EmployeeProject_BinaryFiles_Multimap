#include <iostream>
#include <fstream>
#include <string>

#include "customErrorClass.h"
#include "EmployeeRecords.h"


using namespace std;

int main(int argc, char *argv[]){

    c_EmployeeRecords employeeData;
    string inputFileName;
    string outputFileName;
    bool retValue = false;

    retValue = employeeData.inputValidation(argc, argv);

    inputFileName = argv[1];
    //outputFileName = argv[2];
    employeeData.readFile(inputFileName);
    


    return 0;
}