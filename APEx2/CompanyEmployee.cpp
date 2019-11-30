#include "CompanyEmployee.h"

string CompanyEmployee::getID() {
    return ID;
}

int CompanyEmployee::getSeniority() {
    return seniorityYears;
}

int CompanyEmployee::getBirthYear() {
    return birthYear;
}

Employee *CompanyEmployee::getEmployer() {
    return employer;
}

Jobs CompanyEmployee::getTitle() {
    return jobType;
}

void CompanyEmployee::setEmployer(Employee *employer) {
    this->employer = employer;
}

CompanyEmployee::CompanyEmployee(const string &id, Jobs jobType, int birthYear, Employee *employer,
                                 int seniorityYears) : ID(id), jobType(jobType), birthYear(birthYear),
                                                       employer(employer), seniorityYears(seniorityYears) {}