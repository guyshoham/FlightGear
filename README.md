# FlightGear
FlightGear is a program that can communicate with the FlightGear Simulator, send and recieve data, in order to make the plane in the simulator fly.

The program reads a text file which tell the program what commands to execute.


## Installation

1. Clone project:

```bash
git clone https://github.com/guyshoham/FlightGear.git
```

2. Download and install [Flightgear](http://home.flightgear.org) to your computer

## Set FlightGear Simulator

1. Open FlightGear Simulator.
2. Click Settings
3. Scroll down to Additional Settings
4. type the following commands:

```bash
--telnet=socket,in,10,127.0.0.1,5402,tcp=8080
--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small
```

## Run

1. Run the C++ program on your IDE

2. After the program is running, open the simulator and click Fly!

3. Enjoy!
