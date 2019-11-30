#include "SeatReservation.h"

string SeatReservation::getID() {
    return ID;
}

Customer *SeatReservation::getCustomer() {
    return customer;
}

Flight *SeatReservation::getFlight() {
    return flight;
}

Classes SeatReservation::getClass() {
    return seatType;
}

int SeatReservation::getMaxBaggage() {
    return maxAllowedBaggage;
}

SeatReservation::SeatReservation(const string &id, Customer *customer, Flight *flight, Classes seatType,
                                     int maxAllowedBaggage) : ID(id), customer(customer), flight(flight),
                                                              seatType(seatType),
                                                              maxAllowedBaggage(maxAllowedBaggage) {}
