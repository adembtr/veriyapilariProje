#include "queue.hpp"

NodeQueue::NodeQueue(BST* tr , NodeQueue* nx){
    this->tree = tr;
    this->next = nx;
}

Queue::Queue(){
    front = back = NULL;
    length = 0;
}

Queue::~Queue(){
    NodeQueue* current = front;
    while(current != NULL){
        NodeQueue* temp = current;
        current = current->next;
        delete temp->tree;
        delete temp;
    }
}

void Queue::enqueue(BST* tree){
    if(length >= 6){
        delete tree;
        return;
    }
        
    NodeQueue* yeniNode = new NodeQueue(tree, NULL);
    
    if(front == NULL) {
        front = back = yeniNode;
    } else {
        back->next = yeniNode;
        back = yeniNode;
    }
    length++;    
}

int Queue::getFrontRoot(){
    if(front == NULL) return -1;
    
    NodeQueue* ptr = front;
    while(ptr != NULL){
        if(ptr->tree->getRoot() != -1){
            return ptr->tree->getRoot();
        }
        ptr = ptr->next;
    }
    return -1;
}

int Queue::getPriorityRoot(){
    if(front == NULL) return -1;
    
    NodeQueue* ptr = front;
    NodeQueue* maxNode = NULL;
    int maxHeight = -1;
    
    while(ptr != NULL){
        if(ptr->tree->getRoot() != -1){
            int h = ptr->tree->getHeight();
            if(h > maxHeight){
                maxHeight = h;
                maxNode = ptr;
            }
        }
        ptr = ptr->next;
    }
    
    if(maxNode == NULL) return -1;
    return maxNode->tree->getRoot();
}

int Queue::getLength(){
    return length;
}

BST* Queue::getTreeAt(int index){
    if(front == NULL || index < 0) return NULL;
    
    NodeQueue* ptr = front;
    int i = 0;
    
    while(ptr != NULL && i < index){
        ptr = ptr->next;
        i++;
    }
    
    if(ptr == NULL) return NULL;
    return ptr->tree;
}

bool Queue::isEmpty(){
    return (front == NULL);
}

BST* Queue::getPriorityTree(){
    if(front == NULL) return NULL;
    
    NodeQueue* ptr = front;
    NodeQueue* maxNode = NULL;
    int maxHeight = -1;
    
    while(ptr != NULL){
        if(ptr->tree->getRoot() != -1){
            int h = ptr->tree->getHeight();
            if(h > maxHeight){
                maxHeight = h;
                maxNode = ptr;
            }
        }
        ptr = ptr->next;
    }
    
    if(maxNode == NULL) return NULL;
    return maxNode->tree;
}

BST* Queue::getTreeAtPosition(int startIndex){
    if(front == NULL || length == 0) return NULL;
    
    for(int i = 0; i < length; i++){
        int index = (startIndex + i) % length;
        BST* tree = getTreeAt(index);
        if(tree != NULL && tree->getRoot() != -1){
            return tree;
        }
    }
    return NULL;
}