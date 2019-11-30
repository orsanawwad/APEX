#ifndef APEX2_FLIGHTRESERVATION_H
#define APEX2_FLIGHTRESERVATION_H

#include "interface.h"

/**
 * Reservation implementation.
 */
class SeatReservation : public Reservation {
private:
    string ID;
    Customer* customer;
    Flight* flight;
    Classes seatType;
    int maxAllowedBaggage;
public:
    virtual string getID();

    virtual Customer *getCustomer();

    virtual Flight *getFlight();

    virtual Classes getClass();

    virtual int getMaxBaggage();

    SeatReservation(const string &id, Customer *customer, Flight *flight, Classes seatType, int maxAllowedBaggage);
};


#endif //APEX2_FLIGHTRESERVATION_H
