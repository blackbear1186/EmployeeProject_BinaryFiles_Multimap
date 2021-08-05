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

    int rDepartment;
    int rId;
    char rName[30];

    inputBinaryFile.open(inputFileName, ios::in | ios::binary);
    outputBinaryFile.open(outputFileName, ios:: in | ios::out | ios::binary);

    multimap<int, EMPLOYEE> employeeMap;
    multimap<int, EMPLOYEE>::iterator eIterator;

    EMPLOYEE readInfo;

    if (inputBinaryFile.is_open())
    {
        inputBinaryFile.seekg(ios::beg);
        while (!inputBinaryFile.eof())
        {
            inputBinaryFile.read((char *)&rDepartment, sizeof(int));
            inputBinaryFile.read((char *)&rId, sizeof(int));
            inputBinaryFile.read((char *)rName, 30);

            //cout << department << " " << id << " " << endl;

            readInfo.id = rId;
            readInfo.name = rName;
            employeeMap.insert({rDepartment, {readInfo.id,readInfo.name}});
        }
    }


    outputBinaryFile.seekp(ios::beg);
    EMPLOYEE writtenInfo;
    if (outputBinaryFile.is_open())
    {
        for(eIterator = employeeMap.begin(); eIterator != employeeMap.end();++eIterator){
            EMPLOYEE valuePair = eIterator->second;
            //cout << eIterator->first << " " << valuePair.id << " " << valuePair.name << endl;
            outputBinaryFile.write((char*)&eIterator->first, sizeof(int));
            outputBinaryFile.write((char*)&valuePair.id, sizeof(int));
            outputBinaryFile.write((char*)valuePair.name.c_str(), 30);

        }
        outputBinaryFile.seekg(ios::beg);
        int wDepartment = 0;
        int wId = 0;
        char wName[30];

        while(!outputBinaryFile.eof()){
            outputBinaryFile.read((char*)&wDepartment, sizeof(int));
            outputBinaryFile.read((char*)&wId, sizeof(int));
            outputBinaryFile.read((char*)wName, 30);
            writtenInfo.id = wId;
            writtenInfo.name = wName;
            //cout << wDepartment << " " << writtenInfo.id << " " << writtenInfo.name << endl;

        }
    }


    inputBinaryFile.close();
    outputBinaryFile.close();
}