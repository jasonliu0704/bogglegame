
/******************************************************
 * Tester file to test basic functionality of your code
 * ****************************************************/

#include "baseboggleplayer.h"
#include "boggleplayer.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <sstream>
#include <ctime>

using namespace std;

int main (int argc, char* argv[]) {
    BaseBogglePlayer* p = new BogglePlayer();
    
    ifstream infile;
    infile.open("lex.txt");

    if(!infile.is_open()) {
        cout << "Could not open lexicon file - exiting." << endl;
        exit(-1);
    }
  
    cout<< "Reading lexicon..." << endl;
    
    set<string> lex;
    string word;
    int lexSize = 0;
    
    while(infile.is_open() && infile.good()) {
        getline(infile,word);
        
        if(word.size() < 1) continue;
        
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        lex.insert(word);
        ++lexSize;
    }

    infile.close();
    cout << lexSize << " words in the lexicon" << endl;

    infile.open("brd.txt");
    
    if(!infile.is_open()) {
        cout << "Could not open board file - exiting." << endl;
        exit(-1);
    }

    cout << "Reading board..." << endl;
    
    getline(infile, word);
    int rows = atoi(word.c_str());

    getline(infile, word);
    int cols = atoi(word.c_str());

    unsigned int *a = new unsigned int;
    *a = 20;
    unsigned int *b = new unsigned int;
    *b = 23;

    string ** board;
    p->getCustomBoard(board, a, b);

    int x = 0;
    int y = 0;
    while(infile.is_open() && infile.good()) {
        getline(infile,word);
        
        if(word.size() < 1) continue;
        
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        board[x][y % cols] = word;
        
        ++y;

        if(y % cols == 0) {
            ++x;
        }
    }

    infile.close();
    cout << "Board loaded with " << rows << " rows and " << cols << " cols" << endl;

    set<string> words;
    vector<int> locations;

    p->buildLexicon(lex);

    p->setBoard(20,23,board);

    cout << "Getting all valid words..." << endl;
    
    clock_t begin = clock();

    p->getAllValidWords(2, &words);

    clock_t end = clock();

    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    stringstream secs;
    secs << elapsed_secs;

    if(words.size() != 5450) {
        cerr << "Error with getAllValidWords" << endl;
        return -1;
    }

    cout << words.size() << " valid words on the board found in " + secs.str() + " seconds" << endl;

    delete p;
    return 0;
}
