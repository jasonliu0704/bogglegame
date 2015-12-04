#include "boggleplayer.h"
#include <vector>
#include <string>
#include <set>
#include <locale>
#include <array>
#include <iostream>
using namespace std;

BogglePlayer::BogglePlayer() {
  builtLex = false;
  setboard = false;
}

BogglePlayer::~BogglePlayer(){
  delete[] isVisited;
  delete[] myBoard;
  isVisited = 0;
  myBoard = 0;
}



void BogglePlayer::buildLexicon(const set<string>& word_list){
  //clear the lexicon bebore buid
  lexicon.clean(lexicon.root);
  //delete lexicon.root;
  //lexicon.root = 0;

  //insert words into the lexicon datastructure
  for(set<string>::iterator it = word_list.begin(); it != word_list.end(); it++){
    lexicon.insert(*it);
  }

  builtLex = true;
}

void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray) {
  //set up board parameter
  scol = cols;
  srow = rows;
  sboard = cols * rows;
  //set up board and isvisted and if they exits before, reset it
  if(myBoard) delete[] myBoard;
  if(isVisited)delete[] isVisited;

  myBoard = new string[sboard];
  isVisited = new bool[sboard];

  //convert 2d array into 1d
  for(int i = 0; i < sboard; i++){
    myBoard[i] = diceArray[i/scol][i%scol];

    //lower case
    for(unsigned int j = 0; j < myBoard[i].size(); j++){
      myBoard[i][j] = tolower(myBoard[i][j]);
    }
  }
  setboard = true;
}



bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words) {

  //set check
  if(!builtLex || !setboard) return false;

  // make sure isvisited is false
  for(int i=0; i<sboard; i++) {
    isVisited[i] = false;
  }

  //find words by DFS the board, start with each grid
  for(int grid = 0; grid < sboard ; grid ++){
    string word = myBoard[grid];

    //check validity and attributes for the start letter
    int result = lexicon.search(word);
    
    //not in here
    if(result == 0){ continue;}
    //we find a word
    else if(word.size() > minimum_word_length && result == 2){
      words->insert(word);
    }
    else{
      isVisited[grid] = true;
      //recurse
      getAllValidWordsRec(minimum_word_length, words, word,grid);
      isVisited[grid] = false;
    }
  }
  return true;
}
    

    
void BogglePlayer::push_neighbor(vector<int>& nStore, int grid){
      if((grid + 1 < sboard) && (grid%scol != 0))nStore.push_back(grid + 1);
      if((grid - 1 > 0) && (grid %scol != 1))nStore.push_back(grid - 1);
      if((grid - scol - 1 >= 0) && (grid %scol != 1))nStore.push_back(grid - scol - 1);
      if(grid - scol > 0)nStore.push_back(grid - scol);
      if((grid - scol + 1 >= 0) && (grid%scol != 0))nStore.push_back(grid - scol + 1);
      if(grid + scol < sboard)nStore.push_back(grid + scol);
      if((grid + scol - 1 < sboard) && (grid %scol != 1))nStore.push_back(grid + scol - 1);
      if((grid + scol + 1 < sboard) && (grid%scol != 0))nStore.push_back(grid + scol + 1);
}

void BogglePlayer::getAllValidWordsRec(unsigned int minimum_word_length, set<string>* words, string word, int grid){
  
  //store neighbor grid die
  vector<int> nStore;
  push_neighbor(nStore, grid);

  for (auto neigh : nStore){
    
  //loop through neighbor grid
    //cout << neigh << endl;
    string newWord = word;
    //if not visitied
    if(!isVisited[neigh]){
      
      newWord.append(myBoard[neigh]);
            //cout << newWord << endl;
      //check the word in lexicon
      int result = lexicon.search(newWord);
      //not a prefix and not in lexicon
      if(result == 0){
        continue;
      }
      //it is in the lexicon
      if(result == 2 && newWord.length() >=  minimum_word_length){
        //cout << newWord << endl;
        words->insert(newWord);
      }
      isVisited[neigh] = true;
      //is a prefix and check out other neighbors
      getAllValidWordsRec(minimum_word_length, words, newWord, neigh);
      isVisited[neigh] = false;
    }
  }
}

          

bool BogglePlayer::isInLexicon(const string& word_to_check) {
  if(lexicon.search(word_to_check) == 2){return true;}
  else {return false;}
}



vector<int> BogglePlayer::isOnBoard(const string& word) {
  vector<int> path;
  if(!setboard)return path;

  //reset isVisit
  for(int i=0; i < sboard; i++){
    isVisited[i] = false;
  }
  
  //in case user typed in upper case, convert to lower cases
  string lword = word;
  for(unsigned int i=0; i < word.length(); i++){
    lword[i] = tolower(word[i]);
  }

  //start from first grid to loop through
  for(int grid = 0; grid < sboard; grid++){
    string myword;
    myword.append(myBoard[grid]);
    //check if the first gird is prefix of the word
    if(lword.substr(0,myBoard[grid].size()).compare(myBoard[grid]) == 0){
      //update path
      path.push_back(grid);
      //if we find the word
      if(lword.compare(myBoard[grid]) == 0){
        break;
      }
      
      //recurse and check if it is on my board
      bool check = isOnBoardRec(path, word,grid,myword);
      if(check) break;

      //if not found on this starting point
      path.pop_back();
    }
  }
  return path;
}





bool BogglePlayer::isOnBoardRec(vector<int>& path, const string& word, int grid, string& myword){
  //store neighbor dies
  vector<int> ndie;
  push_neighbor(ndie,grid);
  
  //iterate over its neighbors
  for (auto neigh : ndie){
    //check whether visited
    if(!isVisited[neigh]){
      //put it into myword
      myword.append(myBoard[neigh]);
      cout << myword << endl;

      //check prefix
      if(word.substr(0,myBoard[neigh].size()).compare(myBoard[neigh]) == 0){
        path.push_back(neigh);
        isVisited[neigh] = true;

        //if we found the word at this point
        if(word.compare(myword) == 0) return true;

        //check whether the word is on board
        int check = isOnBoardRec(path, word, neigh, myword);
        if(check)return true;

        //not found
        path.pop_back();
        isVisited[neigh] = false;
      }
    }
  }
  return false;
}




void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols) {
  new_board = new string*[*rows];
  for(unsigned int i = 0; i < *rows; ++i) {
      new_board[i] = new string[*cols];
  }
}

