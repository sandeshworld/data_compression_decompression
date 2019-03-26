// included so we can use cout
#include <iostream>
// stdlib.h is where exit() lives
#include <stdlib.h>
#include <sstream>

#include "heap.h"

using namespace std;

// include the standard I/O library
#include <stdio.h>



// we want to use parameters
int main (int argc, char **argv) {
    // verify the correct number of parameters
    if ( argc != 2 ) {
        cout << "Must supply the input file name as the one and only parameter" << endl;
        exit(1);
    }
    // attempt to open the supplied file.  FILE is a type desgined to
    // hold file pointers.  The first parameter to fopen() is the
    // filename.  The second parameter is the mode -- "r" means it
    // will read from the file.
    FILE *fp = fopen(argv[1], "r");
    // if the file wasn't found, output and error message and exit
    if ( fp == NULL ) {
        cout << "File '" << argv[1] << "' does not exist!" << endl;
        exit(2);
    }

    //________________________________________________________________
    //In the following section I create a vector with the nodes that store
    //char and the frequency of the char occuring in the text

    node * charNodes[95];
    //initialize the vector with all possible characters
    //there are a total of 95 ascii values that we have to take care of
    //starting from value 32 to 126
    for (int z = 0; z < 95; z++) {
      charNodes[z] = NULL; 
    }

    //cout << sizeof(charNodes) << endl;
    //charNodes[1]->addFrequency();
    //cout << charNodes[1]->getFrequency() << endl;

    
    //node k;
    //cout << sizeof(k)*95 << endl;

    
    //while go through text in file and then add to frequency per encounter

    //initialize to all being false
    bool exists[95];
    for (int r = 0; r < 95; r++) {
      exists[r] = false;
    }
    
    //cout << sizeof(exists) << endl;
    
    
    int ds = 0;
    char g;
    int symbols = 0; 
    while ( (g = fgetc(fp)) != EOF ){
      if (32 <= g && g < 127) {
	int m = (int) g;
	//cout << "I am here" << m-32 <<endl;
	if (charNodes[m-32] == NULL) {
	  charNodes[m-32] = new node(g);
	  symbols++;
	}
	charNodes[m-32]->addFrequency();
	exists[m-32] = true;
	ds++;
      }
    }

    

    
    //__________________________________________________________
    //ok so now I have an array with all the characters given
    //now i will add it to my heap one by one
    // cout << "I am here" << endl;
    heap myHeap;
    //loop through my array and then add one by one to the heap and then use
    //find min to build the huffman tree
    for (int k = 0; k < 95; k++) {
      if (exists[k])
	myHeap.insert(charNodes[k]);
    }

    //cout << sizeof(myHeap) << endl;
    //now i will try to build the tree by pulling two mins at a time
    //and connecting them to a parent
    
    //____________________________________________________
    //building my huffman tree

    



    
    while (myHeap.size() > 1) {
      node * k = new node();
      k->one = myHeap.deleteMin();
      // cout << k->zero->getValue() << endl;
      k->zero = myHeap.deleteMin();
      // cout << k->one->getValue() << endl;
      k->giveFrequency();
      myHeap.insert(k);
    }


    //I will do a preorder traversal to find the prefixes
    node * root = myHeap.deleteMin();
    string l("");
    myHeap.getPath(root,l);
    for (int d = 0; d < 95; d++) {
      if (exists[d]) {
	if (d == (' '-32))
	  cout << "space" << " "  << myHeap.paths[d] << endl;
	else 
	  cout << (char) (d+32) << " "  << myHeap.paths[d] << endl;
    }
    }
    cout << "----------------------------------------" << endl;
    
    // read the file again, and print to the screen
    
    string encoded("");
    rewind(fp);
    char qu;
    while ( (qu = fgetc(fp)) != EOF ) {
      if (exists[qu-32]) {
	cout << myHeap.paths[qu-32] << " ";
	encoded.append(myHeap.paths[qu-32]);
      }
      }
    double cost = 0;
    for (int d = 0; d < 95; d++) {
      if (exists[d]) {
	cost += myHeap.paths[d].size()*((charNodes[d]->getFrequency())/(1.0 + ds-1.0));
    }
    }
    
    cout << endl;
    cout << "----------------------------------------" << endl;
    cout << "There are a total of " << ds << " symbols that are encoded." << endl;
    cout << "There are " << symbols << " distinct symbols used." << endl;
    cout << "There were " << ds * 8 << " bits in the original file." << endl;
    cout << "There were " << encoded.size() << " bits in the compressed file." << endl;
    double ratio = (ds*8)/(encoded.size()+1.0-1.0);
    cout << "This gives a compression ratio of " << ratio  <<"."<<endl;
    cout << "The cost of the Huffman tree is " << cost << " bits per character."<< endl;
    
    
    
    
    /**
      //cout << g;
      
    // a nice pretty separator
    cout << "----------------------------------------" << endl;
    // rewinds the file pointer, so that it starts reading the file
    // again from the begnning
    rewind(fp);
    // read the file again, and print to the screen
    while ( (g = fgetc(fp)) != EOF )
        cout << g;
    // close the file
    **/
    fclose(fp);
}
