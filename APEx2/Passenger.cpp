#include "Passenger.h"


string Passenger::getID() {
    return ID;
}

string Passenger::getFullName() {
    return fullName;
}

int Passenger::getPriority() {
    return priority;
}

list<Reservation *> Passenger::getReservations() {
    return this->reservationList;
}

void Passenger::addReservation(Reservation *reservation) {
    this->reservationList.push_back(reservation);
}


Passenger::Passenger(const string &ID, const string &fullName, int priority)
                    : ID(ID), fullName(fullName), priority(priority) {}
