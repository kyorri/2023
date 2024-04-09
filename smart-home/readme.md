# HW8
* Added client / server functions for the application. To use the app: [executable] [server/client] (port)
* Used std::stringstream for passing messages around the application to send a stream of bytes between the client and the server instance;
* Added a list operation that lists every room / device / sensor in our house;
* Also added a create operation that 
* Specifying a room/device/sensor will be done using identifiers (the indexes in the std::vector of every type);
* The identifiers of the objects can be fetched using the list action.
* Usage of every client operation - examples
    - Adding operations (they add objects from their respective pools created with the create operation)
        - Firstly, construct a device and attach to it a constructed sensor, then add the device to another created room!
        1. Adding a room to the home: add room#0
        2. Adding a device: add device#0 room#0
        3. Adding a sensor: add sensor#0 room#0/device#0
        4. Adding an object from an object pool (be it room/device/sensor) - examples:
            - add room_pool#0
            - add sensor_pool#3 room#0/device#1
    - Removing operations
        1. Removing a room: remove room#0
        2. Removing a device: remove room#0/device#0
        3. Removing a sensor: remove room#0/device#0/sensor#0
    - Printing operations
        1. Print the information for the smart home: print home
        2. Print a room: print room#0
        3. Print a device: print room#0/device#0
        4. Print a sensor: print room#0/device#0/sensor#0
    - Listing operations
        1. List every room in the smart home: list rooms
        2. List every device in a room: list devices room#
        3. List every sensor in a device: list sensors room#/device#
        4. Listing object pools: list room_pool, device_pool, sensor_pool
    - Create operations
        1. Create a room to the object pool: create room Kitchen
        2. Create a device to the pool: create device_thermostat
        3. Create a sensor to the pool: create sensor_airquality


# HW9 - Serialization and Scripting
* Added the Message class for serialization of the client instances' inputs, with a timestamp for the bash scripting part of the HW.
* Used a Date class to keep track of the day by using the ctime library and the c-style time functions and structs.
If we'd have C++20 we could have used the newer chrono types from the stdlib.
* The bash script will use the word count options for grep (-w -c) that will supplement the number of matches of the timestamp
of the day in the yyyy-mm-dd format that is supplied by the date command using the +%F specifier.
* The output of the grep command (the number of occurences/ requests for our server) will show up in a file as so:
    > "There were x request(s) today! (yyyy-mm-dd)"
* Added a Thread Pool implementation to permit our server to send and receive data from and to our multiple client instances
using threads, but with a lesser memory overhead by not constructing/deconstructing threads every time we get a connection to a client, having a single finite pool of threads.
* Server will log the timestamp of a client request, followed by its name, and then followed by the content of the request.
* The logging will be in this format
    > [yyyy/mm/dd / username]
    > <br>CONTENT
* The serialization will be done using the Boost library serialization.