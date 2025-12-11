/**
* @file queue.hpp
* @description bu sayfa kuyruk veri yapısı oluşturuyor her kuyruk elemani içinde dizi tutan bir 6 li ağaç tutuyor
* @course 1A grubu ( mehmet fatih adak)
* @assignment 2. Ödev
* @date 07.12.2025
* @author Adem batur , adem.batur@ogr.sakarya.edu.tr
*/
#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "BSTlist.hpp"

// Kuyruk dugumu - dairesel linked list icin
struct QueueNode {
    BST* tree;
    QueueNode* next;
    QueueNode(BST* t = NULL);
};

class Queue {
private:
    QueueNode* head;    // Dairesel linked list - ilk eleman
    QueueNode* tail;    // Son eleman (head'den onceki)
    int length;

public:
    Queue();
    ~Queue();

    void enqueue(BST* tree); // ekle
    BST* dequeue();           // ilk elemani cikar
    BST* dequeuePriority();   // En yüksek height'li cikar

    int getFrontRoot();
    int getPriorityRoot(); // oncelikli getir
    int getLength();
    bool isEmpty();
    QueueNode* getHead();  // headi getir tur icin
};

#endif