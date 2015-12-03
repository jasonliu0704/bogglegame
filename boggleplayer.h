

#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H
#include "baseboggleplayer.h"
#include "boggleutil.h"
using namespace std;

class BogglePlayer : public BaseBogglePlayer {
  public:
  void buildLexicon(const set<string>& word_list);
  
  void setBoard(unsigned int rows, unsigned int cols, string** diceArray); 

  bool getAllValidWords(unsigned int minimum_word_length, set<string>* words);
  
  bool isInLexicon(const string& word_to_check); 

  vector<int> isOnBoard(const string& word);

  void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols);

  BogglePlayer() {
    lexicon = new MTrie();
    node = new TNode();
    visited = false;
    buildLex = false;
    setBoard = false;
  }
  
  ~BogglePlayer() {
  }

  private:
  MTrie lexicon;
  //board parameter
  unsigned int srow, scol, sboard;
  string* myBoard;
  //call indicator
  bool builtLex, setBoard;
  bool visited;

  bool checkPrefix(const string& prefix, const string& word);
};

#endif
