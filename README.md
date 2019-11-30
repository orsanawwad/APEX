###### WIP CLEAPUP ######

# FlightGear Controller
###### AKA: APEX (Advanced Programming EXercises)
###### (AP-MS2 AP2EX2 AP2M3 AP2M4 AP2M5) ######

A fullstack application that is used to directly communicate with [FlighGear](https://www.flightgear.org/) application.

It consists of:

* Backend server (C#):
        
    Used to provide Restful API for fetching realtime information about the current flight instance by communicating directly with FlightGear's [Telnet server](http://wiki.flightgear.org/Telnet_usage).

* Web Frontend client (C# - ASP.Net)

    Displays information about the current flight on a map using the backend API server.

* Desktop client (C# - WPF, C++)

    Similar to frontend except it has built in controllers (Mouse controllable joystick) to directly control the plane in FlightGear using its own Telnet server, plus it has support for writing custom scripts to program flights.

    The script interpreter is written in C++, it utilizes the commander design pattern and shunting yard algorithm where it parses a given text received as input from a TCP socket and as a result it controls the flight.

* Android client (Java - Android Canvas API)

    A controller client just like the desktop client which controls the plane in flight using an Android Phone!


# Pathfinder [(AP-MS2)](https://github.com/orsanawwad/APEX/tree/master/AP-MS2)

An implementation of numerous path finding algorithms such as DFS, BFS, Hill Climbing, A*.

The application consists:

* Server (C++)

    Uses classic TCP sockets for listening for requests, it accepts a matrix of numbers where each is a cost value, start position and goal, then runs these algorithms to calculate the best possible path and return it.

    This application utilizes many design patterns such as Dependency Injection, Object Adapters, Composite Pattern...

* Client (Python, not included here)

    A generic TCP client that reads the matrix data from file and sends it to the server.
