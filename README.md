# FlightGear
FlightGear is an interpreter that allows remote control of a flight simulator.

## Installation

1. Clone project:

```bash
git clone https://github.com/guyshoham/FlightGear.git
```

2. Download and install [Flightgear](http://home.flightgear.org) to your computer

## Introducing the flight simulator
We would like to write an interpreter for UAV control.

Our plane will fly in the virtual space of the flight simulator **FlightGear**

You can download the flight simulator from [here](http://home.flightgear.org).

Among other things, this simulator is also a server that can be connected as a client, and vice versa. This allows us to easily retrieve information about the various flight parameters in real time and even inject commands to operate the aircraft.

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

2. After the program is running, open the simulator and click **Fly!**

3. Enjoy!
