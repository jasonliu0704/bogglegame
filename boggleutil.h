#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H

#include <string>
#include <unordered_map>
#include <regex>
#include <set>
using namespace std;
/**
 * Node of the multiway trie.
 */
class TNode {
  public:
    TNode(char value, bool eow);
    bool EOW;
    char val;
    int childNum;
    vector<TNode*> children;
};


class MTrie {
  public:
    TNode* root;
    MTrie(){};
    ~MTrie();
    bool clean(TNode* n);
    bool insert(string word);
    int search(string word);
};

#endif
