

#include "boggleplayer.h"
BogglePlayer::BogglePlayer() {
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

vector<int> BogglePlayer::isOnBoard(const string& word) {
         vector<int> result;
         return result;
}


void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols) {
}

