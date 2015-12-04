

#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H
#include "baseboggleplayer.h"
#include "boggleutil.h"
#include <vector>
#include <string>
#include <set>
class BogglePlayer : public BaseBogglePlayer {
  public:
  void buildLexicon(const set<string>& word_list);
  
  void setBoard(unsigned int rows, unsigned int cols, string** diceArray); 

  bool getAllValidWords(unsigned int minimum_word_length, set<string>* words);
  
  bool isInLexicon(const string& word_to_check); 

  vector<int> isOnBoard(const string& word);

  void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols);

  bool isOnBoardRec(vector<int>& path, const string& word, int grid, string& myword);

  void push_neighbor(set<int>& nStore, int grid);
  void getAllValidWordsRec(unsigned int minimum_word_length, set<string>* words, string word, int grid);
  
  explicit BogglePlayer();
  ~BogglePlayer();
  private:
  MTrie lexicon;
  //board parameter
  int srow, scol, sboard;
  string* myBoard;
  bool * isVisited;
  //call indicator
  bool builtLex, setboard;
};

#endif
