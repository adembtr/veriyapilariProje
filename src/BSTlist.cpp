#include "BSTlist.hpp"
#include <iostream>


NodeTree::NodeTree(const int& dt , NodeTree* rg , NodeTree* lf ){
        this->data = dt;
        this->right = rg;
        this->left = lf;
}


BST::BST(){
    root = NULL;
}

int BST::countNodes(NodeTree* node){
    if(node == NULL) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

int BST::getNodeCount(){
    return countNodes(root);
}

BST::~BST(){
    deleteTree(root);
}


void BST::SearchAndAdd(NodeTree*& subNode , const int& item){
        if(subNode == NULL) subNode = new NodeTree(item);
        else if( item <= subNode->data ) // eşit değeri sola ekle
            SearchAndAdd(subNode->left , item);
        else if(item > subNode->data)
            SearchAndAdd(subNode->right , item);
        else return;
}



int BST::Height(NodeTree* hNode ){
    if(hNode == NULL) return -1;
    
    int rightH = Height(hNode->right);
    int leftH = Height(hNode->left);
    
    if(rightH > leftH)
        return 1 + rightH;
    else
        return 1 + leftH;
}



void BST::postorderCollect(NodeTree* node, int* arr, int& index){
        if(node == NULL) return;

        postorderCollect(node->left , arr, index);//sol
        postorderCollect(node->right , arr , index);//sağ
        arr[index] = node->data ;//kok
        index++;
}



void BST::deleteTree(NodeTree*& delNode){
        if(delNode == NULL) return;

        deleteTree(delNode->left );//sol
        deleteTree(delNode->right);//sağ
        delete delNode;
}


void BST::add(const int item){
    SearchAndAdd(root , item);   
}


int BST::getHeight(){
    return Height(root);
}



int BST::getRoot(){
    if(root == NULL) return -1;
    return root->data;
}


int* BST::postorderGetAndDelete(int* arr , int& size){
    int index = 0;
    postorderCollect(root, arr, index);
    size = index;
    deleteTree(root);
    root = NULL;
    return arr;
}