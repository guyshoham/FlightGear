#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <unordered_map>
#include "Commands/Command.h"
#include "Commands/OpenServerCommand.h"
#include "Commands/ConnectCommand.h"
#include "Commands/IfCommand.h"
#include "Commands/LoopCommand.h"
#include "Commands/FuncCommand.h"
#include "Commands/SleepCommand.h"
#include "Commands/DefineVarCommand.h"
#include "Commands/PrintCommand.h"
#include "Commands/AssignCommand.h"

using namespace std;

unordered_map<string, Command*> commandTable({
                                                 {"openDataServer", new OpenServerCommand(-1)},
                                                 {"connectControlClient", new ConnectCommand(-1)},
                                                 {"if", new IfCommand(-1)},
                                                 {"while", new LoopCommand(-1)},
                                                 {"func", new FuncCommand(-1)},
                                                 {"Sleep", new SleepCommand(-1)},
                                                 {"var", new DefineVarCommand(-1)},
                                                 {"Print", new PrintCommand(-1)},
                                                 {"assign", new AssignCommand(-1)}
                                             });

string* lexer(string fileName);
void parser(string* arr);

int main() {
  std::cout << "Starting Flightgear..." << std::endl;
  //a pointer to the array.
  string* arr = lexer("fly.txt");
  parser(arr);

  return 0;
}

string* lexer(string fileName) {
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
  return strArray;
}

void parser(string* arr) {
  int index = 0;
  while (index < arr->size()) {
    Command* c;
    c = commandTable.at(arr[index]);
    if (c != NULL) {
      index += c->execute();
    }
  }
}
