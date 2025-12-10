/**
* @file queueControl.hpp
* @description bu sayfa altıgenleri yonetiyor.
* @course 1A grubu ( mehmet fatih adak)
* @assignment 2. Ödev
* @date 07.12.2025
* @author Adem batur , adem.batur@ogr.sakarya.edu.tr
*/
#ifndef QUEUECONTROL_HPP
#define QUEUECONTROL_HPP

#include "queue.hpp"
#include <fstream>
#include <string>

struct HexagonNode {
    Queue veri;  // kuyruk tutuyor veri olarak (max 6 agac)
    HexagonNode* next; // siradaki altigen
    HexagonNode();
};

class queueControl {
private:
    HexagonNode* head;
    HexagonNode** hexArray; // altigenlere direkt erismek icin 
    int** grid;  //ekrana basilacak sayilari tutar
    int rowCount;
    int totalHexagons;

    void updateSingleHexagon(int index);  // Tek altıgenin degerini hesapla, burda hangi altigen oldugunu index ile veriyoruz o orda cikmak uzere olan/oncelikli ile hesapliyor

public:
    queueControl(int hexagonCount); //grid dizisini ve altigenlere hizli erismemizi saglayan altigen dizisini olusturur olusturur
    ~queueControl(); // dizileri ve tum altigenleri siler

    void initializeFromFile(const std::string& dosyaAdi);
    void runTours(int tourCount);
    void updateGrid(); //Tüm altıgenlerin grid değerlerini hesaplar.
    void printGrid();
    void printGridWithTour(int tourNum);
};

#endif