#include "WordLadder.h"

#include <iostream>
#include <queue>

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

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
  ofstream file(outputFile);
  if (!file.is_open()){
    cout << "Error: Failed to open file." << endl;
    return;
  }
  
  stack<string> wordStack;
  queue<stack<string>> wordQueue;

  //check if start and end word exists in dictionary
  if (existsInDict(start,end)) {
    wordStack.push(start); //create a stack containing just the first word in the laader
    wordQueue.push(wordStack); //enqueue this stack on to a queue of stacks
  }
  else{
    file << "No Word Ladder Found." << endl;
    file.close();
    return;
  }

  //if start and end are the same words, output start
  if (start == end){
    file << start << endl;
    file.close();
    return;
  }

  //while this queue of stacks is not empty
  while (!wordQueue.empty()){
    //get the word on top of the front stack of this queue
    string currWord = wordQueue.front().top();

    //for each word in the dictionary
    for (auto it = dict.begin(); it != dict.end(); ++it) {
      const string& dictWord = *it;
      
      //if word is off by just one letter from the top word
      if (offByOne(currWord, dictWord)){
        //create a new stack that is a copy of the front stack and push on this off by one word found
        stack<string> newStack = wordQueue.front();
        newStack.push(dictWord);

        //if word ladder is not completed (word is not the same as end)
        if (dictWord != end){
          wordQueue.push(newStack); 
          it = dict.erase(it); //delete from dictionary
          it--; //this is needed so that we dont skip over an element after delete
        }

        //if word ladder is completed, output to file
        else{
          outputLadderToFile(file,newStack);
        }
      }
    }
    wordQueue.pop();
  }
  //if queue is empty and no ladder was found
  file << "No Word Ladder Found." << endl;
  file.close();
}

bool WordLadder::existsInDict(const string& start, const string& end) const {
    return std::find(dict.begin(),dict.end(),start) != dict.end() && std::find(dict.begin(),dict.end(),end) != dict.end();
  }

bool WordLadder::offByOne(const string& currWord, const string& dictWord) const {
    int count = 0;

    //count how many letters off
    for (unsigned i=0;i<dictWord.size();i++){
      if (dictWord[i] != currWord[i]){
        count++;

        //if word is off by more than one return false
        if (count > 1){
          return false;
        }
      }
    }
    return true;
  }

void WordLadder::outputLadderToFile(ofstream& file, stack<string>& newStack) const {
  list<string> outputBackwards; //creating a list so that we can output the ladder backwards (since zybooks is outputting it the opposite direction)
  while (!newStack.empty()){
    outputBackwards.push_front(newStack.top());
    newStack.pop();
  }
  //write to file
  for (auto it=outputBackwards.begin();it!=outputBackwards.end();++it){
    file << *it << " ";
  }
  file.close();
}