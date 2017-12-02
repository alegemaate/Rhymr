#include "RhymeList.h"

// Ctor
RhymeList::RhymeList(){ }

// Dtor
RhymeList::~RhymeList(){ }

// Loads a dictionary from file
int RhymeList::loadDict( char* file){
  if ( !(this -> db.load(file))) {
		return -1;
	}
	return 0;
}

// Gets all words
WordArray RhymeList::getWords( char* word){
  WordArray words;
  db.findRhymes( words, word, NULL );
  return words;
}

// Get words of given syllable count
WordArray RhymeList::getWords( char* word, int syllableCount){
  WordArray words;
  WordFilter theFilter;

  theFilter.maxSyllables = syllableCount;
  theFilter.minSyllables = syllableCount;

  db.findRhymes( words, word, &theFilter );

  return words;
}
