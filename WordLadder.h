#include <list>
#include <string>

// CODETURD: In header files, it is a BAD idea to say 'using namespace std'
// instead, we just list all the things we want to use
using std::list;
using std::string;

class WordLadder {

  private:
  list<string> dict;        //list of possible words in ladder

  // CODETURD: You may end up defining some private helpers.... I used
  // two when I wrote this.

  public:
    /* Passes in the name of a file that contains a dictionary of 5-letter words.
       Fills the list (dict) with the words within this file. 
       If the file does not open for any reason or if any word within the file
       does not have exactly 5 characters, this function should thrown an
       exception.
    */
    WordLadder(const string& filename);

    /* Passes in two 5-letter words and the name of an output file.
       Outputs to this file a word ladder that starts from the first word passed in
       and ends with the second word passed in.
       If either word passed in does not exist in the dictionary (dict),
       this function should output an error message and return.
       Otherwise, this function outputs to the file the word ladder it finds or outputs
       to the file, the message, "No Word Ladder Found."

       CODETURD:
       Be sure to use the code mechanism discussed in zybooks.  Because this updates
       the dictionary, it means that this method can't be const.

       Algorithm for finding a word ladder
       * create a Stack containing just the first word in the ladder
       * enqueue this Stack on to a Queue of Stacks
       * while this Queue of Stacks is not empty
         get the word on top of the front Stack of this Queue
	 for each word in the dictionary
	   if the word is off by just one letter from the top word
	     create a new Stack that is a copy of the front Stack and push on this off-by-one word found
	     if this off-by-one word is the end word of the ladder, this new Stack contains the entire word ladder. You are done!
	     otherwise, enqueue this new Stack and remove this word from the dictionary
	 dequeue this front stack
	 * if the Queue is empty and you didn't find the word ladder, a word ladder does not exist for these 2 words

	 Four word pairs to try...
	 wheat
	 bread

	 heart
	 wince
	 
	 cheat
	 cheat

	 yards
	 augur
    */
    void outputLadder(const string &start, const string &end, const string &outputFile);
};
