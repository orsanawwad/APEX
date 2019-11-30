#ifndef APEX2_COMMERCIALPLANE_H
#define APEX2_COMMERCIALPLANE_H


#include "interface.h"

class CompanyPlane : public Plane {
private:
    string ID;
    int modelNumber;
    map<Jobs, int> requiredCrew;
    int firstClassMaxQuantity;
    int economyClassMaxQuantity;
    //List of crew and its count

public:

    virtual string getID();

    virtual int getModelNumber();

    virtual map<Jobs, int> getCrewNeeded();

    virtual int getMaxFirstClass();

    virtual int getMaxEconomyClass();

    CompanyPlane(const string &ID, int modelNumber,
            const map<Jobs, int> &requiredCrew,
            const map<Classes, int> &maxPassengers);
};


#endif //APEX2_COMMERCIALPLANE_H