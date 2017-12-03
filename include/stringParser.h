#ifndef STRINGPARSER_H
#define STRINGPARSER_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>


class stringParser{
  public:
    stringParser();
    virtual ~stringParser();

    static std::string lastWord( std::string sentence);
    static void getSentences( std::string input, int iter, int* lineon, std::vector<std::string>* stringCont);

  protected:

  private:
};

#endif // STRINGPARSER_H
