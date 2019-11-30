#ifndef APEX2_COMPANYEMPLOYEE_H
#define APEX2_COMPANYEMPLOYEE_H


#include "interface.h"

/**
 * Employee implementation.
 */
class CompanyEmployee : public Employee {

private:
    string ID;
    Jobs jobType;
    int birthYear;
    Employee* employer;
    int seniorityYears;
public:
    virtual string getID();

    virtual int getSeniority();

    virtual int getBirthYear();

    virtual Employee *getEmployer();

    virtual Jobs getTitle();

    void setEmployer(Employee* employer);

    CompanyEmployee(const string &id, Jobs jobType, int birthYear, Employee *employer, int seniorityYears);
};


#endif //APEX2_COMPANYEMPLOYEE_H
