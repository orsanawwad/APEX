#ifndef APEX2_COMPANYCORE_H
#define APEX2_COMPANYCORE_H

#include "interface.h"


/**
 * AirLine manager software.
 */
class MyImplementation : public Ex2 {

private:

    map<string, Customer*> customerList;
    map<string, Employee*> employeeList;
    map<Employee*, list<Date>* > employeeSchedule;
    map<string, Plane*> planesList;
    map<Plane*, list<Date>* > planeSchedule;
    map<string, Flight*> flightList;
    map<string, Reservation*> reservationList;

    std::string randomString(std::string::size_type length);
public:

    virtual Employee *addEmployee(int seniority, int birth_year, string employer_id, Jobs title);

    virtual Employee *getEmployee(string id);

    virtual Plane *addPlane(int model_number, map<Jobs, int> crew_needed, map<Classes, int> max_passangers);

    virtual Plane *getPlane(string id);

    virtual Flight *addFlight(int model_number, Date date, string source, string destination);

    virtual Flight *getFlight(string id);

    virtual Customer *addCustomer(string full_name, int priority);

    virtual Customer *getCustomer(string id);

    virtual Reservation *addResevation(string customerId, string flightId, Classes cls, int max_baggage);

    virtual Reservation *getReservation(string id);

    virtual void exit();

    MyImplementation();

};


#endif //APEX2_COMPANYCORE_H
