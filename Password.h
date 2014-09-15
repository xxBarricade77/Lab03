#if !defined PASSWORD_H
#define PASSWORD_H

#include "ListArray.h"
#include "Text.h"
#include "ReadFile.h"
#include "Keyboard.h"

using CSC2110::String;

namespace CSC2110
{
class Password
{
   private:
      ListArray<String>* viable_words;  //the list of words that can still be the password
      ListArray<String>* all_words;  //the original list of words
      int len;  //the length of the first word entered is stored to check that all subsequent words have the same length

      //a private helper method to report the number of character matches between two Strings
      int getNumMatches(String* curr_word, String* word_guess);

   public:
   Password();
   ~Password(); //there is work to do here, delete the individual words

   void addWord(String* word); //add a word to the list of possible passwords
   void guess(int try_password, int num_matches); //index of guessed word in the list of all words (1-based), numbers of matches reported by fallout 3, update viable passwords list
   int getNumberOfPasswordsLeft(); //returns the number of possible passwords remaining
   void displayViableWords(); //display the current list of possible passwords
   int bestGuess(); //the best word in the original list to guess next
   String* getOriginalWord(int index); //get a word from the original list of all passwords, 1-based
};
}

#endif
