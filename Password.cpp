#include "ListArrayIterator.h"
#include "Password.h"
#include "Text.h"


using CSC2110::ListArrayIterator;
using CSC2110::Password;

#include <iostream>
using namespace std;

int Password::getNumMatches(String* curr_word, String* word_guess)
{
   int number_matches = 0;

   for (int i = 0; i < len; i++)
   {
      if (curr_word -> charAt(i) == word_guess -> charAt(i))
      {
         number_matches = number_matches + 1;
      }

   }

   return number_matches;
}

Password::Password()
{
   all_words = new ListArray<String>();
   viable_words = new ListArray<String>();
   len = -1;
}

Password::~Password()
{
   ListArrayIterator<String>* iterator_viable = viable_words -> iterator();
   ListArrayIterator<String>* iterator_all = all_words -> iterator();

   while (iterator_viable -> hasNext())
   { 
      String* thing = iterator_viable -> next();
      delete thing; 
   }

   while (iterator_all -> hasNext())
   { 
      String* thing2 = iterator_all -> next();
      delete thing2; 
   }
}

void Password::addWord(String* word)
{
   if (len == -1)
   {
      int length = word->length();
      len = length;

      all_words -> add(word);
      viable_words -> add(word);
   }

   else if (word->length() == len)
   {
      all_words -> add(word);
      viable_words -> add(word);
   }

   else
   {
      cout << "Skipping the word ";
      word -> displayString();
      cout << " due to improper length." << endl;
   }
}
void Password::guess(int try_password, int num_matches) 
{
   ListArray<String>* new_list = new ListArray<String>();
   ListArrayIterator<String>* iterator = viable_words -> iterator();

   while (iterator -> hasNext())
   { 
      int new_matches = 0;
      String* thing = iterator -> next();
      String* guess = all_words -> get(try_password);
   
      new_matches = getNumMatches(thing, guess);

      if (num_matches == new_matches)
      {
         new_list -> add(thing);
      }
   }
   delete viable_words;
   viable_words = new_list;
}

int Password::getNumberOfPasswordsLeft() 
{
   int Remaining = viable_words -> size();
   return Remaining;
}

void Password::displayViableWords() 
{
   ListArrayIterator<String>* iterator = viable_words->iterator();

   while (iterator -> hasNext())
   {
      String* thing = iterator -> next(); 
      thing -> displayString();
      cout << endl;
   }
} 

int Password::bestGuess()
{
   int best_guess_index = -1;
   int best_num_eliminated = -1;
   int num_viable_passwords = getNumberOfPasswordsLeft();

   //loop over ALL words, even if they have been eliminated as the password
   int count = 1;
   ListArrayIterator<String>* all_iter = all_words->iterator();
   while(all_iter->hasNext())
   {
      String* original_word = all_iter->next();

      //loop over only those words that could still be the password
      //count up the number of matches between a possible password and a word in the original list
      int* count_num_matches = new int[len + 1];

      for (int i = 0; i < len; i++) 
      {
         count_num_matches[i] = 0;
      }

      ListArrayIterator<String>* viable_iter = viable_words->iterator();
      while(viable_iter->hasNext())
      {
         String* viable_word = viable_iter->next();
         int num_matches = getNumMatches(viable_word, original_word);
         count_num_matches[num_matches]++;
      }
      delete viable_iter;

      //find the largest number in the count_num_matches array
      //the largest number indicates the guess that will generate the most eliminations
      int most_num_matches = 0;
      for (int j = 0; j < len; j++) 
      {
         int curr_num_matches = count_num_matches[j];
         if (curr_num_matches > most_num_matches)
         {
            most_num_matches = curr_num_matches;
         }
      }

      //compute the fewest that can possibly be eliminated by guessing the current word (original list)
      int num_eliminated = num_viable_passwords - most_num_matches;

      //select the word to guess that maximizes the minimum number of eliminations (minimax)
      if (num_eliminated > best_num_eliminated)
      {
         best_num_eliminated = num_eliminated;
         best_guess_index = count;
      }
      
      count++;
      delete[] count_num_matches;
   }

   delete all_iter;
   return best_guess_index;  //return a 1-based index into the all_words list of words (careful)
}

String* Password::getOriginalWord(int index)
{
   String* Original_Word = all_words -> get(index);   
   return Original_Word;
}