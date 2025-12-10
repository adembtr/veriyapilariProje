/**
* @file BSTlist.cpp
* @description bu sayfa bst list sinifinin fonk larını dolduruyor
* @course 1A grubu ( mehmet fatih adak)
* @assignment 2. Ödev
* @date 07.12.2025
* @author Adem batur , adem.batur@ogr.sakarya.edu.tr
*/
#include "BSTlist.hpp"

NodeTree::NodeTree(const int& dt, NodeTree* rg, NodeTree* lf) {
    data = dt;
    right = rg;
    left = lf;
}

BST::BST() {
    root = NULL;
    nodeCount = 0; // agaci silip ekleyecegimiz dizinin boyutu ne olucak onu tutuyor
}

BST::~BST() {
    deleteTree(root);
}

//eleman eklenecek yeri bul ve ekle
void BST::SearchAndAdd(NodeTree*& subNode, const int& item) {
    if (subNode == NULL)
        subNode = new NodeTree(item);
    else if (item <= subNode->data)
        SearchAndAdd(subNode->left, item);
    else
        SearchAndAdd(subNode->right, item);
}

int BST::Height(NodeTree* hNode) {
    if (hNode == NULL) return -1;
    int rightH = Height(hNode->right);
    int leftH = Height(hNode->left);
    return 1 + (rightH > leftH ? rightH : leftH);
}

//postorder bi sekilde gezip diziye topla
void BST::postorderCollect(NodeTree* node, int* arr, int& index) {
    if (node == NULL) return;
    postorderCollect(node->left, arr, index);
    postorderCollect(node->right, arr, index);
    arr[index++] = node->data; // burda indexi artiriyor ama bu artan deger bu satirdan sonra calisacak
}


//agaci sil
void BST::deleteTree(NodeTree*& node) {
    if (node == NULL) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
    node = NULL;
}

void BST::add(const int item) {
    SearchAndAdd(root, item);
    nodeCount++;
}

int BST::getHeight() {
    return Height(root);
}

int BST::getNodeCount() {
    return nodeCount;
}

int BST::getRoot() {
    if (root == NULL) return -1;
    return root->data;
}

//postorder toplayip heapteki diziye at ve postorder sil 
int* BST::postorderGetAndDelete(int* arr, int& size) {
    size = nodeCount; // Size değişkenini güncelle
    int index = 0; //index 0 dan basliyor
    postorderCollect(root, arr, index);
    deleteTree(root);
    root = NULL;
    nodeCount = 0;
    return arr;
}