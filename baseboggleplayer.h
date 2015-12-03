/**
 *  CSE 100 C++ Boggle
 *  Authors: Vivek Ramavajjala, Paul Kube
 */

#ifndef BASEBOGGLEPLAYER_H
#define BASEBOGGLEPLAYER_H

#include <set>
#include <vector>
#include <string>

using std::vector;
using std::set;
using std::string;

/**
 *  The base class for any computer Boggle player.
 *  Subclass this, and provide definitions for all the
 *  public pure virtual member functions shown.
 *  See the README for detailed documentation on these functions.
 */
class BaseBogglePlayer {

  public:
  virtual void buildLexicon(const set<string>& word_list) = 0;
  virtual void setBoard(unsigned int rows, unsigned int cols, string** diceArray) = 0;
  virtual bool getAllValidWords(unsigned int minimum_word_length, set<string>* words) = 0;
  virtual bool isInLexicon(const string& word_to_check) = 0;
  virtual vector<int> isOnBoard(const string& word_to_check) = 0;
  virtual void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols) = 0;
  virtual ~BaseBogglePlayer() {}

};

#endif // BASEBOGGLEPLAYER_H
