#include "RhymeList.h"

RhymeList::RhymeList(){

}

RhymeList::~RhymeList(){

}

int RhymeList::loadDict( std::string file){
  if ( !(this -> db.load(file.c_str()))) {
		return -1;
	}
	return 0;
}

void RhymeList::sendWord( std::string word){
	db.findRhymes( this -> words, word.c_str(), NULL );
}

int RhymeList::numRhymes(){
  return words.size();
}

WordArray RhymeList::getWords(){
  return words;
}

WordArray RhymeList::getWords( int syllableCount){
  return words;
}
