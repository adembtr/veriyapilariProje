/**
* @file BSTlist.hpp
* @description bu sayfa agac dugumleri ve BST list olusturuyor
* @course 1A grubu ( mehmet fatih adak)
* @assignment 2. Ödev
* @date 07.12.2025
* @author Adem batur , adem.batur@ogr.sakarya.edu.tr
*/
#ifndef BST_HPP
#define BST_HPP
#include <cstddef>

struct NodeTree {
    int data;
    NodeTree* right;
    NodeTree* left;
    NodeTree(const int& dt = 0, NodeTree* rg = NULL, NodeTree* lf = NULL);
};

class BST {
private:
    NodeTree* root;
    int nodeCount;       // Önbelleklenmiş node sayısı
    void SearchAndAdd(NodeTree*& subNode, const int& item); // ekle
    int calculateHeight(NodeTree* hNode);          // height hesapla
    void postorderCollect(NodeTree* node, int* arr, int& index); // postorder topla
    void deleteTree(NodeTree*& node);  // agaci sil
    int Height(NodeTree* hNode) ; 

public:
    BST();
    ~BST();
    void add(const int item); // ekle
    int getHeight();       // height geiir
    int getNodeCount();    // dugumleri hesapla ve getir
    int* postorderGetAndDelete(int* arr, int& size); // postorder gez ve diziye topla ve sil 
    int getRoot();    //koku getir
};

#endif