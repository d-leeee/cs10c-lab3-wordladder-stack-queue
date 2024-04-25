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
    cout << "Error: Failed to open file." << endl;
    return;
  }

  //insert each 5 character word in the dictionary
  string word;
  while (file >> word){
    if (word.size() == 5){
      dict.push_back(word);
    }
    else{
      cout << "Error: " << word << " is not 5 characters." << endl;
      return;
    }
  }

  //throw error if the dictionary is empty
  if (dict.empty()){
    cout <<"Error: dictionary is empty." << endl;
    return;
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
  ofstream file(outputFile);
  if (!file.is_open()){
    cout << "Error: Failed to open file." << endl;
    return;
  }
  
  stack<string> wordStack;
  queue<stack<string>> wordQueue;
  string curr;

  //push start word to stack if it exists in the dictionary
  if (std::find(dict.begin(),dict.end(),start) != dict.end()) {
    //create a stack containing just the first word in the laader
    wordStack.push(start);
    //enqueue this stack on to a queue of stacks
    wordQueue.push(wordStack);
  }
  else{
    file << "No Word Ladder Found." << endl;
    return;
  }

  //while this queue of stacks is not empty
  while (!wordQueue.empty()){
    //get the word on top of the front stack of this queue
    stack<string> currStack = wordQueue.front(); 
    string currWord = currStack.top();
    
    //for each word in the dictionary
    for(auto it = dict.begin(); it != dict.end(); ++it) {
      const string& dictWord = *it;
      int count = 0;
      //count how many letters off
      for (unsigned i=0;i<dictWord.size();i++){
        if (dictWord[i] != currWord[i]){
          count++;
          //if word is off by more than one, exit loop
          if (count > 1){
            break;
          }
        }
      }
      //if word is off by just one letter from the top word
      if (count == 1){
        stack<string> newStack = wordQueue.front();
        newStack.push(dictWord);

        //if word is not the end word, enqueue this stack and remove from dictionary
        if (dictWord != end){
          wordQueue.push(newStack); 
          // This is how we erase an entry and move to the next item (if any)
          it = dict.erase(it);  
        }
        //if word ladder is completed, output to file
        else{
          list<string> output;
          while (!newStack.empty()){
            output.push_front(newStack.top());
            newStack.pop();
          }
          for (auto it=output.begin();it!=output.end();++it){
            cout << *it << " ";
          }
          file.close();
          return;
        }
      }
    }
    wordQueue.pop();
  }
  //if queue is empty and no ladder was found
  file << "No Word Ladder Found." << endl;
  file.close();
}
