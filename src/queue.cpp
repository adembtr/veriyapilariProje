/**
* @file queue.cpp
* @description bu sayfa queue classinin fonklarını dolduruyor
* @course 1A grubu ( mehmet fatih adak)
* @assignment 2. Ödev
* @date 07.12.2025
* @author Adem batur , adem.batur@ogr.sakarya.edu.tr
*/
#include "queue.hpp"

QueueNode::QueueNode(BST* t) {
    tree = t;
    next = NULL;
}

//kuyruklari ilk basta bos olusturuyoruz
Queue::Queue() {
    head = NULL;
    tail = NULL;
    length = 0;
}




Queue::~Queue() {
    if(head == NULL) return;

    QueueNode* current = head;

    while(current != tail){
        QueueNode* del = current;
        current = current->next;
        delete del->tree;
        delete del;
    }
    delete current->tree;
    delete current;
    head = tail = NULL;
    length = 0;
}

void Queue::enqueue(BST* tree) {
    // olmaz ama olursa memory leak olmasin diye kontrol var
    if (length >= 6) {
        delete tree;
        return;
    }

    QueueNode* newNode = new QueueNode(tree);
    if (head == NULL) {
        head = newNode;
        tail = newNode;
        newNode->next = head; // kendine bagla (dairesel)
    } else {
        tail->next = newNode;
        newNode->next = head; // dairesel bagla
        tail = newNode;         //yeni eklenen son yap
    }
    length++;
}

BST* Queue::dequeue() {
    if (length == 0) return NULL;

    QueueNode* temp = head;
    BST* cikan = temp->tree;

    if (length == 1) {
        head = NULL;
        tail = NULL;
    } else {
        head = head->next;
        tail->next = head; // dairesel baglantiyi koru
    }
    
    delete temp;
    length--;
    return cikan;      //bu gonderilen agac queueControl da silinyor
}

BST* Queue::dequeuePriority() {
    if (length == 0) return NULL;

    // En yuksek height'li dugumu ve oncesini bul ( simdilik head sayiyoruz)
    QueueNode* maxNode = head;
    QueueNode* maxPrev = tail;
    int maxHeight = head->tree->getHeight();


    //  prev ve current kullanarak adim adim gezip en yuksek oncelikli olani buluyoruz
    QueueNode* prev = head;
    QueueNode* current = head->next;
    while (current != head) {
        int h = current->tree->getHeight();
        if (h > maxHeight) {
            maxHeight = h;
            maxNode = current;
            maxPrev = prev;
        }
        prev = current;
        current = current->next;
    }


    // burda oncelikli cikanin agacini alip onu siliyoruz
    BST* cikan = maxNode->tree;
    if (length == 1) { // eger 1 agac tek varsa ve onu siliyorsak bu calisir 
        head = tail = NULL;
    } else {
        maxPrev->next = maxNode->next;
        if (maxNode == head)  head = maxNode->next;
        if (maxNode == tail)  tail = maxPrev;
    }
    
    delete maxNode;
    length--;
    return cikan;
}

int Queue::getFrontRoot() {
    if (length == 0) return -1;
    return head->tree->getRoot();
}

int Queue::getPriorityRoot() {
    if (length == 0) return -1;
    
    QueueNode* maxNode = head;
    int maxHeight = head->tree->getHeight();
    
    QueueNode* current = head->next;
    while (current != head) {
        int h = current->tree->getHeight();
        if (h > maxHeight) {
            maxHeight = h;
            maxNode = current;
        }
        current = current->next;
    }
    
    return maxNode->tree->getRoot();
}

int Queue::getLength() {
    return length;
}

QueueNode* Queue::getHead() {
       return head;
}

bool Queue::isEmpty() {
    return (length == 0);
}