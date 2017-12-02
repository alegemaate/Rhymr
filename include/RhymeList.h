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

    int loadDict( char* file);

    // Returns all words as characters
    WordArray getWords( char* word);
    WordArray getWords( char* word, int syllableCount);

  protected:

  private:
    WordArray filteredWords;
    WordDatabase db;
};

#endif // RHYMELIST_H
