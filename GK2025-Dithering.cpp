#include "GK2025-Dithering.h"
#include "GK2025-Zmienne.h"
#include "GK2025-Paleta.h"
#include "GK2025-Pliki.h"
#include "GK2025-Funkcje.h"
#include "GK2025-MedianCut.h"
#include <iostream>


void wyzerujTabliceBledowK(){
    for(int i=0; i<szerokosc/2; i++){
        for(int j=0; j<wysokosc/2; j++){
            tablicaBledowK[i][j][0].r = 0;
            tablicaBledowK[i][j][0].g = 0;
            tablicaBledowK[i][j][0].b = 0;
            tablicaBledowK[i][j][1].r = 0;
            tablicaBledowK[i][j][1].g = 0;
            tablicaBledowK[i][j][1].b = 0;
        }
    }
}

void wyzerujTabliceBledowS(){
    for(int i=0; i<szerokosc/2; i++){
        for(int j=0; j<wysokosc/2; j++){
            tablicaBledowS[i][j][0] = 0;
            tablicaBledowS[i][j][1] = 0;
        }
    }
}

void propagujBladK(SDL_Color wartosciBledow[], int x, int y){
    // jeœli punkt nie wychodzi poza tablice:
    if(x+1>=0 && y>=0 && x+1<szerokosc/2 && y<wysokosc/2){  // propaduj 7/16 na prawo
        tablicaBledowK[ x+1 ][  y  ][ 0 ].r += (wartosciBledow[ 0 ].r * 7 / 16 );
        tablicaBledowK[ x+1 ][  y  ][ 0 ].g += (wartosciBledow[ 0 ].g * 7 / 16 );
        tablicaBledowK[ x+1 ][  y  ][ 0 ].b += (wartosciBledow[ 0 ].b * 7 / 16 );
        tablicaBledowK[ x+1 ][  y  ][ 1 ].r += (wartosciBledow[ 1 ].r * 7 / 16 );
        tablicaBledowK[ x+1 ][  y  ][ 1 ].g += (wartosciBledow[ 1 ].g * 7 / 16 );
        tablicaBledowK[ x+1 ][  y  ][ 1 ].b += (wartosciBledow[ 1 ].b * 7 / 16 );
    }
    // i dla wiersza poni¿ej:
    if(y+1>=0 && y+1<wysokosc/2){
        if(x-1>=0 && x-1<szerokosc/2){                      // propaguj 3/16 w lewo dol
            tablicaBledowK[ x-1 ][ y+1 ][ 0 ].r += (wartosciBledow[ 0 ].r * 3 / 16);
            tablicaBledowK[ x-1 ][ y+1 ][ 0 ].g += (wartosciBledow[ 0 ].g * 3 / 16);
            tablicaBledowK[ x-1 ][ y+1 ][ 0 ].b += (wartosciBledow[ 0 ].b * 3 / 16);
            tablicaBledowK[ x-1 ][ y+1 ][ 1 ].r += (wartosciBledow[ 1 ].r * 3 / 16);
            tablicaBledowK[ x-1 ][ y+1 ][ 1 ].g += (wartosciBledow[ 1 ].g * 3 / 16);
            tablicaBledowK[ x-1 ][ y+1 ][ 1 ].b += (wartosciBledow[ 1 ].b * 3 / 16);
        }
        if( x>=0  &&  x<szerokosc/2 ){                      // propaguj 5/16 w dol
            tablicaBledowK[  x  ][ y+1 ][ 0 ].r += (wartosciBledow[ 0 ].r * 5 / 16);
            tablicaBledowK[  x  ][ y+1 ][ 0 ].g += (wartosciBledow[ 0 ].g * 5 / 16);
            tablicaBledowK[  x  ][ y+1 ][ 0 ].b += (wartosciBledow[ 0 ].b * 5 / 16);
            tablicaBledowK[  x  ][ y+1 ][ 1 ].r += (wartosciBledow[ 1 ].r * 5 / 16);
            tablicaBledowK[  x  ][ y+1 ][ 1 ].g += (wartosciBledow[ 1 ].g * 5 / 16);
            tablicaBledowK[  x  ][ y+1 ][ 1 ].b += (wartosciBledow[ 1 ].b * 5 / 16);
        }
        if(x+1>=0 && x+1<szerokosc/2){                      // propaguj 1/16 w prawo dol
            tablicaBledowK[ x+1 ][ y+1 ][ 0 ].r += (wartosciBledow[ 0 ].r / 16);
            tablicaBledowK[ x+1 ][ y+1 ][ 0 ].g += (wartosciBledow[ 0 ].g / 16);
            tablicaBledowK[ x+1 ][ y+1 ][ 0 ].b += (wartosciBledow[ 0 ].b / 16);
            tablicaBledowK[ x+1 ][ y+1 ][ 1 ].r += (wartosciBledow[ 1 ].r / 16);
            tablicaBledowK[ x+1 ][ y+1 ][ 1 ].g += (wartosciBledow[ 1 ].g / 16);
            tablicaBledowK[ x+1 ][ y+1 ][ 1 ].b += (wartosciBledow[ 1 ].b / 16);
        }
    }
}

void propagujBladS(Uint8 wartosciBledow[], int x, int y){
    // jeœli punkt nie wychodzi poza tablice:
    if(x+1>=0 && y>=0 && x+1<szerokosc/2 && y<wysokosc/2){  // propaduj 7/16 na prawo
        tablicaBledowS[ x+1 ][  y  ][ 0 ] += (wartosciBledow[ 0 ] * 7 / 16 );
        tablicaBledowS[ x+1 ][  y  ][ 1 ] += (wartosciBledow[ 1 ] * 7 / 16 );
    }
    // i dla wiersza poni¿ej:
    if(y+1>=0 && y+1<wysokosc/2){
        if(x-1>=0 && x-1<szerokosc/2){                      // propaguj 3/16 w lewo dol
            tablicaBledowS[ x-1 ][ y+1 ][ 0 ] += (wartosciBledow[ 0 ] * 3 / 16);
            tablicaBledowS[ x-1 ][ y+1 ][ 1 ] += (wartosciBledow[ 1 ] * 3 / 16);
        }
        if( x>=0  &&  x<szerokosc/2 ){                      // propaguj 5/16 w dol
            tablicaBledowS[  x  ][ y+1 ][ 0 ] += (wartosciBledow[ 0 ] * 5 / 16);
            tablicaBledowS[  x  ][ y+1 ][ 1 ] += (wartosciBledow[ 1 ] * 5 / 16);
        }
        if(x+1>=0 && x+1<szerokosc/2){                      // propaguj 1/16 w prawo dol
            tablicaBledowS[ x+1 ][ y+1 ][ 0 ] += (wartosciBledow[ 0 ] / 16);
            tablicaBledowS[ x+1 ][ y+1 ][ 1 ] += (wartosciBledow[ 1 ] / 16);
        }
    }
}

void obliczIPropagujBladK(SDL_Color oryginal, SDL_Color malowany, int x, int y){
    SDL_Color wartosciBledow[2] = {{0,0,0,255},{0,0,0,255}};

    if((int) oryginal.r - (int) malowany.r >=0){
        // R -- jeœli malowany jest za ma³o intensywny
        wartosciBledow[0].r = (int) oryginal.r - (int) malowany.r;
    }else{wartosciBledow[1].r = (int) malowany.r - (int)oryginal.r;}

    if((int) oryginal.g - (int) malowany.g >=0){
        // G -- jeœli malowany jest za ma³o intensywny
        wartosciBledow[0].g = (int) oryginal.g - (int) malowany.g;
    }else{wartosciBledow[1].g = (int) malowany.g - (int) oryginal.g;}

    if(oryginal.b - malowany.b >=0){
        // B -- jeœli malowany jest za ma³o intensywny
        wartosciBledow[0].b = (int) oryginal.b - (int) malowany.b;
    }else{wartosciBledow[1].b = (int) malowany.b - (int) oryginal.b;}

    propagujBladK(wartosciBledow, x, y);
}

void obliczIPropagujBladS(Uint8 oryginal, Uint8 malowany, int x, int y){
    Uint8 wartosciBledow[2] = {0,0};

    if((int) oryginal - (int) malowany >=0){
        // R -- jeœli malowany jest za ma³o intensywny
        wartosciBledow[0] = (int) oryginal - (int) malowany;
    }else{wartosciBledow[1] = (int) malowany - (int)oryginal;}

    propagujBladS(wartosciBledow, x, y);
}

SDL_Color uzyskajKolorPoprawionyOBlodK(SDL_Color oryginalny, int x, int y){
    SDL_Color bledyDoDalszejPropagacji[2] = {{0,0,0,255},{0,0,0,255}};

    // oblicz różnice. Propaguj wszystko poniżej 0 i powyżej 255
    int tempR = (int)tablicaBledowK[x][y][0].r - (int) tablicaBledowK[x][y][1].r + (int) oryginalny.r;
    int tempG = (int)tablicaBledowK[x][y][0].g - (int) tablicaBledowK[x][y][1].g + (int) oryginalny.g;
    int tempB = (int)tablicaBledowK[x][y][0].b - (int) tablicaBledowK[x][y][1].b + (int) oryginalny.b;

    // R --
    if(tempR > 255){
        oryginalny.r = 255;
        bledyDoDalszejPropagacji[0].r = (Uint8) ( tempR - 255 );
    } else if (tempR < 0){
        oryginalny.r = 0;
        bledyDoDalszejPropagacji[1].r = (Uint8)( tempR * -1);
    } else {
        oryginalny.r = (Uint8) tempR;
    }
    // G --
    if(tempG > 255){
        oryginalny.g = 255;
        bledyDoDalszejPropagacji[0].g = (Uint8) ( tempG - 255 );
    } else if (tempG < 0){
        oryginalny.g = 0;
        bledyDoDalszejPropagacji[1].g = (Uint8)( tempG * -1);
    } else {
        oryginalny.g = (Uint8) tempG;
    }
    // B --
    if(tempB > 255){
        oryginalny.b = 255;
        bledyDoDalszejPropagacji[0].b = (Uint8) ( tempB - 255 );
    } else if (tempB < 0){
        oryginalny.b = 0;
        bledyDoDalszejPropagacji[1].b = (Uint8)( tempB * -1);
    } else {
        oryginalny.b = (Uint8) tempB;
    }

    // propaguj:
    propagujBladK(bledyDoDalszejPropagacji, x, y);

    return oryginalny;
}

Uint8 uzyskajKolorPoprawionyOBlodS(Uint8 oryginalny, int x, int y){
    Uint8 bledyDoDalszejPropagacji[2] = {0,0};

    // oblicz różnice. Propaguj wszystko poniżej 0 i powyżej 255
    int tempS = (int)tablicaBledowS[x][y][0] - (int) tablicaBledowS[x][y][1] + (int) oryginalny;
    // R --
    if(tempS > 255){
        oryginalny = 255;
        bledyDoDalszejPropagacji[0] = (Uint8) ( tempS - 255 );
    } else if (tempS < 0){
        oryginalny = 0;
        bledyDoDalszejPropagacji[1] = (Uint8)( tempS * -1);
    } else {
        oryginalny = (Uint8) tempS;
    }
    // propaguj:
    propagujBladS(bledyDoDalszejPropagacji, x, y);

    return oryginalny;
}

void floydSteinbergBasic(){
    wyzerujTabliceBledowK();

    for(int y=0; y<wysokosc/2; y++){
        for(int x=0; x<szerokosc/2; x++){
            // bierzemy kolor
            SDL_Color orgKolor = getPixel(x, y);
            orgKolor = uzyskajKolorPoprawionyOBlodK(orgKolor, x,y);

            // konwersja
            Uint8 kolor6bit = z24Kdo6K(orgKolor);
            SDL_Color nowyKolor = z6Kdo24K(kolor6bit);

            // propagowanie i malowanie
            obliczIPropagujBladK(orgKolor, nowyKolor, x, y);
            setPixel(x + szerokosc /2 , y, nowyKolor.r, nowyKolor.g, nowyKolor.b);
        }
    }
}

void floydSteinbergMedianCutBW(){
    wyzerujTabliceBledowS();

    for(int y=0; y<wysokosc/2; y++){
        for(int x=0; x<szerokosc/2; x++){
            // bierzemy kolor
            SDL_Color orgKolor = getPixel(x, y);
            Uint8 orgSzary = (orgKolor.r + orgKolor.g + orgKolor.b) /3;
            orgSzary = uzyskajKolorPoprawionyOBlodS(orgSzary, x,y);

            // konwersja
            Uint8 kolor6bit = znajdzSasiadaBW_6bit_64odcienieSzarego(orgSzary);
            SDL_Color nowyKolor = z6Sdo24K(kolor6bit);
            // propagowanie i malowanie
            obliczIPropagujBladS(orgSzary, nowyKolor.r, x, y);
            setPixel(x + szerokosc /2 , y, nowyKolor.r, nowyKolor.g, nowyKolor.b);
        }
    }
}
