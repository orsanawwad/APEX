
#include <iostream>
#include "string.h"
#include "interface.h"
#include "MyImplementation.h"


int main() {

    //Added customers
    Ex2* ex2 = new MyImplementation();
    Customer* a = ex2->addCustomer("Orsan",1);
    Customer* b = ex2->addCustomer("Ofek",2);
    Customer* c = ex2->addCustomer("Essa",3);
    Customer* d = ex2->addCustomer("Amit",4);
    Customer* e = ex2->addCustomer("Dvir",5);
    Customer* f = ex2->addCustomer("WHAT",1);

    list<Customer*> customer_test;
    customer_test.push_front(a);
    customer_test.push_front(b);
    customer_test.push_front(c);
    customer_test.push_front(d);
    customer_test.push_front(e);
    customer_test.push_front(f);

    std::list<Customer*>::iterator it;
    for (it = customer_test.begin(); it != customer_test.end(); ++it) {

        Customer* customer = *it;

        if (customer->getFullName() == ex2->getCustomer(customer->getID())->getFullName()) {
            std::cout << "Passed Name " << (*it)->getFullName() << " " << (*it)->getID() << std::endl;
        } else {
            std::cout << "Failed " << (*it)->getFullName() << " " << (*it)->getID() << std::endl;
        }

        if (customer->getPriority() == ex2->getCustomer(customer->getID())->getPriority()) {
            std::cout << "Passed priority " << (*it)->getPriority() << " " << (*it)->getID() << std::endl;
        } else {
            std::cout << "Failed " << (*it)->getPriority() << " " << (*it)->getID() << std::endl;
        }

//        if (customer->getReservations() == ex2->getCustomer(customer->getID())->getPriority()) {
//            std::cout << "Passed priority " << (*it)->getPriority() << " " << (*it)->getID() << std::endl;
//        } else {
//            std::cout << "Failed " << (*it)->getPriority() << " " << (*it)->getID() << std::endl;
//        }
    }

    //Added employees
    Employee* e1 = ex2->addEmployee(10,1968,"",PILOT);
    Employee* e2 = ex2->addEmployee(15,1970,e1->getID(),PILOT);
    Employee* e3 = ex2->addEmployee(13,1971,e2->getID(),FLY_ATTENDANT);
    Employee* e4 = ex2->addEmployee(13,1980,"",FLY_ATTENDANT);
    Employee* e5 = ex2->addEmployee(24,1988,e3->getID(),MANAGER);
    Employee* e6 = ex2->addEmployee(13,1978,"",NAVIGATOR);
    Employee* e7 = ex2->addEmployee(21,1990,e5->getID(),OTHER);
    Employee* e8 = ex2->addEmployee(11,1994,"",PILOT);
//    Employee* e9 = ex2->addEmployee(11,1994,"",PILOT);
//    Employee* e10 = ex2->addEmployee(11,1994,"",PILOT);
//    Employee* e11 = ex2->addEmployee(11,1994,"",PILOT);
//    Employee* e12 = ex2->addEmployee(11,1994,"",PILOT);
//    Employee* e13 = ex2->addEmployee(11,1994,"",PILOT);
//    Employee* e14 = ex2->addEmployee(11,1994,"",PILOT);
    Employee* e15 = ex2->addEmployee(13,1978,"",NAVIGATOR);
    Employee* e16 = ex2->addEmployee(21,1990,e5->getID(),OTHER);

    list<Employee*> employee_list;
    employee_list.push_front(e1);
    employee_list.push_front(e2);
    employee_list.push_front(e3);
    employee_list.push_front(e4);
    employee_list.push_front(e5);
    employee_list.push_front(e6);
    employee_list.push_front(e7);
    employee_list.push_front(e8);
//    employee_list.push_front(e9);
//    employee_list.push_front(e10);
//    employee_list.push_front(e11);
//    employee_list.push_front(e12);
//    employee_list.push_front(e13);
//    employee_list.push_front(e13);
//    employee_list.push_front(e14);
    employee_list.push_front(e15);
    employee_list.push_front(e16);

    std::list<Employee*>::iterator employeeIt;
    for (employeeIt = employee_list.begin(); employeeIt != employee_list.end(); ++employeeIt) {

        Employee* emplo = *employeeIt;

        if (emplo->getSeniority() == ex2->getEmployee(emplo->getID())->getSeniority()) {
            std::cout << "Passed seniority " << emplo->getID() << std::endl;
        } else {
            std::cout << "Failed " << emplo->getID() << std::endl;
        }

        if (emplo->getBirthYear() == ex2->getEmployee(emplo->getID())->getBirthYear()) {
            std::cout << "Passed birthyear " << emplo->getID() << std::endl;
        } else {
            std::cout << "Failed " << emplo->getID() << std::endl;
        }

        if (emplo->getEmployer() == ex2->getEmployee(emplo->getID())->getEmployer()) {
            std::cout << "Passed employer pointer check " << emplo->getID() << std::endl;
        } else {
            std::cout << "Failed " << emplo->getID() << std::endl;
        }

        if (emplo->getEmployer() != NULL) {
            if (emplo->getEmployer()->getID() == ex2->getEmployee(emplo->getID())->getEmployer()->getID()) {
                std::cout << "Passed employer check " << emplo->getID() << std::endl;
            } else {
                std::cout << "Failed " << emplo->getID() << std::endl;
            }
        }

        if (emplo->getTitle() == ex2->getEmployee(emplo->getID())->getTitle()) {
            std::cout << "Passed title check " << emplo->getID() << std::endl;
        } else {
            std::cout << "Failed " << emplo->getID() << std::endl;
        }

    }



    //TODO: Test cases with zeros and negatives
    map<Jobs, int> randomJobs1;
    randomJobs1.insert(std::pair<Jobs,int>(PILOT,2));
    randomJobs1.insert(std::pair<Jobs,int>(NAVIGATOR,1));
    randomJobs1.insert(std::pair<Jobs,int>(MANAGER,1));
    randomJobs1.insert(std::pair<Jobs,int>(FLY_ATTENDANT,1));

    map<Classes , int> randomClasses1;
    randomClasses1.insert(std::pair<Classes,int>(FIRST_CLASS,5));
    randomClasses1.insert(std::pair<Classes,int>(SECOND_CLASS,100));

    Plane* plane1 = ex2->addPlane(370,randomJobs1,randomClasses1);

    map<Jobs, int> randomJobs2;
    randomJobs2.insert(std::pair<Jobs,int>(PILOT,1));

    map<Jobs, int> randomJobs3;
    randomJobs3.insert(std::pair<Jobs,int>(PILOT,1));
//    randomJobs2.insert(std::pair<Jobs,int>(NAVIGATOR,1));
//    randomJobs2.insert(std::pair<Jobs,int>(OTHER,1));

    map<Classes , int> randomClasses2;
    randomClasses2.insert(std::pair<Classes,int>(FIRST_CLASS,5));
    randomClasses2.insert(std::pair<Classes,int>(SECOND_CLASS,5));
    Plane* plane2 = ex2->addPlane(95,randomJobs2,randomClasses2);


    map<Classes , int> randomClasses3;
    randomClasses3.insert(std::pair<Classes,int>(FIRST_CLASS,5));
    randomClasses3.insert(std::pair<Classes,int>(SECOND_CLASS,5));
    Plane* plane3 = ex2->addPlane(95,randomJobs3,randomClasses3);


    list<Plane*> planes_list;
    planes_list.push_front(plane1);
    planes_list.push_front(plane2);

    std::list<Plane*>::iterator planeIt;
    for (planeIt = planes_list.begin(); planeIt != planes_list.end(); ++planeIt) {

        Plane* plane = *planeIt;

        if (plane->getModelNumber() == ex2->getPlane(plane->getID())->getModelNumber()) {
            std::cout << "Passed model number " << plane->getID() << std::endl;
        } else {
            std::cout << "Failed " << plane->getID() << std::endl;
        }

        if (plane->getCrewNeeded() == ex2->getPlane(plane->getID())->getCrewNeeded()) {
            std::cout << "Passed crew needed " << plane->getID() << std::endl;
        } else {
            std::cout << "Failed " << plane->getID() << std::endl;
        }

        if (plane->getMaxFirstClass() == ex2->getPlane(plane->getID())->getMaxFirstClass()) {
            std::cout << "Passed get max first class " << plane->getID() << std::endl;
        } else {
            std::cout << "Failed " << plane->getID() << std::endl;
        }

        if (plane->getMaxEconomyClass() == ex2->getPlane(plane->getID())->getMaxEconomyClass()) {
            std::cout << "Passed get max economy class " << plane->getID() << std::endl;
        } else {
            std::cout << "Failed " << plane->getID() << std::endl;
        }

    }



    Date date1("1990-01-20");
    Date date2("1980-01-20");
    Date date3("1980-02-20");
    Date date4("1976-01-20");
    Date date5("1977-01-20");
    Date date6("1977-01-20");




    if (date1 > date2) {
        std::cout << "Passed date >" << std::endl;
    }

    if (date1 > date3) {
        std::cout << "Passed date >" << std::endl;
    }

    if (date1 > date4) {
        std::cout << "Passed date >" << std::endl;
    }

    if (date1 > date5) {
        std::cout << "Passed date >" << std::endl;
    }

    if (date2 > date3) {
        std::cout << "Passed date >" << std::endl;
    }

    if (date2 > date4) {
        std::cout << "Passed date >" << std::endl;
    }

    if (date4 < date5) {
        std::cout << "Passed date <" << std::endl;
    }

    if (date6 == date5) {
        std::cout << "Passed date ==" << std::endl;
    }

    //TODO: More tests


    Flight* TLVtoAMS = ex2->addFlight(370,date1,"TLV","AMS");
    Flight* TLVtoAMS2 = ex2->addFlight(95,date1,"TLV","AMS");
    Flight* TLVtoAMS3 = ex2->addFlight(95,date2,"TLV","AMS");


    Reservation* reservation1 = ex2->addResevation(a->getID(),TLVtoAMS->getID(),FIRST_CLASS,6);
    Reservation* reservation2 = ex2->addResevation(b->getID(),TLVtoAMS->getID(),FIRST_CLASS,6);
    Reservation* reservation3 = ex2->addResevation(c->getID(),TLVtoAMS->getID(),FIRST_CLASS,6);
    Reservation* reservation4 = ex2->addResevation(d->getID(),TLVtoAMS->getID(),FIRST_CLASS,6);
    Reservation* reservation6 = ex2->addResevation(a->getID(),TLVtoAMS3->getID(),FIRST_CLASS,6);


    Reservation* reservation5 = ex2->addResevation(e->getID(),TLVtoAMS2->getID(),FIRST_CLASS,6);

    ex2->exit();


    delete ex2;


    return 0;
}

//#include "interface.h"
//#include "MyImplementation.h"
//
//#include <iostream>
//#include <fstream>
//
//int session_number = 0;
//const char* test_file = "testing.txt";
//
//#ifndef TEST
//#define TEST
//const int titles_count = 5;
//const Jobs titles_array[] = { MANAGER, PILOT, FLY_ATTENDANT, NAVIGATOR, OTHER };
//
//#endif
//
//const int classes_count = 2;
//const Classes classes_array[] = { SECOND_CLASS, FIRST_CLASS };
//
//int model1 = 1234;
//int model2 = 4321;
//
//int crew_map_1[] = { 1, 0, 0, 1, 0 };
//int crew_map_2[] = { 4, 1, 2, 0, 2 };
//int crew_map_3[] = { 7, 1, 1, 1, 2 };
//
//int classes_map_1[] = { 200, 20 };
//int classes_map_2[] = { 3, 1 };
//
//void success(int counter) {
//    printf("Session %d, test %d passed\n", session_number, counter);
//}
//void failure(int counter, const char* ext = "")
//{
//    printf("Session %d, test %d failed %s\n", session_number, counter, ext);
//}
//
//
//map<Jobs, int> createCrewMap(int *arr)
//{
//    map<Jobs, int> mp;
//    for (int i = 0; i < titles_count; ++i)
//    {
//        mp.insert(pair<Jobs, int>(titles_array[i], arr[i]));
//    }
//
//    return mp;
//}
//
//map<Classes, int> createClassesMap(int *arr)
//{
//    map<Classes, int> mp;
//    for (int i = 0; i < classes_count; ++i) {
//        mp.insert(pair<Classes, int>(classes_array[i], arr[i]));
//    }
//    return mp;
//}
//
//void empFactory(Ex2 *ex2, Jobs title, int num)
//{
//    for (int i = 0; i < num; ++i)
//    {
//        ex2->addEmployee(5, 1950, "", title);
//    }
//}
//
//void empFactory(Ex2* ex2, map<Jobs, int> titles)
//{
//    for (int i = 0; i < titles_count; ++i) {
//        empFactory(ex2, titles_array[i], titles[titles_array[i]]);
//    }
//}
//
//void resFactory(Ex2* ex2, Classes cls, string flight_id, string cust_id, int num) {
//    for (int i = 0; i < num; ++i) {
//        ex2->addResevation(cust_id, flight_id, cls, 2);
//    }
//
//}
//
//template<class T>
//void* should_succeed(Ex2* ex2, T func, int test_number) {
//    void* result = NULL;
//    try
//    {
//        result = func(ex2);
//        success(test_number);
//    }
//    catch (...)
//    {
//        failure(test_number);
//    }
//    return result;
//}
//
//template<class T>
//void should_succeed_bool(Ex2* ex2, T func, int test_num)
//{
//    try
//    {
//        if (func(ex2)) {
//            success(test_num);
//        }
//        return;
//    }
//    catch (...)
//    {
//        failure(test_num, " - WRONG EXCEPTION");
//    }
//    failure(test_num, " - WRONG TEST");
//}
//
//template<class T>
//void should_fail(Ex2* ex2, T func, int test_number) {
//    try
//    {
//        func(ex2);
//        failure(test_number);
//    }
//    catch (...)
//    {
//        success(test_number);
//    }
//}
//
//
//void simple_test1(Ex2* ex2)
//{
//    int counter = 0;
//    // invalid priority
//    should_fail(ex2, [](Ex2* ex2) {ex2->addCustomer("John Hayha", 7); }, counter++);
//    should_succeed(ex2, [](Ex2* ex2) {return (void*)ex2->addCustomer("John Hayha", 4); }, counter++);
//    // add employee - no employer
//    Employee* emp = (Employee*)should_succeed(ex2, [](Ex2* ex2) {return (void*)ex2->addEmployee(4, 6, "", titles_array[0]); }, counter++);
//    ofstream file(test_file, ios_base::trunc);
//    file << emp->getID() << endl;
//    file.close();
//    // add plane
//    should_succeed(ex2, [](Ex2* ex2) {return (void *)ex2->addPlane(model1, createCrewMap(crew_map_1), createClassesMap(classes_map_1)); }, counter++);
//}
//
//void simple_test2(Ex2* ex2)
//{
//    string id;
//    ifstream file(test_file, ios_base::in);
//    file >> id;
//    file.close();
//
//    int counter = 0;
//    Employee* emp = (Employee*)should_succeed(ex2, [id](Ex2* ex2) {return (void*)ex2->addEmployee(4, 6, id, titles_array[3]); }, counter++);
//    should_succeed_bool
//    (ex2, [id, emp](Ex2* ex2) {return emp->getEmployer()->getID() == id; }, counter++);
//
//}
//
//void test3(Ex2* ex2)
//{
//    int counter = 0;
//    Flight* flight = (Flight*)should_succeed(ex2, [](Ex2* ex2) {return (void*)ex2->addFlight(model1, Date("2019-10-10"), "ARL", "VAN"); }, counter++);
//    ofstream file(test_file, ios_base::out | ios_base::trunc);
//    file << flight->getID() << endl;
//    int verifier = 0;
//    auto assigned_c = flight->getAssignedCrew();
//    for (auto it = assigned_c.begin(); it != assigned_c.end(); ++it, ++verifier) {
//        if (verifier > 2) {
//            failure(counter++);
//        }
//        file << (*it)->getID() << endl;
//    }
//
//    file.close();
//}
//
//void test4(Ex2* ex2)
//{
//    int counter = 0;
//    string ids[3];
//    ifstream file(test_file, ios_base::in);
//    for (int i = 0; i < 3; ++i) file >> ids[i];
//    file.close();
//
//    Flight* flight = (Flight*) should_succeed(ex2, [ids](Ex2* ex2) {return (void*)ex2->getFlight(ids[0]); }, counter++);
//    list<Employee*> crew = flight->getAssignedCrew();
//    if (crew.size() != 2)	{
//        failure(counter++);
//    }
//    else
//    {
//        string ids2[2];
//        auto itr = crew.begin();
//        ids2[0] = (*itr++)->getID();
//        ids2[1] = (*itr)->getID();
//
//        bool check1 = (ids2[0] == ids[1]) && (ids2[1] == ids[2]);
//        bool check2 = (ids2[0] == ids[2]) && (ids2[1] == ids[1]);
//        if (check1 || check2) {
//            success(counter++);
//        }
//        else {
//            failure(counter++);
//        }
//
//    }
//
//    should_fail(ex2, [](Ex2* ex2) {return (void*)ex2->addFlight(model1, Date("2019-10-10"), "ARL", "VAN"); }, counter++);
//    should_succeed(ex2, [](Ex2* ex2) {return (void*)ex2->addFlight(model1, Date("2019-10-11"), "ARL", "VAN"); }, counter++);
//}
//
//void test5(Ex2* ex2)
//{
//    int counter = 0;
//    should_succeed(ex2, [](Ex2* ex2) {empFactory(ex2, createCrewMap(crew_map_1)); return nullptr;  }, counter++);
//    should_fail(ex2, [](Ex2* ex2) {return (void*)ex2->addFlight(model1, Date("2019-10-10"), "ARL", "VAN"); }, counter++);
//    // NOTE THAT I SENT model1+1, so the plane is of wrong model!!
//    should_succeed(ex2, [](Ex2* ex2) {return (void *)ex2->addPlane(model1+1, createCrewMap(crew_map_1), createClassesMap(classes_map_1)); }, counter++);
//    should_fail(ex2, [](Ex2* ex2) {return (void*)ex2->addFlight(model1, Date("2019-10-10"), "ARL", "VAN"); }, counter++);
//
//    should_succeed(ex2, [](Ex2* ex2) {return (void *)ex2->addPlane(model1, createCrewMap(crew_map_1), createClassesMap(classes_map_1)); }, counter++);
//    should_succeed(ex2, [](Ex2* ex2) {return (void*)ex2->addFlight(model1, Date("2019-10-10"), "ARL", "VAN"); }, counter++);
//}
//
//
//
//void(*tests[])(Ex2*) = { simple_test1, simple_test2, test3, test4, test5};
//const int tests_number = 5;
//
//class Tester {
//    int session_number;
//public:
//    void operator()(int session_number)
//    {
//        Ex2* ex2 = new MyImplementation();
//        tests[session_number](ex2);
//        ex2->exit();
//        delete ex2;
//    }
//};
//
//
//int main(int argc, char* argv[])
//{
//
//#ifdef DELETE_FIRST
//    // Make sure to delete all of your database files before
//    // you start my tests! You don't want old data to interfere
//#endif
//    Tester t;
//    for (int i = 0; i < tests_number; ++i) {
//        session_number = i;
//        t(i);
//    }
//
//    return 0;
//
//
//}