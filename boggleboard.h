/**
 *  CSE 100 C++ Boggle
 *  Authors: Vivek Ramavajjala, Paul Kube
 */

#ifndef BOGGLEBOARD_H
#define BOGGLEBOARD_H

#include <string>
#include <vector>
#include <set>

class Die {
public:
    std::vector<std::string> faces;
    Die();
    Die(const char* f1, const char* f2, const char* f3, const char* f4, const char* f5, const char* f6);
    ~Die();
    std::string getRandomFace();
};

class BoggleBoard {
  
public:
    std::string lexicon_filename;
    std::set<std::string> lexicon_words;
    unsigned int ROWS;
    unsigned int COLS;
    std::string **board;
    std::vector<Die*> diceBag;

private:
    void destroyBoard();
    void createBoard(unsigned int rows, unsigned int cols);

public:
    BoggleBoard(const char* lexfilename, unsigned int rows, unsigned int cols);
    ~BoggleBoard();
    /*Helper functions*/
    int returnIndex(unsigned int row, unsigned int col);
    std::vector<int> returnGridLocation(unsigned int index);

    /*Game functions*/
    void initDiceBag();
    void initRandomBoard();
    void setBoard(unsigned int rows, unsigned int cols, std::string **list);
};



#endif // BOGGLEBOARD_H
