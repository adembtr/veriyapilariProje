#include "queueControl.hpp"
#include <cmath>  // ceil için
#include <iostream>

HexagonNode::HexagonNode(){
    this->veri = Queue();
    this->next = NULL;
}

queueControl::queueControl(int hexagonCount){
    this->totalHexagons = hexagonCount;
    this->rowCount = ceil(hexagonCount / 6.0); // dizinin satır sayısı , sütün abit 6.

    this-> grid = new int*[rowCount];
    for(int i = 0; i < rowCount ; i++){
        grid[i] = new int[6];
        
        for(int j = 0; j< 6 ; j++){
            grid[i][j] = 0;
        }
    }

    // altıgen sayısı kadar altıgen oluşturuyoruz
    this->head = new HexagonNode();
    HexagonNode* ptr = head;
    for(int i=1 ; i< hexagonCount ; i++){
        ptr->next = new HexagonNode();
        ptr = ptr->next;
    }
    ptr->next = head; // son node heada döndü. dairesel liste.

    printGrid();
}


void queueControl::printGrid(){
    system("cls"); 
    
    int count = 0;
    for(int i = 0; i < rowCount; i++){
        for(int j = 0; j < 6 && count < totalHexagons; j++){
            cout << grid[i][j] << "\t";
            count++;
        }
        cout << endl;
    }
}

void queueControl::initializeFromFile(const std::string& dosyaAdi){
    std::ifstream file(dosyaAdi); 

    if (!file.is_open()) {
        std::cerr << "HATA: dosya acilamadi!\n";
        return;
    }

    std::string line;
    int satirSayaci = 0;
    HexagonNode* aktifAltigen = head;

    while(std::getline(file, line)){
        // yeni bst olustur
        BST* agac = new BST();

        // Satırdaki sayıları ayir ve ağaca ekle
        int sayi = 0;
        bool sayiVar = false;
        
        // burda manuel olarak satırları bölüp ağaça
        for(int i = 0; i <= line.length(); i++) {
            char c;
            if(i < line.length()) {
                c = line[i];
            } else {
                c = ' ';  // satır sonu
            }
            
            if(c >= '0' && c <= '9') {
                sayi = sayi * 10 + (c - '0');
                sayiVar = true;
            } 
            else if(sayiVar) {
                agac->add(sayi);
                sayi = 0;
                sayiVar = false;
            }
        }
        // 3. BST'yi aktif altıgenin kuyruğuna ekle
        aktifAltigen->veri.enqueue(agac);
        
        // 4. Satır sayacını artır
        satirSayaci++;
        
        // 5. 6 satır olduysa sonraki altıgene geç
        if(satirSayaci == 6) {
            satirSayaci = 0;
            aktifAltigen = aktifAltigen->next;
        }
    }
    file.close();
    updateGrid();      // değerleri hesapla
    printGrid();   // ekrana bas
}



queueControl::~queueControl(){
    // 1. Grid'i sil
    for(int i = 0; i < rowCount; i++){
        delete[] grid[i];
    }
    delete[] grid;
    
    // 2. Altıgen listesini sil (dairesel liste)
    if(head != NULL){
        HexagonNode* current = head->next;
        while(current != head){
            HexagonNode* temp = current;
            current = current->next;
            delete temp;
        }
        delete head;
    }
}



void queueControl::updateGrid(){
    HexagonNode* ptr = head;
    int count = 0;
    
    for(int i = 0; i < rowCount; i++){
        for(int j = 0; j < 6 && count < totalHexagons; j++){
            
            int normalRoot = ptr->veri.getFrontRoot();
            int priorityRoot = ptr->veri.getPriorityRoot();
            
            if(priorityRoot <= 0 || normalRoot < 0){
                grid[i][j] = 0;
            } else {
                grid[i][j] = normalRoot / priorityRoot;
            }
            
            ptr = ptr->next;
            count++;
        }
    }
}



void queueControl::printGridWithTour(int tourNum){
    system("cls"); 
    
    cout <<"TUR "<<tourNum<<endl;
    
    int count = 0;
    for(int i = 0; i < rowCount; i++){
        for(int j = 0; j < 6 && count < totalHexagons; j++){
            cout << grid[i][j] << "\t";
            count++;
        }
        cout << endl;
    }
}

void queueControl::runTours(int tourCount){
    int normalSayac = 0;
    
    for(int tur = 1; tur <= tourCount; tur++){
        bool isPriority = (tur % 2 == 0);
        HexagonNode* current = head;
        
        for(int h = 0; h < totalHexagons; h++){
            BST* agac;
            if(isPriority){
                agac = current->veri.getPriorityTree();
            } else {
                agac = current->veri.getTreeAtPosition(normalSayac);
            }
            
            if(agac != NULL && agac->getRoot() != -1){
                // Dinamik dizi - node sayısı kadar
                int nodeCount = agac->getNodeCount();
                int* arr = new int[nodeCount];  // DİNAMİK
                int size = 0;
                
                agac->postorderGetAndDelete(arr, size);
                
                HexagonNode* hedef = current->next;
                int hedefUzunluk = hedef->veri.getLength();
                
                if(hedefUzunluk > 0 && size > 0){
                    int treeIndex = 0;
                    for(int i = 0; i < size; i++){
                        BST* hedefAgac = hedef->veri.getTreeAt(treeIndex);
                        if(hedefAgac != NULL){
                            hedefAgac->add(arr[i]);
                        }
                        treeIndex = (treeIndex + 1) % hedefUzunluk;
                    }
                }
                
                delete[] arr;  // TEMİZLE
            }
            current = current->next;
        }
        
        if(!isPriority){
            normalSayac = (normalSayac + 1) % 6;
        }
        
        updateGrid();
        printGridWithTour(tur);

    }
    
    cout << endl << "Turlar tamamlandi." << endl;
}