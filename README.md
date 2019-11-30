###### WIP CLEAPUP ######

# FlightGear Controller
###### AKA: APEX (Advanced Programming EXercises)

A fullstack application that is used to directly communicate with [FlighGear](https://www.flightgear.org/) application.

It consists of:

* Backend server (C#):
        
    Used to provide Restful API for fetching realtime information about the current flight instance by communicating directly with FlightGear's [Telnet server](http://wiki.flightgear.org/Telnet_usage).

* Web Frontend client (C# - ASP.Net)

    Displays information about the current flight on a map using the backend API server.

* Desktop client (C# - WPF)

    Similar to frontend except it has built in controllers (Mouse controllable joystick) to directly control the plane in FlightGear using its own Telnet server, plus it has support for writing custom scripts to program flights.

* Android client (Java - Android Canvas API)

    A controller client just like the desktop client which controls the plane in flight using an Android Phone!