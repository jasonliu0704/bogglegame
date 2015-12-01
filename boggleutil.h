

#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H

#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;
//Data structures for lexicon and board should reside in this file.
//All of the operations your data structures support should be declared within your data structures.

class baseNode
{
   friend class BogglePlayer;
   friend class drawBoard;

   private:
      int index;
      bool Visited;
      string diceNum;
      vector<baseNode*>* adjacentList;

   public:
      baseNode( string& diceNum, int index );

      ~baseNode();

      void addAdjacentBaseNode( baseNode* node );
};

class drawBoard
{
   friend class BogglePlayer;

   private:
      vector<baseNode*>* baseNodes;

   public:
      drawBoard();

      ~drawBoard();

      void buildGraph( const int width, const int height, string** board );

};

class Lex
{
   private:
      int size;
      int capacity;
      vector<vector<string>* >* hashTable;
      int hash( const string& word );

   public:
      Lex();

      ~Lex();

     void build( const set<string>& word_list );

     bool findString( const string& word );

     vector<string> getValidString( unsigned int minLen );
};

#endif
