#include "queueControl.hpp"
#include <fstream>
#include <iostream>
#include <string> 
#include <cmath>
using namespace std;

int main(){

    //? altigen sayisini buluyoruz
    std::ifstream file("data.txt"); 
    int totalLines = 0;

    if (file.is_open()) {
        std::string line;
        
        while (std::getline(file, line)) {
            totalLines++;
        }
        file.close();
    } else {
        std::cerr << "HATA: 'data.txt' dosyasi acilamadi!\n";
        return 1;
    }

    int altigenSayisi = ceil(totalLines / 6.0);

  
    

    

    // 2. Boş grid'i oluştur ve ekrana 0'lari bas
    queueControl* listePtr = new queueControl(altigenSayisi);
    // 1. Toplam altigen sayisini göster
    cout << "Toplam altigen sayisi: " << altigenSayisi << endl;

    cout << "Altigenleri doldurmak icin bir tusa basip entera basin...";
    cin.ignore();
    cin.get();
    


    // 3. Dosyadan oku, ağaçlari oluştur, grid'i güncelle fonksiyonu
    listePtr->initializeFromFile("data.txt");


    // 4. Kullanicidan tur sayisini iste
    int turSayisi;
    cout << endl << "Kac tur calistirilacak? ";
    cin >> turSayisi;


    // 5. Turlari çaliştir
    listePtr->runTours(turSayisi);
    
    // 6. Çikiş için bekle
    cin.get();
    
    delete listePtr;
    return 0;
}