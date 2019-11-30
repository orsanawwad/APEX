#include "DBEngine.h"
#include "interface.h"
#include "CompanyFlight.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Passenger.h"
#include "CompanyPlane.h"
#include "CompanyEmployee.h"
#include "CompanyFlight.h"
#include "SeatReservation.h"

/**
 * Delimiter used for table.
 */
#define DELIMITER ","

/**
 * DB File names.
 */
#define CUSTOMER_TABLE_FILE "customers_db.csv"
#define EMPLOYEE_TABLE_FILE "employees_db.csv"
#define EMPLOYEE_SCHEDULE_TABLE_FILE "employees_schedule_db.csv"
#define PLANE_TABLE_FILE "planes_db.csv"
#define PLANE_SCHEDULE_TABLE_FILE "planes_schedule_db.csv"
#define REQUIRED_CREW_TABLE_FILE "required_crew_db.csv"
#define FLIGHT_TABLE_FILE "flight_db.csv"
#define FLIGHT_CREW_TABLE_FILE "flight_crew_db.csv"
#define RESERVATION_TABLE_FILE "reservations_db.csv"

void DBEngine::writeCustomersTable(map<string, Customer *> customers) {

    map<string, Customer *>::iterator customersIterator;

    ofstream customerDBFile (CUSTOMER_TABLE_FILE);

    /*
        +------------+
        |            |
        |  Customer  |
        |            |
        +------------+
        |            |
        |  ID        |
        |            |
        |  FullName  |
        |            |
        |  Priority  |
        |            |
        +------------+
     */


    if (customerDBFile.is_open()) {

    //HEADER
    customerDBFile << "ID";
    customerDBFile << DELIMITER;
    customerDBFile << "FULLNAME";
    customerDBFile << DELIMITER;
    customerDBFile << "PRIORITY";
    customerDBFile << endl;

    for (customersIterator = customers.begin(); customersIterator != customers.end() ; ++customersIterator) {
        Customer* currentCustomer = customersIterator->second;

        customerDBFile << currentCustomer->getID();
        customerDBFile << DELIMITER;
        customerDBFile << currentCustomer->getFullName();
        customerDBFile << DELIMITER;
        customerDBFile << currentCustomer->getPriority();
        customerDBFile << endl;

    }

    customerDBFile.close();
    } else {
        throw "Error opening file.";
    }
}

void DBEngine::writEmployeesTable(map<string, Employee *> employees) {

    /*
        +----------------+
        |                |
        |  Employee      |
        |                |
        +----------------+
        |                |
        | ID             |
        |                |
        | JobType        |
        |                |
        | BirthYear      |
        |                |
        | EmployerID     |
        |                |
        | SeniorityYears |
        |                |
        +----------------+
     */

    map<string, Employee *>::iterator employeesIterator;

    ofstream employeeDBFile (EMPLOYEE_TABLE_FILE);

    if (employeeDBFile.is_open()) {

    //HEADER
    employeeDBFile << "ID";
    employeeDBFile << DELIMITER;
    employeeDBFile << "JOB_TYPE";
    employeeDBFile << DELIMITER;
    employeeDBFile << "BIRTH_YEAR";
    employeeDBFile << DELIMITER;
    employeeDBFile << "EMPLOYER_ID";
    employeeDBFile << DELIMITER;
    employeeDBFile << "SENIORITY_YEARS";
    employeeDBFile << endl;

    for (employeesIterator = employees.begin(); employeesIterator != employees.end() ; ++employeesIterator) {
        Employee* currentEmployee = employeesIterator->second;

        employeeDBFile << currentEmployee->getID();
        employeeDBFile << DELIMITER;
        employeeDBFile << currentEmployee->getTitle();
        employeeDBFile << DELIMITER;
        employeeDBFile << currentEmployee->getBirthYear();
        employeeDBFile << DELIMITER;
        if (currentEmployee->getEmployer() == nullptr) {
            employeeDBFile << 0;
        } else {
            employeeDBFile << currentEmployee->getEmployer()->getID();
        }
        employeeDBFile << DELIMITER;
        employeeDBFile << currentEmployee->getSeniority();
        employeeDBFile << endl;

    }

    employeeDBFile.close();

    } else {
        throw "Error opening file.";
    }

}

void DBEngine::writeEmployeesScheduleTable(map<Employee *, list<Date> *> employeeSchedule) {
    map<Employee *, list<Date> *> ::iterator employeeScheduleIterator;

    ofstream employeeScheduleDBFile(EMPLOYEE_SCHEDULE_TABLE_FILE);

    if(employeeScheduleDBFile.is_open()) {

    employeeScheduleDBFile << "EMPLOYEE_ID";
    employeeScheduleDBFile << DELIMITER;
    employeeScheduleDBFile << "DATE";
    employeeScheduleDBFile << endl;

    for (employeeScheduleIterator = employeeSchedule.begin();
    employeeScheduleIterator != employeeSchedule.end();
    ++employeeScheduleIterator) {

        Employee* currentEmployee = employeeScheduleIterator->first;
        list<Date>* currentDates = employeeScheduleIterator->second;

        list<Date>::iterator currentDatesIterator;

        for (currentDatesIterator = currentDates->begin();
        currentDatesIterator != currentDates->end();
        ++currentDatesIterator) {

            Date currentDate = *currentDatesIterator;

            employeeScheduleDBFile << currentEmployee->getID();
            employeeScheduleDBFile << DELIMITER;
            employeeScheduleDBFile << currentDate.getDate();
            employeeScheduleDBFile << endl;

        }

    }

    employeeScheduleDBFile.close();

    } else {
        throw "Error opening file.";
    }

}

void DBEngine::writePlanesTable(map<string, Plane *> planes) {

    /*
        +------------------------+
        |                        |
        |  Plane                 |
        |                        |
        +------------------------+
        |                        |
        |  ID                    |
        |                        |
        |  ModelNumber           |
        |                        |
        |  FirstClassQuantity    |
        |                        |
        |  EconomyClassQuantity  |
        |                        |
        +------------------------+
    */

    map<string, Plane *>::iterator planeIterator;

    ofstream planeDBFile (PLANE_TABLE_FILE);

    if(planeDBFile.is_open()) {

    //HEADER
    planeDBFile << "ID";
    planeDBFile << DELIMITER;
    planeDBFile << "MODEL_NUMBER";
    planeDBFile << DELIMITER;
    planeDBFile << "FIRST_CLASS_QUANTITY";
    planeDBFile << DELIMITER;
    planeDBFile << "ECONOMY_CLASS_QUANTITY";
    planeDBFile << endl;

    for (planeIterator = planes.begin(); planeIterator != planes.end() ; ++planeIterator) {

        Plane* currentPlane = planeIterator->second;

        planeDBFile << currentPlane->getID();
        planeDBFile << DELIMITER;
        planeDBFile << currentPlane->getModelNumber();
        planeDBFile << DELIMITER;
        planeDBFile << currentPlane->getMaxFirstClass();
        planeDBFile << DELIMITER;
        planeDBFile << currentPlane->getMaxEconomyClass();
        planeDBFile << endl;
    }

    planeDBFile.close();

    } else {
        throw "Error opening file.";
    }
}

void DBEngine::writePlanesScheduleTable(map<Plane *, list<Date> *> planesSchedule) {
    map<Plane *, list<Date> *>::iterator planesScheduleIterator;

    ofstream planeScheduleDBFile (PLANE_SCHEDULE_TABLE_FILE);

    if(planeScheduleDBFile.is_open()) {

    planeScheduleDBFile << "PLANE_ID";
    planeScheduleDBFile << DELIMITER;
    planeScheduleDBFile << "DATE";
    planeScheduleDBFile << endl;

    for (planesScheduleIterator = planesSchedule.begin();
    planesScheduleIterator != planesSchedule.end();
    ++planesScheduleIterator) {

        Plane* currentPlane = planesScheduleIterator->first;
        list<Date>* currentDates = planesScheduleIterator->second;

        list<Date>::iterator currentDatesIterator;

        for (currentDatesIterator = currentDates->begin(); currentDatesIterator != currentDates->end(); ++currentDatesIterator) {

            Date currentDate = *currentDatesIterator;

            planeScheduleDBFile << currentPlane->getID();
            planeScheduleDBFile << DELIMITER;
            planeScheduleDBFile << currentDate.getDate();
            planeScheduleDBFile << endl;


        }

    }

    planeScheduleDBFile.close();

    } else {
        throw "Error opening file.";
    }

}


void DBEngine::writeRequiredCrewTable(map<string, Plane *> planes) {

    /*
        +------------------------+
        |                        |
        |  RequiredCrew          |
        |                        |
        +------------------------+
        |                        |
        |  PlaneID               |
        |                        |
        |  Type                  |
        |                        |
        |  Amount                |
        |                        |
        +------------------------+
    */

    map<string, Plane *>::iterator requiredCrewIterator;

    ofstream requiredCrewDBFile (REQUIRED_CREW_TABLE_FILE);

    if(requiredCrewDBFile.is_open()) {

    requiredCrewDBFile << "PLANE_ID";
    requiredCrewDBFile << DELIMITER;
    requiredCrewDBFile << "TYPE";
    requiredCrewDBFile << DELIMITER;
    requiredCrewDBFile << "AMOUNT";
    requiredCrewDBFile << endl;

    for (requiredCrewIterator = planes.begin();
    requiredCrewIterator != planes.end();
    ++requiredCrewIterator) {

        Plane* currentPlane = requiredCrewIterator->second;

        map<Jobs, int> currentRequiredList = currentPlane->getCrewNeeded();

        map<Jobs, int>::iterator currentRequiredListIterator;

        for (currentRequiredListIterator = currentRequiredList.begin();
        currentRequiredListIterator != currentRequiredList.end();
        ++currentRequiredListIterator) {

            Jobs currentJob = currentRequiredListIterator->first;
            int currentJobAmount = currentRequiredListIterator->second;

            requiredCrewDBFile << currentPlane->getID();
            requiredCrewDBFile << DELIMITER;
            requiredCrewDBFile << currentJob;
            requiredCrewDBFile << DELIMITER;
            requiredCrewDBFile << currentJobAmount;
            requiredCrewDBFile << endl;


        }

    }

    requiredCrewDBFile.close();

    } else {
        throw "Error opening file.";
    }

}

void DBEngine::writeFlightTable(map<string, Flight *> flights) {

    /*
        +---------------+
        |               |
        |  Flight       |
        |               |
        +---------------+
        |               |
        |  ID           |
        |               |
        |  PLANE_ID     |
        |               |
        |  DATE         |
        |               |
        |  ORIGIN       |
        |               |
        |  DESTINATION  |
        |               |
        +---------------+
     */

    map<string, Flight*>::iterator flightIterator;

    ofstream flightDBFile (FLIGHT_TABLE_FILE);

    if(flightDBFile.is_open()) {

    flightDBFile << "ID";
    flightDBFile << DELIMITER;
    flightDBFile << "PLANE_ID";
    flightDBFile << DELIMITER;
    flightDBFile << "DATE";
    flightDBFile << DELIMITER;
    flightDBFile << "ORIGIN";
    flightDBFile << DELIMITER;
    flightDBFile << "DESTINATION";
    flightDBFile << endl;

    for (flightIterator = flights.begin(); flightIterator != flights.end(); ++flightIterator) {
        CompanyFlight* currentFlight = (CompanyFlight*)flightIterator->second;

        flightDBFile << currentFlight->getID();
        flightDBFile << DELIMITER;
        flightDBFile << currentFlight->getPlane()->getID();
        flightDBFile << DELIMITER;
        flightDBFile << currentFlight->getDate().getDate();
        flightDBFile << DELIMITER;
        flightDBFile << currentFlight->getSource();
        flightDBFile << DELIMITER;
        flightDBFile << currentFlight->getDestination();
        flightDBFile << endl;

    }

    flightDBFile.close();

    } else {
        throw "Error opening file.";
    }

}

void DBEngine::writeFlightEmployeesTable(map<string, Flight *> flights) {

    /*
        +-------------------+
        |                   |
        |  FlightEmployees  |
        |                   |
        +-------------------+
        |                   |
        |  Flight_ID        |
        |                   |
        |  Employee_ID      |
        |                   |
        +-------------------+
     */

    map<string, Flight*>::iterator flightCrewIterator;

    ofstream flightCrewDBFile (FLIGHT_CREW_TABLE_FILE);

    if(flightCrewDBFile.is_open()) {

    flightCrewDBFile << "FLIGHT_ID";
    flightCrewDBFile << DELIMITER;
    flightCrewDBFile << "EMPLOYEE_ID";
    flightCrewDBFile << endl;

    for (flightCrewIterator = flights.begin(); flightCrewIterator != flights.end(); ++flightCrewIterator) {

        CompanyFlight* currentFlight = (CompanyFlight*)flightCrewIterator->second;


        list<Employee*> currentCrewList = currentFlight->getAssignedCrew();
        list<Employee*>::iterator currentCrewListIterator;

        for (currentCrewListIterator = currentCrewList.begin();
        currentCrewListIterator != currentCrewList.end();
        ++currentCrewListIterator) {

            Employee* currentEmployee = *currentCrewListIterator;

            flightCrewDBFile << currentFlight->getID();
            flightCrewDBFile << DELIMITER;
            flightCrewDBFile << currentEmployee->getID();
            flightCrewDBFile << endl;

        }

    }

    flightCrewDBFile.close();

    } else {
        throw "Error opening file.";
    }

}

void DBEngine::writeReservationTable(map<string, Reservation *> reservations) {

    /*
        +---------------------+
        |                     |
        |  Reservation        |
        |                     |
        +---------------------+
        |                     |
        |  ID                 |
        |                     |
        |  CustomerID         |
        |                     |
        |  FlightID           |
        |                     |
        |  SeatType           |
        |                     |
        |  MaxAllowedBaggage  |
        |                     |
        +---------------------+
     */

    map<string, Reservation*>::iterator reservationIterator;

    ofstream reservationDBFile (RESERVATION_TABLE_FILE);

    if(reservationDBFile.is_open()) {

    reservationDBFile << "ID";
    reservationDBFile << DELIMITER;
    reservationDBFile << "CUSTOMER_ID";
    reservationDBFile << DELIMITER;
    reservationDBFile << "FLIGHT_ID";
    reservationDBFile << DELIMITER;
    reservationDBFile << "SEAT_TYPE";
    reservationDBFile << DELIMITER;
    reservationDBFile << "MAX_ALLOWED_BAGGAGE";
    reservationDBFile << endl;

    for (reservationIterator = reservations.begin(); reservationIterator != reservations.end(); ++reservationIterator) {

        Reservation* currentReservation = reservationIterator->second;

        reservationDBFile << currentReservation->getID();
        reservationDBFile << DELIMITER;
        reservationDBFile << currentReservation->getCustomer()->getID();
        reservationDBFile << DELIMITER;
        reservationDBFile << currentReservation->getFlight()->getID();
        reservationDBFile << DELIMITER;
        reservationDBFile << currentReservation->getClass();
        reservationDBFile << DELIMITER;
        reservationDBFile << currentReservation->getMaxBaggage();
        reservationDBFile << endl;
    }

    reservationDBFile.close();

    } else {
        throw "Error opening file.";
    }

}

map<string, Customer *> DBEngine::readCustomersTable() {

    vector<vector<string>> customerFields = parseCSVFile(CUSTOMER_TABLE_FILE, true);

    map<string, Customer*> customersList;

    if (customerFields.size() <= 0) {
        return customersList;
    }

    for(auto row : customerFields) {
        std::pair<string, Customer*> customer(row[0],new Passenger(row[0],row[1],stoi(row[2])));
        customersList.insert(customer);
    }

    return customersList;
}


map<string, Plane *> DBEngine::readPlanesTable() {
    vector<vector<string>> planesField = parseCSVFile(PLANE_TABLE_FILE, true);
    vector<vector<string>> requiredCrewFields = parseCSVFile(REQUIRED_CREW_TABLE_FILE, true);

    map<string, Plane*> planesList;

    if (planesField.size() <= 0) {
        return planesList;
    }

    for(auto row : planesField) {

        map<Jobs, int> jobsList;
        map<Classes, int> classesList;

        for(auto crewRow: requiredCrewFields) {
            if (row[0] == crewRow[0]) {
                std::pair<Jobs, int> job((Jobs)stoi(crewRow[1]),stoi(crewRow[2]));
                jobsList.insert(job);
            }
        }

        classesList.insert(std::pair<Classes ,int>(FIRST_CLASS,stoi(row[2])));
        classesList.insert(std::pair<Classes ,int>(SECOND_CLASS,stoi(row[3])));

        std::pair<string, Plane*> plane(row[0],new CompanyPlane(row[0],stoi(row[1]),jobsList,classesList));
        planesList.insert(plane);
    }

    return planesList;
}

map<string, Employee *> DBEngine::readEmployeesTable() {
    vector<vector<string>> employeesFields = parseCSVFile(EMPLOYEE_TABLE_FILE, true);

    map<string, Employee *> employeesList;

    if (employeesFields.size() <= 0) {
        return employeesList;
    }

    map<string, string> employeeToEmployer;

    for (auto employeeRow : employeesFields) {

        if (employeeRow[3] != "0") {
            employeeToEmployer.insert({employeeRow[0],employeeRow[3]});
        }
        employeesList.insert(std::pair<string, Employee*>(
                employeeRow[0],
                new CompanyEmployee(employeeRow[0],
                        Jobs(stoi(employeeRow[1])),
                        stoi(employeeRow[2]),
                        NULL,
                        stoi(employeeRow[4])
                        )));
    }

    for(auto employeeToEmployerPair: employeeToEmployer) {
        ((CompanyEmployee*)(employeesList[employeeToEmployerPair.first]))->
        setEmployer(employeesList[employeeToEmployerPair.second]);
    }

    return employeesList;
}

map<Plane *, list<Date> *> DBEngine::readPlanesScheduleTable(map<string, Plane*> planeList) {

    vector<vector<string>> planeScheduleFields = parseCSVFile(PLANE_SCHEDULE_TABLE_FILE, true);

    map<Plane *, list<Date> *> planeScheduleList;

    if (planeScheduleFields.size() <= 0) {

        if (planeList.size() <= 0) {
            return planeScheduleList;
        } else {

            for(auto plane : planeList) {
                planeScheduleList[plane.second] = new list<Date>;
            }

            return planeScheduleList;

        }
    }

    for (auto currentPlane : planeList) {
        for(auto planeScheduleRow : planeScheduleFields) {

            if (currentPlane.second->getID() == planeScheduleRow[0]) {

                list<Date>* dates;

                if (planeScheduleList.count(currentPlane.second) > 0) {
                    dates = planeScheduleList[currentPlane.second];
                } else {
                    planeScheduleList[currentPlane.second] = new list<Date>;
                    dates = planeScheduleList[currentPlane.second];
                }
                dates->push_back(Date(planeScheduleRow[1]));
            } else {
                if (planeScheduleList.count(currentPlane.second) > 0) {
                } else {
                    planeScheduleList[currentPlane.second] = new list<Date>;
                }
            }

        }
    }

    return planeScheduleList;
}

map<Employee *, list<Date> *> DBEngine::readEmployeesScheduleTable(map<string, Employee *> employeeList) {

    vector<vector<string>> employeeScheduleFields = parseCSVFile(EMPLOYEE_SCHEDULE_TABLE_FILE, true);

    map<Employee *, list<Date> *> employeeScheduleList;

    if (employeeScheduleFields.size() <= 0) {

        if (employeeList.size() <= 0) {
            return employeeScheduleList;
        } else {

            for(auto employee : employeeList) {
                employeeScheduleList[employee.second] = new list<Date>;
            }

            return employeeScheduleList;

        }

    }


    for (auto currentEmployee : employeeList) {
        for(auto employeeScheduleRow : employeeScheduleFields) {

            if (currentEmployee.second->getID() == employeeScheduleRow[0]) {

                list<Date>* dates;

                if (employeeScheduleList.count(currentEmployee.second) > 0) {
                    dates = employeeScheduleList[currentEmployee.second];
                } else {
                    employeeScheduleList[currentEmployee.second] = new list<Date>;
                    dates = employeeScheduleList[currentEmployee.second];
                }
                dates->push_back(Date(employeeScheduleRow[1]));
            } else {
                if (employeeScheduleList.count(currentEmployee.second) > 0) {
                } else {
                    employeeScheduleList[currentEmployee.second] = new list<Date>;
                }
            }

        }
    }

    return employeeScheduleList;
}

map<string, Flight*> DBEngine::readFlightsTable(map<string, Employee *> employeeList, map<string, Plane*> planesList) {

    vector<vector<string>> flightsTable = parseCSVFile(FLIGHT_TABLE_FILE, true);
    vector<vector<string>> employeesForFlightsTable = parseCSVFile(FLIGHT_CREW_TABLE_FILE, true);

    map<string, Flight*> flightsList;

    if (flightsTable.size() <= 0) {
        return flightsList;
    }

    for (auto flightRow : flightsTable) {

        list<Employee*> flightEmployees;

        for (auto employeeRow : employeesForFlightsTable) {

            if (flightRow[0] == employeeRow[0]) {
                flightEmployees.push_back(employeeList[employeeRow[1]]);
            }

        }


        Flight* flight = new CompanyFlight(
                flightRow[0],
                planesList[flightRow[1]],
                flightEmployees,
                Date(flightRow[2]),
                flightRow[3],
                flightRow[4]);

        flightsList.insert(std::pair<string, Flight*>(flightRow[0],flight));

    }

    return flightsList;
}

map<string, Reservation *> DBEngine::readReservationTable(
        map<string, Customer *> customerList, map<string, Flight *> flightsList) {

    vector<vector<string>> reservationTable = parseCSVFile(RESERVATION_TABLE_FILE, true);

    map<string, Reservation *> reservationList;

    if (reservationTable.size() <= 0) {
        return reservationList;
    }

    for (auto reservationRow : reservationTable) {

        Customer* customer = customerList[reservationRow[1]];

        Reservation* reservation = new SeatReservation(
                reservationRow[0],
                customer,
                flightsList[reservationRow[2]],
                (Classes)stoi(reservationRow[3]),
                stoi(reservationRow[4]));

        ((Passenger*)customer)->addReservation(reservation);

        reservationList.insert(std::pair<string, Reservation*>(reservationRow[0],reservation));

    }


    return reservationList;
}


vector<vector<string>> DBEngine::parseCSVFile(string inputFile, bool shouldSkipHeader) {

    //Buffer for row
    string tableRow;
    
    //File stream
    ifstream DBFile (inputFile);

    vector<vector<string>> parsedTable;

    bool didSkipHeader = !shouldSkipHeader;

    if (DBFile.is_open())
    {
        while ( getline (DBFile,tableRow) )
        {

            if (!didSkipHeader) {
                didSkipHeader = true;
                continue;
            }

            std::stringstream rowStream(tableRow);

            std::vector<char> cellValue;
            std::vector<string> rowValues;

            char i;

            while (rowStream >> i)
            {
                cellValue.push_back(i);
                if (rowStream.peek() == ',') {
                    rowValues.push_back(string(cellValue.begin(), cellValue.end()));
                    cellValue.clear();
                    rowStream.ignore();
                }
            }
            rowValues.push_back(string(cellValue.begin(), cellValue.end()));
            cellValue.clear();
            parsedTable.push_back(rowValues);
        }
        DBFile.close();
    }
    
    return parsedTable;
}