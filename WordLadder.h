#include <list>
#include <string>
#include <fstream>
#include <stack>
#include <algorithm>

using std::list;
using std::string;
using std::ofstream;
using std::stack;

class WordLadder {

  private:
  list<string> dict; //list of possible words in ladder

  //helper functions
  
  //return true if start and end word is in dictionary
  bool existsInDict(const string& start, const string& end) const;
  //return true if the dictionary word is off by one letter from the top word
  bool offByOne(const string& currWord, const string& dictWord) const;
  //output the word ladder to file
  void outputLadderToFile(ofstream& file, stack<string>& newStack) const;

  public:
    //open a dictionary and place the words into a list dict
    WordLadder(const string& filename);
    //Create a word ladder (if any) and output to a file
    void outputLadder(const string &start, const string &end, const string &outputFile);
};
