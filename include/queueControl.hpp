#ifndef QUEUECONTROL_HPP
#define QUEUECONTROL_HPP

#include "queue.hpp"
#include <fstream>
#include <iostream>
#include <string>


struct HexagonNode {
    Queue veri;        // Bu altigenin kuyrugu (6 BST)
    HexagonNode* next; // Sonraki altigen

    HexagonNode();
};
                 

                                                            


class queueControl{
private:
    HexagonNode* head;    // Altigen listesinin başi
    int** grid;           // Ekran grid'i
    int rowCount;         // Grid satir sayisi, sütün 6 zaten.
    int totalHexagons;    // Toplam altigen sayisi
public:
    queueControl(int hexagonCount); // bu diziyi ve listeyi boş olarak oluşturur. altigen listesini tek yönlü ve dairesel olarak oluşturur.

    void initializeFromFile(const std::string& dosyaAdi); //dosyadan okuyup agaclari doldurup ekrana basar

    void runTours(int tourCount);    // 3. Fonksiyon "tur yapar"

    void updateGrid();  // Grid degerlerini hesapla
    void printGrid();
    void printGridWithTour(int tourNum);  // turlar ile gridi doldurur
    ~queueControl();
};

#endif