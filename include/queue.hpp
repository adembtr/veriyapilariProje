#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "BSTlist.hpp"
#include <iostream>
using namespace std;

struct NodeQueue{
    BST* tree;
    NodeQueue* next;
    
    NodeQueue(BST* tr , NodeQueue* nx);
};

class Queue{
private:
    NodeQueue* front;
    NodeQueue* back;
    int length;

public:
    Queue();
    ~Queue();

    void enqueue(BST* tree);
    //kökü döndürüyor
    int getFrontRoot();
    //öncelikliyi döndürüyor
    int getPriorityRoot();
    int getLength();

     // indexe gore ağaç getiriyor.
     BST* getTreeAtPosition(int startIndex); 
    BST* getTreeAt(int index); 

    
    bool isEmpty();
    BST* getPriorityTree(); // oncelikliyi getiriyor
};
#endif