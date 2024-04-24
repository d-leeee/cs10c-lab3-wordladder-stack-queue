#include "WordLadder.h"

#include <iostream>
#include <fstream>

// This gives us access to std::stack and std::queue.  
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

WordLadder::WordLadder(const string& filename) {
  ifstream file(filename);
  //exception if file did not properly open
  if (!file.is_open()){
    throw runtime_error("Error: Failed to open file.");
  }

  //insert each 5 character word in the dictionary
  string word;
  while (file >> word){
    if (word.size() == 5){
      dict.push_back(word);
    }
    else{
      throw runtime_error("Error: " + word + " is not 5 characters.");
    }
  }

  //throw error if the dictionary is empty
  if (dict.empty()){
    throw runtime_error("Error: dictionary is empty.");
  }

  //close file
  file.close();
}

// CODETURD:  To iterate through the dictionary list, we can use this loop
//    for(auto it = dict.begin(); it != dict.end(); ++it) {
//      const string& x = *it;
//
// CODETURD: We need that because we have to remove words from the dictionary
// after we use them (if we are following the zyBook algorithm), to erase, use
//
// it = dict.erase(x);
//
// CODETURD: To see if a word is in the dictionary, use
// if (std::find(dict.begin(),dict.end(),word) != dict.end()) {
//    cout << word << " is in the dictionary" << endl;
// }
//
// std::find is defined in <algorithm> (you can google more about how it works)
//
void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
  stack<string> words;

  words.push(start);
  // This is how we traverse the std::list dict
  for(auto it = dict.begin(); it != dict.end(); ++it) {
    // This is how we erase an entry and move to the next item (if any)
    it = dict.erase(it);
  }
}
