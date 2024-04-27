#include "WordLadder.h"

#include <iostream>
#include <queue>

using namespace std;

//open a dictionary and place the words into a list dict
WordLadder::WordLadder(const string& filename) {
  ifstream file(filename);

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
      file.close();
      return;
    }
  }

  if (dict.empty()){
    cout <<"Error: dictionary is empty." << endl;
    file.close();
    return;
  }

  file.close();
}

//Create a word ladder (if any) and output to a file
void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
  ofstream file(outputFile);

  if (!file.is_open()){
    cout << "Error: Failed to open file." << endl;
    return;
  }
  
  stack<string> wordStack;
  queue<stack<string>> wordQueue;

  //check if start and end word exists in dictionary
  if (existsInDict(start, end)) {
    wordStack.push(start); //push to stack containing the first word of the ladder (start)
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
  //create a word ladder
  while (!wordQueue.empty()){
    string currWord = wordQueue.front().top(); //word on top of stack in front of queue

    for (auto it = dict.begin(); it != dict.end(); ++it) {
      const string& dictWord = *it; //current word in the dictionary 
      
      //if word is off by just one letter from the top word
      //create a new copy of the front stack and push the current word in dictionary into the stack
      if (offByOne(currWord, dictWord)){
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

//return true if start and end word is in dictionary
bool WordLadder::existsInDict(const string& start, const string& end) const {
    return std::find(dict.begin(),dict.end(),start) != dict.end() && std::find(dict.begin(),dict.end(),end) != dict.end();
  }

//return true if the dictionary word is off by one letter from the top word
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

//output the word ladder to file
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