

#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <string>

using namespace std;

class node {
 public:
  node();
  node(char x);
  ~node();
  //void setChar(char x);
  void addFrequency();
  int getFrequency();
  char getValue();
  void giveFrequency();
  node * zero;
  node * one;
  char value;
 private:
  int frequency;
  friend class heap;
};

class heap {
 public:
  heap();
  ~heap();
  void insert(node * x);
  node * deleteMin();
  int size();
  void getPath(node * k,string j);
  vector <string> paths;
 private:
  vector <node*> my_heap;
  void percolateUp(int hole);
  void percolateDown(int hole);
  int heap_size;
};


#endif
