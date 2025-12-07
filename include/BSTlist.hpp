#ifndef BST_HPP
#define BST_HPP
#include <cstddef>  // NULL için

struct NodeTree{
    int data;
    NodeTree* right;
    NodeTree* left;

    NodeTree(const int& dt = 0 , NodeTree* rg = NULL , NodeTree* lf = NULL);
};

class BST{
private:
    NodeTree* root;
    void SearchAndAdd(NodeTree*& subNode, const int& item);

    int Height(NodeTree* hNode);  //agacin yuksekligini donuyor

    //agaci silmek icin gereken fonklar
    void postorderCollect(NodeTree* node, int* arr, int& index); 
    void deleteTree(NodeTree*& node);

    //agacin node sayisini hesapiyor ve diziyi buna göre belirliyor.
    int countNodes(NodeTree* node); 
public:
    BST();
    ~BST();
    void add(const int item);
    int getHeight();
    int getNodeCount();

    // postorder bi sekile agaci alip diziye dolduruyor ve agaci siliyor
    int* postorderGetAndDelete(int* arr, int& size);
    int getRoot();
};
#endif