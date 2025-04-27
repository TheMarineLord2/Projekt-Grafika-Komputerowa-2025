// metody do algorytmu kwantyzacji (MedianCut)
#include "GK2025-MedianCut.h"
#include "GK2025-Zmienne.h"
#include "GK2025-Funkcje.h"
#include "GK2025-Paleta.h"

using namespace std;



void paletaMedianCutBW(){
    ileKubelkow = 0;
    ileKolorow = 0;
    czyscPalete();
    SDL_Color kolor;
    int szary = 0;
    int numer = 0;
    int indeks = 0;

    for(int y=0; y<wysokosc/2; y++){
        for(int x=0; x<szerokosc/2; x++){
            kolor = getPixel(x,y);
            szary = 0.299*kolor.r + 0.587*kolor.g + 0.114*kolor.b;
            obrazekS[numer] = szary;
            setPixel(x+szerokosc/2, y, szary, szary, szary);
            numer++;
        }
    }
    MedianCutBW(0, numer-1, 3);
    SDL_UpdateWindowSurface(window);

    numer = 0;

    for(int y=0; y<wysokosc/2; y++){
        for(int x=0; x<szerokosc/2; x++){
            szary = obrazekS[numer];
            setPixel(x+szerokosc/2,y+wysokosc/2,szary,szary,szary);
            numer++;
        }
    }
    SDL_UpdateWindowSurface(window);

}

void MedianCutBW(int start, int koniec, int iteracja){

    if(iteracja > 0){

    for(int i=0; i<iteracja; i++) cout << " ";
    cout << "start: " << start<<", koniec: "<<koniec<<", iteracja:"<<iteracja<<endl;
    if(iteracja>0){
        for(int i=0; i<iteracja; i++) cout<<" ";
        cout<<"Dzielimy kubelek na poziomie "<<iteracja<<endl;

        int srodek = (start+koniec+1)/2;

        MedianCutBW(start, srodek-1, iteracja-1);
        MedianCutBW(srodek, koniec, iteracja-1);
    }
    }else{
        int sumaBW = 0;
        for(int p=start; p<=koniec; p++){
            sumaBW += obrazekS[p];
        }
        Uint8 noweBW = sumaBW / (koniec+1-start);
        SDL_Color nowyKolor = {noweBW, noweBW, noweBW};
        paleta8s[ileKubelkow] = nowyKolor;

        cout << "Kubelek "<<ileKubelkow;
        cout<<"(s:"<<start<<", k:"<<koniec<<", e:"<<(koniec+1-start)<<")";
        cout<<endl;
        cout<<"Kolor "<<ileKubelkow<<": ("<<(int)nowyKolor.r<<",";
        cout<<(int)nowyKolor.g<<","<<(int)nowyKolor.b<<")"<<endl;
        ileKubelkow++;

    }

}

void sortujKubelekBW(int start, int koniec){
    int minimum;
    for(int p=start; p<= koniec; p++){
        minimum = p;
        for(int i=p; i<=koniec; i++){
            if(obrazekS[i] < obrazekS[minimum])
                minimum = i;
        }
        swap(obrazekS[p], obrazekS[minimum]);
    }
}
