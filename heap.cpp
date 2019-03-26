#include "heap.h"


//will implement methods for node first

//I will use this constructor to create my huffman nodes
node::node() {
  zero = NULL;
  one = NULL;
  frequency = 0;
  value = 0;
}

node::node(char x) {
  value = x;
  frequency = 0;
  zero = NULL;
  one = NULL;
}

//default destructor is okay since nothing is dynamically
//allocated inside of my node class

node::~node() {
  delete zero;
  delete one;
}


void node::addFrequency() {
  frequency++;
}

int node::getFrequency() {
  return frequency;
}

char node::getValue() {
  return value;
}

void node::giveFrequency() {
  //i have to make sure I don't call this on a leaf node
  frequency = zero->getFrequency() + one->getFrequency();
}

//implementing methods for heap class

heap::heap() {
  //since it is an implementation of a binary heap
  //and to use some of the useful arithmetic properties of
  //heap, i shouldn't use the zeroth index of the vector
  //therefore, I will initialize the vector with the first
  //element being empty
  my_heap.push_back(new node('z'));
  paths.reserve(100);
  heap_size = 0;
}

heap::~heap() {
  //need to destroy all dynamically allocated nodes

  //*****CHECK IF THIS WORKS AGAIN
  for (int i = 0; i < my_heap.size();i++) {
    delete my_heap[i];
  }

}

void heap::insert(node * x) {
  my_heap.push_back(x);
  heap_size++;
  percolateUp(heap_size);
}



node * heap::deleteMin() {
  if (heap_size == 0)
    throw "deleteMin() called on empty heap";
  //value to be returned (which is at the top) (at the first idx) 
  node * ret = my_heap[1];
  //move the last inserted thing into the root
  my_heap[1] = my_heap[heap_size];
  //remove the last element and
  my_heap.pop_back();
  heap_size--;
  //percolate the moved element down
  percolateDown(1);
  //return the root node
  return ret;
}


//code from class
void heap::percolateUp(int hole) {
  node * x = my_heap[hole];
  for ( ; (hole > 1) && (x->frequency < my_heap[hole/2]->frequency); hole /=2)
    my_heap[hole] = my_heap[hole/2];
  my_heap[hole] = x;
}

//code from class
void heap::percolateDown(int hole) {
    // get the value to percolate down
    node * x = my_heap[hole];
    // while there is a left child...
    while ( hole*2 <= heap_size ) {
        int child = hole*2; // the left child
        // is there a right child?  if so, is it lesser?
        if ( (child+1 <= heap_size) && 
             (my_heap[child+1]->frequency < my_heap[child]->frequency) )
            child++;
        // if the child is greater than the node...
        if ( x->frequency > my_heap[child]->frequency) {
            my_heap[hole] = my_heap[child]; // move child up
            hole = child;             // move hole down
        } else
            break;
    }
    // correct position found!  insert at that spot
    my_heap[hole] = x;
}


int heap::size() {
  return heap_size;
}


void heap::getPath(node * k, string j) {
  if (k->zero == NULL && k->one == NULL) {
    paths[(k->getValue())-32] = j;
  }
  if (k->zero != NULL) {
    string m = j;
    m.append("0");
    getPath(k->zero,m); 
  }
  if (k->one != NULL) {
    string p = j;
    p.append("1");
    getPath(k->one,p);
  }
}
