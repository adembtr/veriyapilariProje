/**
* @file queueControl.cpp
* @description bu sayfa queueControl classinin fonklarini dolduruyor
* @course 1A grubu ( mehmet fatih adak)
* @assignment 2. Ödev
* @date 07.12.2025
* @author Adem batur , adem.batur@ogr.sakarya.edu.tr
*/
#include "queueControl.hpp"
#include <cmath>
#include <iostream>
using namespace std;

HexagonNode::HexagonNode() {
    this->next = NULL;
}

queueControl::queueControl(int hexagonCount) {
    this->totalHexagons = hexagonCount;
    this->rowCount = (int)ceil(hexagonCount / 6.0);

    // Grid olustur
    this->grid = new int*[rowCount];
    for (int i = 0; i < rowCount; i++) {
        grid[i] = new int[6];
        for (int j = 0; j < 6; j++) {
            grid[i][j] = 0;
        }
    }

    // Hizli erisim dizisi
    this->hexArray = new HexagonNode*[hexagonCount];

    // Altigen listesi olustur
    this->head = new HexagonNode();
    hexArray[0] = head;

    HexagonNode* ptr = head;
    for (int i = 1; i < hexagonCount; i++) {
        ptr->next = new HexagonNode();
        ptr = ptr->next;
        hexArray[i] = ptr;
    }
    ptr->next = head;  // Dairesel

    printGrid();
}

queueControl::~queueControl() {
    for (int i = 0; i < rowCount; i++) {
        delete[] grid[i];
    }
    delete[] grid;
    delete[] hexArray;

    if (head != NULL) {
        HexagonNode* current = head->next;
        while (current != head) {
            HexagonNode* temp = current;
            current = current->next;
            delete temp;
        }
        delete head;
    }
}

void queueControl::printGrid() {
    system("cls");

    int count = 0;
    for (int i = 0; i < rowCount; i++) {
        // Bu satirdaki altigen sayisi
        int colsInRow = 6;
        if ((i + 1) * 6 > totalHexagons) {
            colsInRow = totalHexagons - i * 6;
        }
        
        if (i % 2 == 0) {
            // Cift satirlar (0, 2, 4...) normal yazdir
            for (int j = 0; j < colsInRow; j++) {
                cout << grid[i][j] << "\t";
            }
        } else {
            // Tek satirlar (1, 3, 5...) tersten yazdir
            for (int j = colsInRow - 1; j >= 0; j--) {
                cout << grid[i][j] << "\t";
            }
        }
        cout << endl;
        count += colsInRow;
    }
}

void queueControl::printGridWithTour(int tourNum) {
    // imleci sol ust koseye tasir ve ustune yazar . hiz icin
     system("cls");
    
    cout << "TUR " << tourNum << endl;

    for (int i = 0; i < rowCount; i++) {
        int colsInRow = 6;
        if ((i + 1) * 6 > totalHexagons) {
            colsInRow = totalHexagons - i * 6;
        }
        
        if (i % 2 == 0) {
            for (int j = 0; j < colsInRow; j++) {
                cout << grid[i][j] << "\t";
            }
        } else {
            for (int j = colsInRow - 1; j >= 0; j--) {
                cout << grid[i][j] << "\t";
            }
        }
        cout << "     " << endl;
    }
    cout.flush();
}

void queueControl::initializeFromFile(const std::string& dosyaAdi) {
    std::ifstream file(dosyaAdi);
    if (!file.is_open()) {
        std::cerr << "HATA: dosya acilamadi!\n";
        return;
    }

    std::string line;
    int satirSayaci = 0;
    int altigenIndex = 0;

    while (std::getline(file, line) && altigenIndex < totalHexagons) {
        BST* agac = new BST();

        int sayi = 0;
        bool sayiVar = false;

        for (int i = 0; i <= (int)line.length(); i++) {
            char c = (i < (int)line.length()) ? line[i] : ' ';

            if (c >= '0' && c <= '9') {
                sayi = sayi * 10 + (c - '0');
                sayiVar = true;
            } else if (sayiVar) {
                agac->add(sayi);
                sayi = 0;
                sayiVar = false;
            }
        }

        hexArray[altigenIndex]->veri.enqueue(agac);
        satirSayaci++;

        if (satirSayaci == 6) {
            satirSayaci = 0;
            altigenIndex++;
        }
    }

    file.close();
    updateGrid();
    printGrid();
}

void queueControl::updateSingleHexagon(int index) {
    int row = index / 6;
    int col = index % 6;

    int frontRoot = hexArray[index]->veri.getFrontRoot();
    int priorityRoot = hexArray[index]->veri.getPriorityRoot();

    //eger ki oncelikli yoksa veya frontroot yoksa sifir basar ki bu olmayacak bir durum ama kontrol olmasi gerek
    if (priorityRoot <= 0 || frontRoot < 0) {
        grid[row][col] = 0;
    } else {
        grid[row][col] = frontRoot / priorityRoot;
    }
}

void queueControl::updateGrid() {
    for (int i = 0; i < totalHexagons; i++) {
        updateSingleHexagon(i);
    }
}


void queueControl::runTours(int tourCount) {
    // cls yerine ustune yazmayi tercih ettim. daha hizli 
    cout << "\033[2J\033[H"; 
    
    for (int tur = 1; tur <= tourCount; tur++) {
        bool isPriority = (tur % 2 == 0); // oncelikli mi cikacak

        for (int h = 0; h < totalHexagons; h++) {
            BST* cikanAgac;
            if (isPriority) {
                cikanAgac = hexArray[h]->veri.dequeuePriority();
            } else {
                cikanAgac = hexArray[h]->veri.dequeue();
            }

            if (cikanAgac == NULL) continue;

            int nodeCount = cikanAgac->getNodeCount();
            if (nodeCount == 0) {
                delete cikanAgac;
                continue;
            }

            int* arr = new int[nodeCount];
            int size = 0;
            cikanAgac->postorderGetAndDelete(arr, size);
            delete cikanAgac;   // alinan agac sonra siliniyor

            int hedefIndex = (h + 1) % totalHexagons;
            Queue& hedefKuyruk = hexArray[hedefIndex]->veri;



//! burda cok onemli bir islem var. eger kuyruk 4 elemanli ise 4 e kadar ekliyor sonra 5 i sonra 6 yi olusturup onlarada ekliyor sonra tekrar basa donuyor
            QueueNode* currentNode = hedefKuyruk.getHead();
            int mevcutUzunluk = hedefKuyruk.getLength();
            int treeIndex = 0;
            
            for (int i = 0; i < size; i++) {
                if (treeIndex < mevcutUzunluk) {
                    currentNode->tree->add(arr[i]);
                    currentNode = currentNode->next;
                    treeIndex++;
                }
                else if (mevcutUzunluk < 6) {
                    BST* yeniAgac = new BST();
                    yeniAgac->add(arr[i]);
                    hedefKuyruk.enqueue(yeniAgac);
                    mevcutUzunluk++;
                    treeIndex++;
                }
                else {
                    treeIndex = 0;
                    currentNode = hedefKuyruk.getHead();
                    currentNode->tree->add(arr[i]);
                    currentNode = currentNode->next;
                    treeIndex++;
                }
            }

            delete[] arr;
        }

        updateGrid();
        printGridWithTour(tur);
    }

    cout << endl << "Turlar tamamlandi." << endl;
}