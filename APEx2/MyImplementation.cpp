#include <cstdlib>
#include "MyImplementation.h"
#include "interface.h"
#include "CompanyEmployee.h"
#include "CompanyPlane.h"
#include "CompanyFlight.h"
#include "Passenger.h"
#include "SeatReservation.h"
#include "DBEngine.h"
#include "iostream"

#define ID_LENGTH 20

/**
 * Add a new employee.
 * @param seniority how many years he/she worked.
 * @param birth_year year of birth
 * @param employer_id 30
 * @param title job title.
 * @return a new employee.
 */
Employee *MyImplementation::addEmployee(int seniority, int birth_year, string employer_id, Jobs title) {

    //Get random string
    string id = randomString(ID_LENGTH);

    //Get employer if exist.
    Employee* employer = getEmployee(employer_id);

    //Create new employee
    Employee* employee = new CompanyEmployee(id,title,birth_year,employer,seniority);

    //Insert to map (aka db in ram)
    employeeList.insert(std::pair<string,Employee*>(id,employee));
    employeeSchedule.insert(std::pair<Employee*, list<Date>* >(employee,new list<Date>()));

    return employee;
}

/**
 * Get employee by id.
 * @param id id of employee.
 * @return employee by id if exist.
 */
Employee *MyImplementation::getEmployee(string id) {

    if (employeeList.count(id) > 0) {
        return employeeList[id];
    } else {
        return NULL;
    }
}

/**
 * Add Plane to company's collection of planes.
 * @param model_number plane model number.
 * @param crew_needed what kind of crew required for operating the plane.
 * @param max_passangers maximum amount of possible passengers from each class.
 * @return plane pointer.
 */
Plane *MyImplementation::addPlane(int model_number, map<Jobs, int> crew_needed, map<Classes, int> max_passangers) {

    string id = randomString(ID_LENGTH);

    Plane* plane = new CompanyPlane(id,model_number,crew_needed,max_passangers);

    planesList.insert(std::pair<string,Plane*>(id,plane));
    planeSchedule.insert(std::pair<Plane*, list<Date>* >(plane,new list<Date>()));

    return plane;
}

/**
 * Get plane by id.
 * @param id id of plane.
 * @return plane pointer if exist.
 */
Plane *MyImplementation::getPlane(string id) {
    if (planesList.count(id) > 0) {
        return planesList[id];
    } else {
        return NULL;
    }
}


/**
 * Register new flight line.
 * @param model_number plane model required for this flight.
 * @param date when the flight is due.
 * @param source plane's origin airport.
 * @param destination plane's destination airport.
 * @return
 */
Flight *MyImplementation::addFlight(int model_number, Date date, string source, string destination) {

    string id = randomString(ID_LENGTH);

    Plane* plane = NULL;

    //Go through each plane
    for (auto& planeScheduleAuto : planeSchedule) {

        //Flag for if the plane is taken from that day
        bool shouldSkip = false;

        //Plane to check
        Plane* currentPlane = planeScheduleAuto.first;

        //Work days of the plane
        list<Date>* currentPlaneWorkDays = planeScheduleAuto.second;

        //Check if the plane is of the required model.
        if (currentPlane->getModelNumber() == model_number) {

            //Check each date, if the same, that means its taken.
            for (auto& currentPlaneWorkDaysAuto : *currentPlaneWorkDays) {
                const Date &currentDate = currentPlaneWorkDaysAuto;

                //If its taken, set a flag for first loop to continue and break the current one..
                if (currentDate == date) {
                    shouldSkip = true;
                    break;
                }
            }

            if (shouldSkip) {
                continue;
            } else {
                //If plane is available on that day, set it as taken and add the date to its list.
                plane = currentPlane;
                this->planeSchedule[plane]->push_front(date);
                break;
            }
        }
    }

    /**
     * If no plane exists throw error.
     */
    if (plane == NULL) {
        throw "No Planes found for this flight!";
    }

    //Prepare list of employees
    list<Employee*> employeesToAssign;

    map<Jobs, int> requiredCrewTitles = plane->getCrewNeeded();

    map<Jobs, int>::iterator requiredCrewTitlesIterator;

    //Iterate through crew titles
    for (requiredCrewTitlesIterator = requiredCrewTitles.begin();
    requiredCrewTitlesIterator != requiredCrewTitles.end();
    ++requiredCrewTitlesIterator) {

        Jobs currentJob = requiredCrewTitlesIterator->first;
        int currentJobAmount = requiredCrewTitlesIterator->second;

        if (currentJobAmount <= 0) {
            continue;
        }

        map<Employee*, list<Date>* >::iterator employeeScheduleIterator;

        //Iterate through employees
        for (employeeScheduleIterator = employeeSchedule.begin();
             employeeScheduleIterator != employeeSchedule.end();
             ++employeeScheduleIterator) {

            bool shouldSkip = false;

            if (currentJobAmount <= 0) {
                break;
            }

            Employee* currentEmployee = employeeScheduleIterator->first;
            list<Date>* currentEmployeeDates = employeeScheduleIterator->second;
            list<Date>::iterator currentEmployeeDatesIterator;

            if (currentEmployee->getTitle() == currentJob) {
                //Iterate through dates
                for (currentEmployeeDatesIterator = currentEmployeeDates->begin();
                currentEmployeeDatesIterator != currentEmployeeDates->end();
                ++currentEmployeeDatesIterator) {

                    Date currentDate = *currentEmployeeDatesIterator;

                    //If the required date exist on his/her schedule, add it to list of employees and continue looking.
                    if (currentDate == date) {
                        shouldSkip = true;
                        break;
                    }
                }

                //Assign if found, else continue looking.
                if (shouldSkip) {
                    continue;
                } else {
                    employeesToAssign.push_back(currentEmployee);
                    employeeScheduleIterator->second->push_back(date);
                    currentJobAmount--;
                }

            }

        }

        //If not enough employees found for operating the plane, throw an error and hire more people.
        if (currentJobAmount > 0) {
            throw "Could not find unassigned employees for the task.";
        }

    }

    Flight* flight = new CompanyFlight(id,plane,employeesToAssign,date,source,destination);

    flightList.insert(std::pair<string,Flight*>(id,flight));

    return flight;
}

/**
 * Get flight by id.
 * @param id id of flight.
 * @return flight if exist.
 */
Flight *MyImplementation::getFlight(string id) {
    if (flightList.count(id) > 0) {
        return flightList[id];
    } else {
        return NULL;
    }
}

/**
 *
 * @param full_name name of customer.
 * @param priority priority of customer from 1 to 5.
 * @return a new customer.
 */
Customer *MyImplementation::addCustomer(string full_name, int priority) {

    string id = randomString(ID_LENGTH);

    if (priority > 5 || priority < 1) {
        throw "Error, Priority must be between 1 and 5";
    }

    Customer* customer = new Passenger(id, full_name, priority);

    customerList.insert(std::pair<string,Customer*>(id,customer));

    return customer;
}

/**
 * Get customer by id.
 * @param id id of customer.
 * @return customer by id if exist.
 */
Customer *MyImplementation::getCustomer(string id) {
    if (customerList.count(id) > 0) {
        return customerList[id];
    } else {
        return NULL;
    }
}

Reservation *MyImplementation::addResevation(string customerId, string flightId, Classes cls, int max_baggage) {

    string id = randomString(ID_LENGTH);

    Customer* customer = getCustomer(customerId);

    if (customer == NULL) {
        throw "Customer not found!";
    }

    CompanyFlight* flight = (CompanyFlight*)getFlight(flightId);

    if (flight == NULL) {
        throw "Flight not found!";
    }

    list<Reservation*> flightReservations = flight->getReservations();

    list<Reservation*>::iterator reservationsIterator;


    /**
     * Count each class reservations.
     */

    int currentFirstClassPassengers = 0;
    int currentEconomyClassPassengers = 0;

    for (reservationsIterator = flightReservations.begin();
    reservationsIterator != flightReservations.end() ;
    ++reservationsIterator) {
        Reservation* reserve = *reservationsIterator;

        if (reserve->getClass() == FIRST_CLASS) {
            currentFirstClassPassengers++;
        } else if (reserve->getClass() == SECOND_CLASS) {
            currentEconomyClassPassengers++;
        }

    }

    /**
     * Check if there's an available seat.
     */

    Plane* planeForThisFlight = flight->getPlane();

    if (cls == FIRST_CLASS) {
        if (currentFirstClassPassengers == planeForThisFlight->getMaxFirstClass()) {
            throw "No space left in economy class.";
        }
    } else if (cls == SECOND_CLASS) {
        if (currentEconomyClassPassengers == planeForThisFlight->getMaxEconomyClass()) {
            throw "No space left in economy class.";
        }
    }

    /**
     * Create reservation and push to list.
     */

    Reservation* reservation = new SeatReservation(id, customer, flight,cls,max_baggage);

    ((Passenger*)customer)->addReservation(reservation);

    flight->addReservation(reservation);

    reservationList.insert(std::pair<string,Reservation*>(id,reservation));

    return reservation;
}

/**
 * Get reservation by id.
 * @param id to get reservation for.
 * @return reservation pointer if exists.
 */
Reservation *MyImplementation::getReservation(string id) {
    if (reservationList.count(id) > 0) {
        return reservationList[id];
    } else {
        return NULL;
    }
//    return reservationList[id];
}

/**
 * on application exit save state.
 */
void MyImplementation::exit() {

    //DBEngine class used to save and read files.
    DBEngine db;

    db.writeCustomersTable(customerList);
    db.writEmployeesTable(employeeList);
    db.writeEmployeesScheduleTable(employeeSchedule);
    db.writePlanesTable(planesList);
    db.writePlanesScheduleTable(planeSchedule);
    db.writeRequiredCrewTable(planesList);
    db.writeFlightTable(flightList);
    db.writeFlightEmployeesTable(flightList);
    db.writeReservationTable(reservationList);


    //Flush allocated head memory

    map<string, Customer*>::iterator customerIterator;
    for (customerIterator = customerList.begin(); customerIterator != customerList.end(); ++customerIterator) {
        delete customerIterator->second;
    }

    map<string, Employee*>::iterator employeeIterator;
    for (employeeIterator = employeeList.begin(); employeeIterator != employeeList.end(); ++employeeIterator) {
        delete employeeIterator->second;
    }

    map<Employee*, list<Date>* >::iterator employeeScheduleIterator;
    for (employeeScheduleIterator = employeeSchedule.begin(); employeeScheduleIterator != employeeSchedule.end(); ++employeeScheduleIterator) {
        delete employeeScheduleIterator->second;
    }

    map<string, Plane*>::iterator planesListIterator;
    for (planesListIterator = planesList.begin(); planesListIterator != planesList.end(); ++planesListIterator) {
        delete planesListIterator->second;
    }

    map<Plane*, list<Date>* >::iterator planeScheduleIterator;
    for (planeScheduleIterator = planeSchedule.begin(); planeScheduleIterator != planeSchedule.end(); ++planeScheduleIterator) {
        delete planeScheduleIterator->second;
    }

    map<string, Flight*>::iterator flightListIterator;
    for (flightListIterator = flightList.begin(); flightListIterator != flightList.end(); ++flightListIterator) {
        delete flightListIterator->second;
    }

    map<string, Reservation*>::iterator reservationListIterator;
    for (reservationListIterator = reservationList.begin(); reservationListIterator != reservationList.end(); ++reservationListIterator) {
        delete reservationListIterator->second;
    }

}

/**
 * Generates a random string.
 * @param length id length
 * @return "unique" strind id.
 */
std::string MyImplementation::randomString(std::string::size_type length) {
    std::string s;

    s.reserve(length);

    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    while (length--) {
        s += alphanum[(rand() * rand()) % (sizeof(alphanum) - 1)];
    }

    return s;
}

/**
 * CTOR: Read and load from files.
 */
MyImplementation::MyImplementation() {
    DBEngine db;
    customerList = db.readCustomersTable();
    planesList = db.readPlanesTable();
    employeeList = db.readEmployeesTable();
    planeSchedule = db.readPlanesScheduleTable(planesList);
    employeeSchedule = db.readEmployeesScheduleTable(employeeList);
    flightList = db.readFlightsTable(employeeList,planesList);
    reservationList = db.readReservationTable(customerList,flightList);
}
