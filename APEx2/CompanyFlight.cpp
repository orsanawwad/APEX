#include "CompanyFlight.h"

string CompanyFlight::getID() {
    return ID;
}

int CompanyFlight::getModelNumber() {
    return assignedPlane->getModelNumber();
}

list<Reservation *> CompanyFlight::getReservations() {
    return flightReservation;
}

list<Employee *> CompanyFlight::getAssignedCrew() {
    return assignedEmployees;
}

Date CompanyFlight::getDate() {
    return date;
}

string CompanyFlight::getSource() {
    return origin;
}

string CompanyFlight::getDestination() {
    return destination;
}

Plane *CompanyFlight::getPlane() {
    return assignedPlane;
}


CompanyFlight::CompanyFlight(const string &ID, Plane *assignedPlane,
                             const list<Employee *> &assignedEmployees, const Date &date, const string &origin,
                             const string &destination) : ID(ID), assignedPlane(assignedPlane),
                                                          assignedEmployees(assignedEmployees), date(date),
                                                          origin(origin), destination(destination) {}

void CompanyFlight::addReservation(Reservation* reservation) {
    this->flightReservation.push_front(reservation);
}
