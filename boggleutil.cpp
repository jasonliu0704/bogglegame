#include <algorithm>
#include <vector>
#include <string>
#include"boggleutil.h"

using namespace std;
//In this file, implement all of the operations your data structures support (you have declared these operations in boggleutil.h).

   BoardNode::BoardNode( string& diceStr, int index ): diceStr( diceStr ),
   index( index ), wasVisited( false ), adjList( new vector<BoardNode*>() )
   {}

   BoardNode::~BoardNode()
   {
      delete adjList;
   }

   void BoardNode::addAdjacentBoardNode( BoardNode* node )
   {
      adjList->push_back( node );
   }

   BoardGraph::BoardGraph() : boardNodes( new vector<BoardNode*>() )
   {}

   BoardGraph::~BoardGraph()
   {
      for( unsigned int i = 0; i < boardNodes->size(); i++ )
      {
         delete boardNodes->at( i );
      }
      delete boardNodes;
   }

   void BoardGraph::buildGraph( const int width, const int height, string** board )
   {
      BoardNode*** nodes = new BoardNode**[height];
      for( int i = 0; i < height; i++ )
      {
         nodes[i] = new BoardNode*[width];
      }

      for( int row = 0; row < height; row++ )
      {
         for( int col = 0; col < width; col++ )
         {
            string str = board[row][col];
            transform( str.begin(), str.end(), str.begin(), ::tolower );
            nodes[row][col] = new BoardNode( str, row*width + col );
         }
      }

      for( int row = 0; row < height; row++ )
      {
         for( int col = 0; col < width; col++ )
         {
            if( col - 1 >= 0 )
            {
               nodes[row][col]->addAdjacentBoardNode( nodes[row][col-1] );
            }
            if( col - 1 >= 0 && row - 1 >= 0 )
            {
               nodes[row][col]->addAdjacentBoardNode( nodes[row-1][col-1] );
            }
            if( row - 1 >= 0 )
            {
               nodes[row][col]->addAdjacentBoardNode( nodes[row-1][col] );
            }
            if( row - 1 >= 0 && col + 1 < width )
            {
               nodes[row][col]->addAdjacentBoardNode( nodes[row-1][col+1] );
            }
            if( col + 1 < width )
            {
               nodes[row][col]->addAdjacentBoardNode( nodes[row][col+1] );
            }
            if( row + 1 < height && col + 1 < width )
            {
               nodes[row][col]->addAdjacentBoardNode( nodes[row+1][col+1] );
            }
            if( row + 1 < height )
            {
               nodes[row][col]->addAdjacentBoardNode( nodes[row+1][col] );
            }
            if( row + 1 < height && col - 1 >= 0 )
            {
               nodes[row][col]->addAdjacentBoardNode( nodes[row+1][col-1] );
            }
         }
      }

      for( int row = 0; row < height; row++ )
      {
         for( int col = 0; col < width; col++ )
         {
            boardNodes->push_back( nodes[row][col] );
         }
      }

      for( int i = 0; i < height; i++ )
      {
         delete [ ] nodes[i];
      }

      delete [ ] nodes;
   }

   Lexicon::Lexicon() : size( 0 ), capacity( 0 ), hashTable( 0 )
   {}

   Lexicon::~Lexicon()
   {
      for( unsigned int i = 0; i < hashTable->size(); i++ )
      {
         delete hashTable->at( i );
      }
      delete hashTable;
   }

   int Lexicon::hash( const string& word )
   {
      long hashVal = 0;
      
      for( unsigned int i = 0; i < word.length(); i++ )
      {
         hashVal = ( hashVal << 4 ) + word.at( i );
         long g = hashVal & 0xF0000000L;
         if( g != 0 )
         {
            hashVal ^= g >> 24;
         }
         hashVal &= ~g;
      }

      return (int)( hashVal % capacity );
   }

   void Lexicon::build( const set<string>& wordList )
   {
      size = wordList.size();
      capacity = (int) ( 1.3 * wordList.size() );
      hashTable = new vector<vector<string>* >( capacity, (vector<string>*) 0 );
      
      set<string>::iterator it = wordList.begin();
      set<string>::iterator en = wordList.end();

      for( ; it != en; ++it )
      {
         int index = hash( *it );
         if( ! hashTable->at( index ) )
         {
            hashTable->at( index ) = new vector<string>();
         }
         hashTable->at( index )->push_back( *it );
      }
   }

   bool Lexicon::findWord( const string& word )
   {
      if( !hashTable )
      {
         return false;
      }

      int index = hash( word );
      
      if( !(hashTable->at( index )) )
      {
         return false;
      }

      vector<string>::iterator it = hashTable->at( index )->begin();
      vector<string>::iterator en = hashTable->at( index )->end();

      for( ; it != en; ++it )
      {
         if( *it == word )
         {
            return true;
         }
      }

      return false;
   }

   vector<string> Lexicon::getValidWords( unsigned int minLength )
   {
      vector<string> results;
      results.clear();
      if( !hashTable )
      {
         return results;
      }

      vector<vector<string>* >::iterator it = hashTable->begin();
      vector<vector<string>* >::iterator en = hashTable->end();

      for( ; it != en; ++it)
      {
         if( *it )
         {
            for( unsigned int i = 0; i < (*it)->size(); i++ )
            {
               if( (*it)->at( i ).length() >= minLength )
               {
                  results.push_back( (*it)->at( i ) );
               }
            }
         }
      }

      return results;
   }
