#include "stringParser.h"

stringParser::stringParser(){}
stringParser::~stringParser(){}

std::string stringParser::lastWord( std::string input){
  size_t index = input.find_last_of(" ");
  if(index != std::string::npos){
    std::string tempString = input.substr(index+1, input.length());
    tempString.erase(std::remove(tempString.begin(), tempString.end(), '\n'), tempString.end());
    tempString.erase(std::remove(tempString.begin(), tempString.end(), '\r'), tempString.end());
    tempString.erase(std::remove(tempString.begin(), tempString.end(), '\0'), tempString.end());

    return tempString;
  }
  else
    return input;
}

void stringParser::getSentences( std::string input, int iter, int* lineon, std::vector<std::string>* stringCont){
  int iterpos = 0;
  int iterline = 0;
  bool lineSet = false;

  std::stringstream ss( input);
  std::string to;

  if( input != ""){
    while( std::getline( ss, to, '\n')){
      if( iter >= iterpos && iter <= iterpos + to.length()){
        *lineon = iterline;
        lineSet = true;
      }

      stringCont -> push_back(to);

      iterpos += to.length() + 1;
      iterline ++;
    }

    if( !lineSet){
      *lineon = iterline;
      stringCont -> push_back("");
    }
  }
}
