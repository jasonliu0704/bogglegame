/**
 *  CSE 100 C++ Boggle
 *  Authors: Vivek Ramavajjala, Paul Kube
 */

#include "boggleboard.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

BoggleBoard::BoggleBoard(const char* lexfilename,
			 unsigned int rows,
			 unsigned int cols) {
  // Initialize the board
  createBoard(rows, cols);
  initDiceBag();

  // Initialize the lexicon
  this->lexicon_filename = lexfilename;
  std::ifstream infile;
  infile.open(this->lexicon_filename.c_str());
  if(! infile.is_open()) {
    std::cout<<"Could not open lexicon file " << lexfilename << ", exiting." <<std::endl;
    exit(-1);
  }
  std::cout<<"Reading lexicon from " << lexfilename << "..." <<std::endl;
  std::string word;
  int i=0;
  this->lexicon_words.clear();
  while(infile.is_open() && infile.good())
    {
      std::getline(infile,word);
      if(word.size() < 1) continue;
      // lowercase the word
      //      std::cerr << word << std::endl;
      std::transform(word.begin(), word.end(), word.begin(), ::tolower);
      //      std::cerr << " to " << word << std::endl;
      this->lexicon_words.insert(word);
      i++;
    }
  std::cout << this->lexicon_words.size() << " distinct words read from " << lexfilename << "." <<std::endl;
  infile.close();


  srand(time(NULL));
}

BoggleBoard::~BoggleBoard() {
  diceBag.clear();
}

int BoggleBoard::returnIndex(unsigned int row, unsigned int col) {
  //Assuming row,col are indexed from 0
  return row*COLS + col;
}

std::vector<int> BoggleBoard::returnGridLocation(unsigned int index) {
  //Assuming indexing starts from 0
  std::vector<int> gridLocation;
  int rowIndex = index / this->COLS;
  int colIndex = index % this->COLS;
  gridLocation.push_back(rowIndex);
  gridLocation.push_back(colIndex);
  return gridLocation;
}

void BoggleBoard::initDiceBag() {
  this->diceBag.push_back(new Die("A", "O", "B", "B", "O", "J"));
  this->diceBag.push_back(new Die("W", "H", "G", "E", "E", "N"));
  this->diceBag.push_back(new Die("N", "R", "N", "Z", "H", "L"));
  this->diceBag.push_back(new Die("N", "A", "E", "A", "G", "E"));
  this->diceBag.push_back(new Die("D", "I", "Y", "S", "T", "T"));
  this->diceBag.push_back(new Die("I", "E", "S", "T", "S", "O"));
  this->diceBag.push_back(new Die("A", "O", "T", "T", "W", "O"));
  this->diceBag.push_back(new Die("H", "Qu", "U", "M", "N", "I"));
  this->diceBag.push_back(new Die("R", "Y", "T", "L", "T", "E"));
  this->diceBag.push_back(new Die("P", "O", "H", "C", "S", "A"));
  this->diceBag.push_back(new Die("L", "R", "E", "V", "Y", "D"));
  this->diceBag.push_back(new Die("E", "X", "L", "D", "I", "R"));
  this->diceBag.push_back(new Die("I", "E", "N", "S", "U", "E"));
  this->diceBag.push_back(new Die("S", "F", "F", "K", "A", "P"));
  this->diceBag.push_back(new Die("I", "O", "T", "M", "U", "C"));
  this->diceBag.push_back(new Die("E", "H", "W", "V", "T", "R"));
}

void BoggleBoard::initRandomBoard() {
  //Random boards are 4x4
  destroyBoard();
  createBoard(4, 4);
  for(unsigned int r=0;r<ROWS;r++)  {
    for(unsigned int c=0;c<COLS;c++)   {
      int index = this->returnIndex(r, c) % this->diceBag.size();
      std::string face = this->diceBag[index]->getRandomFace();
      this->board[r][c] = face;
    }
  }
}

void BoggleBoard::setBoard(unsigned int rows, unsigned int cols, std::string **list) {
  destroyBoard();
  createBoard(rows, cols);
  //    std::cout<<ROWS<<" "<<COLS<<std::endl;
  for(unsigned int r=0;r<ROWS;r++)    {
    for(unsigned int c=0;c<COLS;c++)        {
      this->board[r][c] = list[r][c];
    }
  }
}


void BoggleBoard::destroyBoard() {
  for(unsigned int i=0;i<ROWS;i++) {
    delete[] board[i];
  }
  delete[] board;
}

void BoggleBoard::createBoard(unsigned int rows, unsigned int cols) {
  //Assumes boggle_board and boggle_board_indexed don't already exist.
  ROWS = rows;
  COLS = cols;
  this->board = new std::string*[ROWS];
  for(unsigned int r=0; r < ROWS; r++) {
    this->board[r] = new std::string[COLS];
  }
}


Die::Die() { }

Die::Die(const char* f1, const char* f2, const char* f3, const char* f4, const char* f5, const char* f6) {
  faces.push_back(std::string(f1));
  faces.push_back(std::string(f2));
  faces.push_back(std::string(f3));
  faces.push_back(std::string(f4));
  faces.push_back(std::string(f5));
  faces.push_back(std::string(f6));
}

Die::~Die() {
  faces.clear();
}

std::string Die::getRandomFace() {
  int rand_num = rand() % 6;
  return faces[rand_num];
}

