/**
* @file queue.cpp
* @description bu sayfa queue classinin fonklarını dolduruyor
* @course 1A grubu ( mehmet fatih adak)
* @assignment 2. Ödev
* @date 07.12.2025
* @author Adem batur , adem.batur@ogr.sakarya.edu.tr
*/
#include "queue.hpp"

//kuyruklari ilk basta bos olusturuyoruz
Queue::Queue() {
    for (int i = 0; i < 6; i++) {
        trees[i] = NULL;
    }
    length = 0;
}

Queue::~Queue() {
    for (int i = 0; i < 6; i++) {
        if (trees[i] != NULL) {
            delete trees[i];
        }
    }
}

void Queue::enqueue(BST* tree) {
    // olmaz ama olursa memory leak olmasin diye kontrol var
    if (length >= 6) {
        delete tree;
        return;
    }
    trees[length] = tree;
    length++;
}

BST* Queue::dequeue() {
    if (length == 0) return NULL;

    BST* cikan = trees[0];

    // burda kuyrugun ilk elmanini cikartiyoruz ve kuyrugu kaydiriyoruz ( dizinin icinde)
    for (int i = 0; i < length - 1; i++) {
        trees[i] = trees[i + 1];
    }
    trees[length - 1] = NULL;
    length--;

    return cikan;
}

BST* Queue::dequeuePriority() {
    if (length == 0) return NULL;

    // En yüksek height'lı bul
    int maxIdx = 0;
    int maxHeight = trees[0]->getHeight();

    for (int i = 1; i < length; i++) {
        int h = trees[i]->getHeight();
        if (h > maxHeight) {
            maxHeight = h;
            maxIdx = i;
        }
    }

    BST* cikan = trees[maxIdx];

    // burda oncelikliyi cikarttiktan  sonra kaydirma yapiyoruz
    for (int i = maxIdx; i < length - 1; i++) {
        trees[i] = trees[i + 1];
    }
    trees[length - 1] = NULL;
    length--;

    return cikan;
}

int Queue::getFrontRoot() {
    if (length == 0) return -1;
    return trees[0]->getRoot();
}

int Queue::getPriorityRoot() {
    if (length == 0) return -1;

    int maxIdx = 0;
    int maxHeight = trees[0]->getHeight();

    for (int i = 1; i < length; i++) {
        int h = trees[i]->getHeight();
        if (h > maxHeight) {
            maxHeight = h;
            maxIdx = i;
        }
    }

    return trees[maxIdx]->getRoot();
}

int Queue::getLength() {
    return length;
}

// istedigim indeksteki agaci getir
BST* Queue::getTreeAt(int index) {
    if (index < 0 || index >= length) return NULL;
    return trees[index];
}

bool Queue::isEmpty() {
    return (length == 0);
}