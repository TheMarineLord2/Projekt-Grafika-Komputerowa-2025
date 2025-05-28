#include <SDL2/SDL_stdinc.h>
#include <bitset>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

#include "GK2025-Paleta.h"
#include "GK2025-Zmienne.h"
#include "GK2025-Funkcje.h"

void normalizePixels(Uint8 *data,  Uint8 *pixels, int depth) {
    for(int byte = 0; byte < depth; byte++) {
        for(int p = 0; p < 8; p++) {
            uint8_t bit = (pixels[p] >> byte) & 1;
            data[byte] |= (bit << p);        
        }
    }
}

void readBuffer(Uint8 *codeData, Uint8 *decodedArray) {
    // Read the 6 depth layers back into each pixel
    for (int bit = 0; bit < 6; bit++) {
        for (int i = 0; i < 8; i++) {
            uint8_t bitVal = (codeData[bit] >> i) & 1;
            decodedArray[i] |= (bitVal << bit);
        }
    }
}

void writeFile() {
    Uint8 colors[8] = {1, 1, 1, 1, 7, 1, 1, 1};

    Uint8 data[6];
    memset(data, 0, 6);

    normalizePixels(data, colors, 6);

    for(int i = 0; i < 6; i ++) {
        std::bitset<8> x(data[i]);
        std::cout << x << "\n";
    }
    std::cout << "\n";
    for(int i = 0; i < 8; i ++) {
        std::bitset<8> x(colors[i]);
        std::cout << x << "\n";
    }
    std::cout << "\n";

    Uint8 decoded[8];
    memset(decoded, 0, 8);

    readBuffer(data, decoded);

    for(int i = 0; i < 8; i ++) {
        std::bitset<8> x(decoded[i]);
        std::cout << x << "\n";
    }
}

void zapiszPlik() {
    SDL_Color kolor;
    Uint16 szerokoscObrazka = szerokosc/2;
    Uint16 wysokoscObrazka = wysokosc/2;
    Uint8 ileBitow = 24;
    char identyfikator[] = "DG";

    std::cout<<"Zapisujemy plik 'obrazRGB.bin' uzywajac metody write()"<<std::endl;
    
    std::ofstream wyjscie("obrazRGB.bin", std::ios::binary);

    wyjscie.write(reinterpret_cast<char*>(&identyfikator), sizeof(char)*2);
    wyjscie.write(reinterpret_cast<char*>(&szerokoscObrazka), sizeof(Uint16));
    wyjscie.write(reinterpret_cast<char*>(&wysokoscObrazka), sizeof(Uint16));
    wyjscie.write(reinterpret_cast<char*>(&ileBitow), sizeof(Uint8));

    wyjscie.close();
}

void odczytajPlik(){
    SDL_Color kolor;
    Uint16 szerokoscObrazka = 0;
    Uint16 wysokoscObrazka = 0;
    Uint8 ileBitow = 0;
    char identyfikator[] = "  ";

    std::cout<<"Odczytujemy plik 'obrazRGB.bin' uzywajac metody read()"<<std::endl;
    std::ifstream wejscie("obrazRGB.bin", std::ios::binary);

    wejscie.read((char*)&identyfikator, sizeof(char)*2);
    wejscie.read((char*)&szerokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&wysokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&ileBitow, sizeof(Uint8));

    std::cout<<"id: "<<identyfikator<<std::endl;
    std::cout<<"szerokosc: "<<szerokoscObrazka<<std::endl;
    std::cout<<"wysokosc: "<<wysokoscObrazka<<std::endl;
    std::cout<<"ile bitow: "<<((int)ileBitow)<<std::endl;

    SDL_UpdateWindowSurface(window);
}

void zapiszPlik6() {
    SDL_Color kolor;
    Uint8 kolor8bit;
    Uint8 pixels[8];     // Bufor na 8 pikseli (8 x 8-bit)
    Uint8 zakodowane[6]; // Bufor na zakodowane dane (6 bajtów)
    Uint16 szerokoscObrazka = szerokosc / 2;
    Uint16 wysokoscObrazka = wysokosc / 2;
    Uint8 ileBitow = 6;
    char identyfikator[] = "DG";

    std::cout << "Zapisujemy plik 'obraz8.bin' uzywajac metody write() i kodowania 6-bitowego" << std::endl;
    std::ofstream wyjscie("obraz8.bin", std::ios::binary);
    wyjscie.write((char*)&identyfikator, sizeof(char) * 2);
    wyjscie.write((char*)&szerokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&ileBitow, sizeof(Uint8));

    // Przechodzimy przez obraz blokami 8-wierszowymi
    for (int blockStartY = 0; blockStartY < wysokoscObrazka; blockStartY += 8) {
        for (int x = 0; x < szerokoscObrazka; x++) {
            // Wypełniamy bufor 8 pikseli z kolumny
            for (int yOffset = 0; yOffset < 8; yOffset++) {
                int y = blockStartY + yOffset;
                if (y >= wysokoscObrazka) {
                    pixels[yOffset] = 0; // Jeśli wychodzimy poza obraz, wypełniamy zerami
                } else {
                    kolor = getPixel(x, y);
                    pixels[yOffset] = z24Kdo6K(kolor);
                }
            }

            // Wyzeruj bufor wyjściowy
            for (int i = 0; i < 6; i++) zakodowane[i] = 0;

            // Zakoduj 8 pikseli do 6 bajtów
            normalizePixels(zakodowane, pixels, 6);

            // Zapisz 6 bajtów do pliku
            wyjscie.write((char*)zakodowane, sizeof(Uint8) * 6);
        }
    }

    wyjscie.close();
    SDL_UpdateWindowSurface(window);
}

void odczytajPlik6() {
    SDL_Color kolor;
    Uint8 kolor8bit = 0;
    Uint16 szerokoscObrazka = 0;
    Uint16 wysokoscObrazka = 0;
    Uint8 ileBitow = 0;
    char identyfikator[] = "  ";

    Uint8 zakodowane[6]; // 6 bajtów zakodowanych
    Uint8 pixels[8];     // Odtworzone 8 pikseli

    std::cout << "Odczytujemy plik 'obraz8.bin' uzywajac metody read()" << std::endl;
    std::ifstream wejscie("obraz8.bin", std::ios::binary);

    wejscie.read((char*)&identyfikator, sizeof(char) * 2);
    wejscie.read((char*)&szerokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&wysokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&ileBitow, sizeof(Uint8));

    std::cout << "id: " << identyfikator << std::endl;
    std::cout << "szerokosc: " << szerokoscObrazka << std::endl;
    std::cout << "wysokosc: " << wysokoscObrazka << std::endl;
    std::cout << "ile bitow: " << (int)ileBitow << std::endl;

    for (int blockStartY = 0; blockStartY < wysokoscObrazka; blockStartY += 8) {
        for (int x = 0; x < szerokoscObrazka; x++) {
            // Wczytaj 6 bajtów danych
            wejscie.read((char*)zakodowane, sizeof(Uint8) * 6);

            // Wyzeruj bufor pikseli
            for (int i = 0; i < 8; i++) pixels[i] = 0;

            // Odtwórz 8 pikseli z 6 bajtów
            readBuffer(zakodowane, pixels);

            // Ustaw piksele na ekranie (prawe pół)
            for (int yOffset = 0; yOffset < 8; yOffset++) {
                int y = blockStartY + yOffset;
                if (y >= wysokoscObrazka) break;

                kolor = z6Kdo24K(pixels[yOffset]);
                setPixel(x + (szerokosc / 2), y, kolor.r, kolor.g, kolor.b);
            }
        }
    }

    SDL_UpdateWindowSurface(window);
}
