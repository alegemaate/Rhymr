#ifndef RHYMELIST_H
#define RHYMELIST_H

#include <string>
#include <vector>

#include "WordDatabase.h"

class RhymeList
{
  public:
    RhymeList();
    virtual ~RhymeList();

    int loadDict( std::string file);
    void sendWord( std::string word);

    int numRhymes();

    WordArray getWords();
    WordArray getWords( int syllableCount);

  protected:

  private:
    WordArray words;
    WordDatabase db;
};

#endif // RHYMELIST_H
