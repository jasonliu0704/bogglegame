//own version

#include "boggleplayer.h"
#include <string>
#include <vector>
#include <iostream>
#include <locale>
#include <set>
#include <array>
BogglePlayer::BogglePlayer() {
  delete[] myBoard;
  delete[] visited;
  builtLex = false;
  setBoard = false;
}

void BogglePlayer::buildLexicon(const set<string>& word_list){

  //insert words into the lexicon datastructure
  for(auto word : word_list){
    lexicon.insert(word);
  }


}

void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray) {
  //set up board parameter
  scol = cols;
  srow = rows;
  sboard = cols * rows;
  //set up board
  myBoard = string[sboard];

  //convert 2d array into 1d
  for(int i = 0 ; i < rows; i++){
    for(int j = 0; j < cols; j++){
      //lower case
      myBoard[i*cols + j] = tolower(diceArray[i][j]);
    }
  }
}

bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words) {
  //set check
  if(!builtLex || !setBoard) return false;

  //find words by DFS the board


        return true;
}

bool BogglePlayer::isInLexicon(const string& word_to_check) {
        return true;
}


//check if isOnBoard works


//isOnBoard function

vector<int> BogglePlayer::isOnBoard(const string& word) {
  /*
  *vector<int> result;
  if(!setBoard || !builtLexicon){
     return result;
  }
  result = node->isOnBoard(word);
  return result;
  
  */
         vector<int> result;
         if(!setBoard){
             return result;//if the board hasn't been set, we set the vector to empty
         }
         for (int i=0; i<sboard; i++){
             String visited[i]=false; //we intialize all bools to be false
         }
         string lowerCase_word = word;
         for(unsigned int i=0; i<word.size();i++){
            lowerCase_word[i]=tolower(word[i]);
         }
         for(int j=0; j<sboard; j++){
            //first of all, we check if the dice has a face of the word's prefix
            if(checkPrefix(myBoard[j], lowerCase_word])){
              result.push_back(j); 
              if(myBoard[j].size() == word.size()){
                 break;
              }
              //if(isOnBoardRecurse(result, lowerCase_word.substr(myBoard[j].size()))){
                //break;
              //}
              result.pop_back();//if we didn't find the word, we will move on to next
                                //die to find
            }
         }


         return result;
}


void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols) {
    new_board = new string*[*rows];
    for (unsigned int i=0; i<*rows; ++i){
      new_board[i] = new string[*cols];
    }
}

