#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include "Commands/Command.h"
#include "Commands/OpenServerCommand.h"
#include "Commands/ConnectCommand.h"
#include "Commands/IfCommand.h"
#include "Commands/LoopCommand.h"
#include "Commands/SleepCommand.h"
#include "Commands/DefineVarCommand.h"
#include "Commands/PrintCommand.h"
#include "Data.h"

using namespace std;

string* lexer(string fileName, Data* data);

void parser(Data* data);

void initSymTableSimulator(Data* data);

void initCommandTable(Data* data);

int main() {
  Data* data = new Data();
  initCommandTable(data);
  initSymTableSimulator(data);

  cout << "Starting Flightgear..." << endl;
  //a pointer to the array.
  data->textArr = lexer("fly.txt", data);
  parser(data);

  return 0;
}

void initCommandTable(Data* data) {
  data->addCommand("openDataServer", new OpenServerCommand());
  data->addCommand("connectControlClient", new ConnectCommand());
  data->addCommand("var", new DefineVarCommand());
  data->addCommand("if", new IfCommand());
  data->addCommand("while", new LoopCommand());
  data->addCommand("Sleep", new SleepCommand());
  data->addCommand("Print", new PrintCommand());
}

void initSymTableSimulator(Data* data) {
  //todo: make function more generic (in case the xml will be changed)
  data->addVariable("airspeed-indicator_indicated-speed-kt",
                    1,
                    "/instrumentation/airspeed-indicator/indicated-speed-kt");

  data->addVariable("time_warp", 1, "/sim/time/warp");

  data->addVariable("switches_magnetos", 1, "/controls/switches/magnetos");

  data->addVariable("heading-indicator_offset-deg", 1, "//instrumentation/heading-indicator/offset-deg");

  data->addVariable("altimeter_indicated-altitude-ft", 1, "/instrumentation/altimeter/indicated-altitude-ft");

  data->addVariable("altimeter_pressure-alt-ft", 1, "/instrumentation/altimeter/pressure-alt-ft");

  data->addVariable("attitude-indicator_indicated-pitch-deg",
                    1,
                    "/instrumentation/attitude-indicator/indicated-pitch-deg");

  data->addVariable("attitude-indicator_indicated-roll-deg",
                    1,
                    "/instrumentation/attitude-indicator/indicated-roll-deg");

  data->addVariable("attitude-indicator_internal-pitch-deg",
                    1,
                    "/instrumentation/attitude-indicator/internal-pitch-deg");

  data->addVariable("attitude-indicator_internal-roll-deg", 1,
                    "/instrumentation/attitude-indicator/internal-roll-deg");

  data->addVariable("encoder_indicated-altitude-ft", 1, "/instrumentation/encoder/indicated-altitude-ft");

  data->addVariable("encoder_pressure-alt-ft", 1, "/instrumentation/encoder/pressure-alt-ft");

  data->addVariable("gps_indicated-altitude-ft", 1, "/instrumentation/gps/indicated-altitude-ft");

  data->addVariable("gps_indicated-ground-speed-kt", 1, "/instrumentation/gps/indicated-ground-speed-kt");

  data->addVariable("gps_indicated-vertical-speed", 1, "/instrumentation/gps/indicated-vertical-speed");

  data->addVariable("indicated-heading-deg", 1, "/instrumentation/heading-indicator/indicated-heading-deg");

  data->addVariable("magnetic-compass_indicated-heading-deg",
                    1,
                    "/instrumentation/magnetic-compass/indicated-heading-deg");

  data->addVariable("slip-skid-ball_indicated-slip-skid", 1, "/instrumentation/slip-skid-ball/indicated-slip-skid");

  data->addVariable("turn-indicator_indicated-turn-rate", 1, "/instrumentation/turn-indicator/indicated-turn-rate");

  data->addVariable("vertical-speed-indicator_indicated-speed-fpm",
                    1,
                    "/instrumentation/vertical-speed-indicator/indicated-speed-fpm");

  data->addVariable("flight_aileron", 1, "/controls/flight/aileron");

  data->addVariable("flight_elevator", 1, "/controls/flight/elevator");

  data->addVariable("flight_rudder", 1, "/controls/flight/rudder");

  data->addVariable("flight_flaps", 1, "/controls/flight/flaps");

  data->addVariable("engine_throttle", 1, "/controls/engines/engine/throttle");

  data->addVariable("current-engine_throttle", 1, "/controls/engines/current-engine/throttle");

  data->addVariable("switches_master-avionics", 1, "/controls/switches/master-avionics");

  data->addVariable("switches_starter", 1, "/controls/switches/starter");

  data->addVariable("active-engine_auto-start", 1, "/engines/active-engine/auto-start");

  data->addVariable("flight_speedbrake", 1, "/controls/flight/speedbrake");

  data->addVariable("c172p_brake-parking", 1, "/sim/model/c172p/brake-parking");

  data->addVariable("engine_primer", 1, "/controls/engines/engine/primer");

  data->addVariable("current-engine_mixture", 1, "/controls/engines/current-engine/mixture");

  data->addVariable("switches_master-bat", 1, "/controls/switches/master-bat");

  data->addVariable("switches_master-alt", 1, "/controls/switches/master-alt");

  data->addVariable("engine_rpm", 1, "/engines/engine/rpm");

}

string* lexer(string fileName, Data* data) {
  list<string> strList;
  ifstream stream;
  string word, tempWord, argument1, argument2;
  int position1, position2;
  stream.open(fileName, ios::in);
  if (!stream.is_open()) {
    throw "File did not open";
  }
  while (!stream.eof()) {
    //if the last element we added was "=" we need to read the whole line and put it as 1 argument in the list
    if (strList.size() != 0 && strList.back() == "=") {
      getline(stream, word);
      strList.push_back(word);
      continue;
    } else {
      stream >> word;
      tempWord = word;
    }
    //if the first word is Print, cut the word print and put it an the list. then i read the rest of the line
    // and put it in the list.
    if (tempWord.length() > 5 && tempWord.erase(5, tempWord.length()) == "Print") {
      strList.push_back(tempWord);
      word.erase(0, 6);
      if (!stream.eof()) {
        getline(stream, tempWord);
      } else {
        tempWord = "";
      }
      if (tempWord.length() >= 1) {
        tempWord.erase(tempWord.length() - 1, tempWord.length());
      } else {
        word.erase(word.length() - 1, word.length());
      }
      word = word + " " + tempWord;
      if ((position1 = word.find('"', 0)) != -1) {
        position2 = word.find('"', position1 + 1);
        word.erase(position1, position1 + 1);
        word.erase(position2 - 1, position2);
      }
      strList.push_back(word);
      continue;
    } else {
      tempWord = word;
    }
    //finds if there is "->" or "<-", cut it and add it to the list.
    if (word.find('-', 0) == 0 && (word.find('>', 0) == 1 || word.find('<', 0) == 1)
        && word.length() > 2) {
      tempWord.erase(2, tempWord.length());
      strList.push_back(tempWord);
      word.erase(0, 2);
      tempWord = word;
    }
    //finds if there are variables we need to add to the list
    if ((position1 = word.find('(', 0)) != -1) {
      position2 = word.find(')', position1);
      strList.push_back(tempWord.erase(position1, position2));
      argument1 = word.erase(0, position1 + 1);
      argument1 = argument1.erase(argument1.length() - 1, argument1.length());
      //if there is more than one argument1, we cut the string to 2 pieces
      // an put them in the list in the right order.
      if ((position1 = argument1.find(',', 0)) != -1) {
        argument2 = argument1;
        argument2 = argument2.erase(0, position1 + 1);
        argument1.erase(position1, argument1.length());
      }
      //if there is a char " in the string it deletes it
      if ((position1 = argument1.find('"', 0)) != -1) {
        position2 = argument1.find('"', position1 + 1);
        argument1.erase(position1, position1 + 1);
        argument1.erase(position2 - 1, position2);

        if ((position1 = argument2.find('"', 0)) != -1) {
          position2 = argument2.find('"', position1 + 1);
          argument2.erase(position1, position1 + 1);
          argument2.erase(position2 - 1, position2);
        }
        strList.push_back(argument1);
        strList.push_back(argument2);
      } else {
        strList.push_back(argument1);
      }
    } else {
      strList.push_back(word);
    }
  }

  string* strArray = new string[strList.size()];
  auto iterator = strList.begin();
//copying all the data to a string array.
  for (int i = 0; i < strList.size(); i++) {
    strArray[i] = *iterator;
    iterator++;
  }
  data->arrSize = strList.size();
  return strArray;
}

void parser(Data* data) {
  int index = 0;
  while (index < data->arrSize - 1) {
    Command* c;

    //todo: delete this code after fixing lexer
    if (data->textArr[index] == "5402") {
      index++;
    }

    c = data->commandTable.at(data->textArr[index]);
    if (c != nullptr) {
      c->setIndex(index);
      index += c->execute(data->textArr, data->commandTable, data->symTableUser, data->symTableSimulator,
                          data->commandsToSimulator);
    }
  }
}
