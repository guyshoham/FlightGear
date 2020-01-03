# FlightGear
FlightGear is an interpreter that allows remote control of a flight simulator.

## Installation

1. Clone project:

```bash
git clone https://github.com/guyshoham/FlightGear.git
```

2. Download and install [Flightgear](http://home.flightgear.org) to your computer

## Introducing to flight simulator
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

## Set generic_small.xml 
The sampled values are defined in a file called **generic_small.xml** that is attached to the project.
The file should be added in the location where you installed **FlightGear** in the **/data/protocol** folder.

## Run

### on Clion:
1. Run the C++ program on your IDE.

2. After the program is running, open the simulator and click **Fly!**

3. Enjoy!

### Manual:

Open terminal in project directory and type:

```bash
sudo g++ -std=c++14 main.cpp Commands/Command.h Commands/Command.cpp Commands/ConditionParser.h Commands/ConditionParser.cpp Commands/ConnectCommand.h Commands/ConnectCommand.cpp Commands/DefineVarCommand.h Commands/DefineVarCommand.cpp Commands/IfCommand.h Commands/IfCommand.cpp Commands/LoopCommand.h Commands/LoopCommand.cpp Commands/PrintCommand.h Commands/PrintCommand.cpp Commands/SleepCommand.h Commands/SleepCommand.cpp Commands/AssignCommand.h Commands/AssignCommand.cpp Commands/OpenServerCommand.h Commands/OpenServerCommand.cpp VarInfo.cpp VarInfo.h Data.cpp Data.h Expressions/Expression.h Expressions/Calculator.h Expressions/Calculator.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
```
After the compilation process has done, type:
```bash
./a.out fly.txt
```
After the program is running, open the simulator and click **Fly!**

Enjoy!
