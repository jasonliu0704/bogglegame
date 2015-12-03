

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
  //set up board and isvisted and if they exits before, reset it
  if(myBoard) delete[] myBoard;
  if(isVisited)delete[] isVisited;

  myBoard = new string[sboard];
  isVisited = new bool[sboard];

  //convert 2d array into 1d
  for(int i = 0 ; i < rows; i++){
    for(int j = 0; j < cols; j++){
      //lower case
      myBoard[i*cols + j] = tolower(diceArray[i][j]);
    }
  }
}



bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words) {
  //set is visited indicator

  //set check
  if(!builtLex || !setBoard) return false;

  // make sure isvisited is false
  for(int i=0; i<BOARDSIZE; i++) {
    isVisited[i] = false;
  }

  //find words by DFS the board, start with each grid
  for(int grid = 0; grid < sboard ; grid ++){

    string word = myBoard[grid];

    //check validity and attributes for the start letter
    int result = lexicon.search(word);
    switch(result){

      //not a word and prefix
      case 0 :
        break;
      //prefix
      case 1 :
        isVisited[grid] = true;
        getAllValidWordsRec(minimum_word_length, words, word, grid);
        isVisited[grid] = false;
        break;
      //is a word
      case 2 :
        if(word.length() >= minimum_word_length)words.push_back(word);
        isVisited[grid] = true;
        getAllValidWordsRec(minimum_word_length, words, word, grid);
        isVisited[grid] = false;
        break;
    }
  }
  return true;
}

void BogglePlayer::getAllValidWordsRec(unsigned int minimum_word_length, set<string>* words, string word, int grid){
  
  //store neighbor grid die
  vector<int> nStore;
  push_neighbor(nStore, grid);

  //loop through neighbor grid
  for(auto neigh : nStore){
    //if not visitied
    if(!isVisited[neigh]){
      string newWord = word;
      newWord.push_back(myBoard[neigh]);
      //check the word in lexicon
      int result = lexicon.search(word);
      //not a prefix and not in lexicon
      if(result == 0){
        continue;
      }
      //it is in the lexicon
      if(result == 2 && newWord.length() >=  minimum_word_length){
        words->push_back(newWord);
      }
      isVisited[neigh] == true;
      //is a prefix and check out other neighbors
      getAllValidWordsRec(min, words, newWord, neigh);
      isVisited[neigh] = false;
    }
  }
}

          
void BogglePlayer::push_neighbor(vector<int>& nStore, int grid){
      if(grid + 1 < sboard)nStore.push_back(grid + 1);
      if(grid - 1 > 0)nStore.push_back(grid - 1);
      if(grid - srow - 1 > 0)nStore.push_back(grid - srow - 1);
      if(grid - srow > 0)nStore.push_back(grid - srow);
      if(grid - srow + 1 > 0)nStore.push_back(grid - srow + 1);
      if(grid + srow < sboard)nStore.push_back(grid + srow);
      if(grid + srow - 1 < sboard)nStore.push_back(grid + srow - 1);
      if(grid + srow + 1 < sboard)nStore.push_back(grid + srow + 1);
}

bool BogglePlayer::isInLexicon(const string& word_to_check) {
  if(lexicon.search(word_to_check) == 2){return true;}
  else {return false;}
}

vector<int> BogglePlayer::isOnBoard(const string& word) {
  vector<int> path;
  if(!setBoard || !builtLex)return path;

  //reset isVisit
  for(int i=0; i < sboard; i++){
    isVisited[i] = false;
  }

  //in case user typed in upper case, convert to lower cases
  string lword;
  for(int i=0; i < word.length(); i++){
    lword[i] = tolower(word[i]);
  }

  //start from first grid to loop through
  for(int grid = 0; grid < sboard; grid++){
    //check if the first gird is prefix of the word
    if(lword.find(myBoard[grid] !=  string::npos)){
      //update path
      path.push_back(grid);
      //if we find the word
      if(lword.compare(myBoard[grid] == 0)){
        break;
      }
      
      //recurse and check if it is on my board
      bool


}

bool BogglePlayer::isOnBoardRec(vector<int>& path, const string& word){
  //store neighbor dies
  vector<int> ndie;
  push_neighbor(ndie, int grid)
void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols) {
}

