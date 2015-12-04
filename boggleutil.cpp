#include "boggleutil.h"
//#include <iostream>
using namespace std;

//return 0 for not a word and prefix, 1 for prefix, 2 for word
int MTrie::search(string word) {
  unsigned int i = 0;
  TNode* cur = root; 
  
  while(1){
    if(cur == 0 || i > word.length()){
      return 0;
    }else if(i == word.length()){
      if(cur->EOW){
        return 2;
      }else{
        return 1;
      }
    }else{
      cur = (cur->children).at(word.at(i) - 'a');
      i++;
    }
  }
}

MTrie::MTrie(){
  root = new TNode(' ', false);
}

TNode::TNode(char value, bool eow){
  EOW = eow;
  val = value;
  children.resize(26);
}

bool MTrie::insert(string word) {
  TNode* cur = root;
  unsigned int i = 0;

  while(1){

    //check whether the node contains the letter exists
    if((cur->children).at(word.at(i) - 'a') == 0){
      //if not, then creat a new one for it
      cur->childNum++;
      (cur->children).at(word.at(i) - 'a') = new TNode(word.at(i),false); 
      //(i == (word.size() - 1) ? true : false);
    }
    
    //go check next letter
    cur = (cur->children).at(word.at(i) - 'a');
    i++;

    //check EOW
    if(i == word.size()){
      cur->EOW = true;
      return true;
    }
  }

  return false;
}


MTrie::~MTrie() {
  clean(root);
  delete root;
  root = NULL;
}

void MTrie::clean(TNode* n){
  //base case, n's children array has 0 node
  if(n == 0){
    return;
  }
  
  //loop through and clean all its children node
  for(auto& node : n->children){
    clean(node);
    delete node;
    node = 0;
  }
}
