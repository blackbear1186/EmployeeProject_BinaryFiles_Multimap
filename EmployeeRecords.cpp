#include <iostream>
#include <fstream>
#include <math.h>
#include <sys/stat.h>
#include <exception>
#include <cerrno>
#include <cstring>
#include <string>
#include <map>

#include "EmployeeRecords.h"
#include "customErrorClass.h"

using namespace std;

/*
**    Author: Berlin Johnson
**    Function Purpose:
**    Function Output:
**    Side Effects:
**
*/
c_EmployeeRecords::c_EmployeeRecords()
{
}
/*
**    Author: Berlin Johnson
**    Function Purpose:
**    Function Output:
**    Side Effects:
**
*/
c_EmployeeRecords::~c_EmployeeRecords()
{
}

bool c_EmployeeRecords::inputValidation(int argc, char *argv[])
{

    bool retValue = false;
    struct stat fileInfo;
    string errorString;
    int error;

    if (argc <= 1)
    {
        //throw MyException("ERROR: Command line should have two arguments.");
    }
    error = stat(argv[1], &fileInfo);
    if (0 != error)
    {
        errorString = strerror(errno);
        errorString += ": ";
        errorString += argv[1];
        throw runtime_error(errorString);
    }

    if (0 == fileInfo.st_size)
    {
        errorString += "file is empty: ";
        errorString += argv[1];
        throw runtime_error(errorString);
    }

    retValue = true;

    return retValue;
}

/*
**    Author: Berlin Johnson
**    Function Purpose:
**    Function Output:
**    Side Effects:
**
*/
void c_EmployeeRecords::readFile(string inputFileName)
{

    fstream inputBinaryFile;
    fstream outputBinaryFile;

    int department;
    int id;
    char name[30];

    inputBinaryFile.open(inputFileName, ios::in | ios::binary);
    //outputBinaryFile.open(outputBinaryFile, ios:: in | ios::out | ios::binary);

    multimap<int, EMPLOYEE> employeeMap;
    multimap<int, EMPLOYEE>::iterator eIterator;

    EMPLOYEE emp;

    if (inputBinaryFile.is_open())
    {
        inputBinaryFile.seekg(ios::beg);
        while (!inputBinaryFile.eof())
        {
            inputBinaryFile.read((char *)&department, sizeof(int));
            inputBinaryFile.read((char *)&id, sizeof(int));
            inputBinaryFile.read((char *)name, 30);

            //cout << department << " " << id << " " << endl;

            emp.id = id;
            emp.name = name;
            employeeMap.insert({department, {emp.id,emp.name}});
        }
    }
    for(eIterator = employeeMap.begin(); eIterator != employeeMap.end();++eIterator){
        auto valuePair = eIterator->second;
        cout << eIterator->first << " " << valuePair.id << " " << valuePair.name << endl;
    }

    /*if (outputBinaryFile.is_open())
    {
    }*/

    inputBinaryFile.close();
    outputBinaryFile.close();
}
