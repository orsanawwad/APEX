#ifndef APEX2_DBENGINE_H
#define APEX2_DBENGINE_H


#include "interface.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


/**
 * DBEngine used for storing and reading files.
 */
class DBEngine {

private:
    /**
     * Read CSV files and return 2D array.
     * @param inputFile file to read.
     * @param shouldSkipHeader if header should from table should be skipped or not.
     * @return 2D array of parsed table;
     */
    vector<vector<string>> parseCSVFile(string inputFile, bool shouldSkipHeader);

public:

    //Each one of the functions takes a map and flushes it to a file.
    void writeCustomersTable(map<string, Customer*> customers);
    void writEmployeesTable(map<string, Employee*> employees);
    void writeEmployeesScheduleTable(map<Employee*, list<Date>* > employeeSchedule);
    void writePlanesTable(map<string, Plane*> planes);
    void writePlanesScheduleTable(map<Plane*, list<Date>* > planesSchedule);
    void writeRequiredCrewTable(map<string, Plane*> planes);
    void writeFlightTable(map<string, Flight*> flights);
    void writeFlightEmployeesTable(map<string, Flight*> flights);
    void writeReservationTable(map<string, Reservation*> reservations);

    //Reads from the saved files (if exist) and
    map<string, Customer*> readCustomersTable();
    map<string, Plane*> readPlanesTable();
    map<string, Employee*> readEmployeesTable();
    map<Plane*, list<Date>* > readPlanesScheduleTable(map<string, Plane*> planeList);
    map<Employee*, list<Date>* > readEmployeesScheduleTable(map<string, Employee*> employeeList);
    map<string, Flight*> readFlightsTable(map<string, Employee*> employeeList, map<string, Plane*> planesList);
    map<string, Reservation*> readReservationTable(map<string, Customer*> customerList, map<string, Flight*> flightsList);
};


#endif //APEX2_DBENGINE_H
