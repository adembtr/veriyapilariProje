/**
* @file main.cpp
* @description bu sayfa ekrana yazdırma islerini kontrol ediyor
* @course 1A grubu ( mehmet fatih adak)
* @assignment 2. Ödev
* @date 07.12.2025
* @author Adem batur , adem.batur@ogr.sakarya.edu.tr
*/
#include "queueControl.hpp"
#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    ifstream file("data.txt");
    int totalLines = 0;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            totalLines++;
        }
        file.close();
    } else {
        cerr << "HATA: 'data.txt' dosyasi acilamadi!\n";
        return 1;
    }

    int altigenSayisi = (int)ceil(totalLines / 6.0);

    queueControl* listePtr = new queueControl(altigenSayisi);

    cout << "Toplam altigen sayisi: " << altigenSayisi << endl;
    cout << "Devam etmek icin ENTER'a basin...";
    cin.get();

    listePtr->initializeFromFile("data.txt");

    int turSayisi;
    cout << endl << "Kac tur calistirilacak? ";
    cin >> turSayisi;
    cin.ignore();

    cout << "Turlari baslatmak icin ENTER'a basin...";
    cin.get();

    listePtr->runTours(turSayisi);

    cout << "Cikmak icin ENTER'a basin...";
    cin.get();

    delete listePtr;
    return 0;
}