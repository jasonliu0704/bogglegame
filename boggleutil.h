#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H

#include <string>
#include <vector>
using namespace std;
/**
 * Node of the multiway trie.
 */
class TNode {
  public:
    explicit TNode(char value, bool eow);
    bool EOW;
    char val;
    int childNum;
    vector<TNode*> children;
};


class MTrie {
  public:
    TNode* root;
    explicit MTrie();
    ~MTrie();
    void clean(TNode* n);
    bool insert(string word);
    int search(string word);
};

#endif
