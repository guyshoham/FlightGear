#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

string* lexer(string fileName);

int main() {
  std::cout << "Hello, World!" << std::endl;
  std::cout << "this is new branch" << std::endl;
  //a pointer to the array.
  string* string1 = lexer("fly");

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
