#include "boggleutil.h"
#include <iostream>
using namespace std;


bool WordTrie::search(string word) {
  int i = 0;
  TNode* cur = root; 
  
  while(1){
    if(cur == 0 || i > word.length()){
      return false;
    }else if(cur->EOW && i == word.length()){
      return true;
    }else{
      cur = (cur->children).at(word.at(i) - 'a');
      i++;
    }
  }
}

TNode::TNode(char value, bool eow){
  EOW = eow;
  val = value;
}

bool MTrie::insert(string word) {
  TNode* cur = root;
  int i = 0;

  while(1){

    //check whether the node contains the letter exists
    if((cur->children).at(word.at(i) - 'a') == 0){
      //if not, then creat a new one for it
      cur->childNum++;
      (cur-children).at(word.at(i) - 'a') = new TNode(word.at(i), 
      (i == word.size() - 1) ? true : false);
    }
    
    //go check next letter
    cur = cur = (cur-children).at(word.at(i) - 'a');
    i++;

    //check EOW
    if(i == word.size()) return true;
  }

  return false;
}

MTrie::MTrie(){
  root = new TNode(' ', false);
}

MTrie::~MTrie() {
  clean(root);
  delete root;
  root = NULL;
}

MTrie::clean(TNode* n){
  //base case, n's children array has 0 node
  if(n->childNum == 0){
    return;
  }
  
  //loop through and clean all its children node
  for(auto& node : n->children){
    clean(node);
    delete node;
    node == 0;
  }
}
