cmake_minimum_required(VERSION 3.12)
project(APEx2)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS ON)

add_executable(APEx2 main.cpp interface.h CompanyEmployee.cpp CompanyEmployee.h CompanyPlane.cpp CompanyPlane.h CompanyFlight.cpp CompanyFlight.h Passenger.cpp Passenger.h SeatReservation.cpp SeatReservation.h Date.cpp MyImplementation.cpp MyImplementation.h DBEngine.cpp DBEngine.h)