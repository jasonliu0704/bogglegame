

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
  }
  
  ~BogglePlayer() {
  }

  void push_neighbor(stack& nStack, int grid);
  getAllValidWordsRec(unsigned int minimum_word_length, set<string>* words, string word, int grid);

  private:
  MTrie lexicon;
  //board parameter
  unsigned int srow, scol, sborad;
  string* myBoard;
  bool * isVisited;
  //call indicator
  bool builtLex, setBoard;
};

#endif
