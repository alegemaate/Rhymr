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

    void sendWord( std::string word);

    int numRhymes();

    std::vector<std::string> getWords();
    std::vector<std::string> getWords( int syllableCount);

  protected:

  private:
    int rhymeCount;
};

#endif // RHYMELIST_H
