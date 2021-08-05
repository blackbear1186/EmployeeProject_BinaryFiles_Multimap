#ifndef __EMPLOYEE_RECORDS__
#define __EMPLOYEE_RECORDS__

#include <iostream>
#include <string>

using namespace std;

struct EMPLOYEE {
    int id;
    string name;
    
    //EMPLOYEE();
    //EMPLOYEE(int newId, string newName) : id{newId}, name{newName}{}
};

class c_EmployeeRecords
{
public:

    c_EmployeeRecords();
    ~c_EmployeeRecords();

    bool inputValidation(int,char*[]);
    void readFile(string);

private:

};

#endif