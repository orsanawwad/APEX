#ifndef APEX2_PASSENGER_H
#define APEX2_PASSENGER_H


#include "interface.h"

/**
 * Customer implementation.
 *
 * Note that we also assign his own reservations to a list of his own.
 *
 * (Security risk of course, but there's no other way for now...)
 *
 */
class Passenger : public Customer {
private:
    string ID;
    string fullName;
    int priority;
    list<Reservation*> reservationList;
public:
    virtual string getID();

    virtual string getFullName();

    virtual int getPriority();

    virtual list<Reservation *> getReservations();

    void addReservation(Reservation* reservation);

    Passenger(const string &ID, const string &fullName, int priority);
};


#endif //APEX2_PASSENGER_H
