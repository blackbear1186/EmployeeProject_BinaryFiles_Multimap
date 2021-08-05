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
void c_EmployeeRecords::readFile(string inputFileName, string outputFileName)
{

    fstream inputBinaryFile;
    fstream outputBinaryFile;

    int department;
    int id;
    char name[30];

    inputBinaryFile.open(inputFileName, ios::in | ios::binary);
    outputBinaryFile.open(outputFileName, ios:: in | ios::out | ios::binary);

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


    outputBinaryFile.seekp(ios::beg);

    if (outputBinaryFile.is_open())
    {
        for(eIterator = employeeMap.begin(); eIterator != employeeMap.end();++eIterator){
            EMPLOYEE valuePair = eIterator->second;
            //cout << eIterator->first << " " << valuePair.id << " " << valuePair.name << endl;
            outputBinaryFile.write((char*)&eIterator->first, sizeof(int));
            //outputBinaryFile.write((char*)&valuePair.id, sizeof(valuePair.id));
            //outputBinaryFile.write((char*)valuePair.name.c_str(), sizeof(valuePair.name));

        }
        outputBinaryFile.seekg(ios::beg);
        int dep = 0;
        int i = 0;
        char n[30];

        while(!outputBinaryFile.eof()){
            outputBinaryFile.read((char*)&dep, sizeof(int));
            //outputBinaryFile.read((char*)&i, sizeof());
            //outputBinaryFile.read((char*)n, sizeof(EMPLOYEE));
            cout << dep << endl;

        }
    }


    inputBinaryFile.close();
    outputBinaryFile.close();
}
