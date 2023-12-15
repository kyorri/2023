# Smart Home Application

> Here i will explain briefly the chosen data structures to store the information that will be read/written from/to XML files, and explain why I have chosen this approach.

1. I composed the Device class using a bunch of Sensor objects (using std::vector), so that every device will take the sensors' readings.
2. I composed every Room to have a bunch of Devices (using std::vector), each room has a specific number of devices allocated.
3. The class that the whole app works on is storing every Room for our Smart Home using a std::vector.

> I have chosen the vector data structure for every part of the application because of the way every part works, the hierarchy of Room <- Devices <- Sensors.
> Also, the management of the stored info would be easier, just so that I have access to iterators for every vector structure, and easier push/pop operations.

Update
---
- changed pull request base to the correct branch - master to master_dmarian
- modified the code accordingly to the google core guidelines
- added namespaces and scoping
- added the rule of 5 in the device class
- added xml configuration load / save
- resolved the return by value logic error