#include "CompanyPlane.h"

string CompanyPlane::getID() {
    return this->ID;
}

int CompanyPlane::getModelNumber() {
    return this->modelNumber;
}

map<Jobs, int> CompanyPlane::getCrewNeeded() {
    return this->requiredCrew;
}

int CompanyPlane::getMaxFirstClass() {
    return this->firstClassMaxQuantity;
}

int CompanyPlane::getMaxEconomyClass() {
    return this->economyClassMaxQuantity;
}

CompanyPlane::CompanyPlane(
        const string &ID,
        int modelNumber,
        const map<Jobs, int> &requiredCrew,
        const map<Classes, int> &maxPassengers) :
        ID(ID),
        modelNumber(modelNumber),
        requiredCrew(requiredCrew),
        firstClassMaxQuantity(maxPassengers.at(FIRST_CLASS)),
        economyClassMaxQuantity(maxPassengers.at(SECOND_CLASS)) {}