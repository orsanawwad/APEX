#ifndef APEX2_COMPANYFLIGHT_H
#define APEX2_COMPANYFLIGHT_H

#include "interface.h"

/**
 * Flight implementation.
 */
class CompanyFlight : public Flight{
private:
    string ID;
    Plane* assignedPlane;
    list<Reservation*> flightReservation;
    list<Employee*> assignedEmployees;
    Date date;
    string origin;
    string destination;

public:
    virtual string getID();

    virtual int getModelNumber();

    virtual Plane* getPlane();

    virtual list<Reservation *> getReservations();

    virtual list<Employee *> getAssignedCrew();

    virtual Date getDate();

    virtual string getSource();

    virtual string getDestination();

    virtual void addReservation(Reservation* reservation);

    CompanyFlight(const string &ID, Plane *assignedPlane,
                  const list<Employee *> &assignedEmployees, const Date &date, const string &origin,
                  const string &destination);
};


#endif //APEX2_COMPANYFLIGHT_H
