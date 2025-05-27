#ifndef GK2025_PALETA_H_INCLUDED
#define GK2025_PALETA_H_INCLUDED
#include "GK2025-Dithering.h"
#include "GK2025-Zmienne.h"
#include "GK2025-Pliki.h"
#include <iostream>


void wyzerujTabliceBledow(){
    for(int i=0; i<szerokosc/2; i++){
        for(int j=0; j<wysokosc/2; j++){
            tablicaBledow[i][j][0].r = 0;
            tablicaBledow[i][j][0].g = 0;
            tablicaBledow[i][j][0].b = 0;
            tablicaBledow[i][j][1].r = 0;
            tablicaBledow[i][j][1].g = 0;
            tablicaBledow[i][j][1].b = 0;
        }
    }
}

void propagujBlad(SDL_Color wartosciBledow[], int x, int y){
    // jeœli punkt nie wychodzi poza tablice:
    if(x+1>=0 && y>=0 && x+1<szerokosc/2 && y<wysokosc/2){  // propaduj 7/16 na prawo
        tablicaBledow[ x+1 ][  y  ][ 0 ].r += (wartosciBledow[ 0 ].r * 7 / 16 );
        tablicaBledow[ x+1 ][  y  ][ 0 ].g += (wartosciBledow[ 0 ].g * 7 / 16 );
        tablicaBledow[ x+1 ][  y  ][ 0 ].b += (wartosciBledow[ 0 ].b * 7 / 16 );
        tablicaBledow[ x+1 ][  y  ][ 1 ].r += (wartosciBledow[ 1 ].r * 7 / 16 );
        tablicaBledow[ x+1 ][  y  ][ 1 ].g += (wartosciBledow[ 1 ].g * 7 / 16 );
        tablicaBledow[ x+1 ][  y  ][ 1 ].b += (wartosciBledow[ 1 ].b * 7 / 16 );
    }
    // i dla wiersza poni¿ej:
    if(y+1>=0 && y+1<wysokosc/2){
        if(x-1>=0 && x-1<szerokosc/2){                      // propaguj 3/16 w lewo dol
            tablicaBledow[ x-1 ][ y+1 ][ 0 ].r += (wartosciBledow[ 0 ].r * 3 / 16);
            tablicaBledow[ x-1 ][ y+1 ][ 0 ].g += (wartosciBledow[ 0 ].g * 3 / 16);
            tablicaBledow[ x-1 ][ y+1 ][ 0 ].b += (wartosciBledow[ 0 ].b * 3 / 16);
            tablicaBledow[ x-1 ][ y+1 ][ 1 ].r += (wartosciBledow[ 1 ].r * 3 / 16);
            tablicaBledow[ x-1 ][ y+1 ][ 1 ].g += (wartosciBledow[ 1 ].g * 3 / 16);
            tablicaBledow[ x-1 ][ y+1 ][ 1 ].b += (wartosciBledow[ 1 ].b * 3 / 16);
        }
        if( x>=0  &&  x<szerokosc/2 ){                      // propaguj 5/16 w dol
            tablicaBledow[  x  ][ y+1 ][ 0 ].r += (wartosciBledow[ 0 ].r * 5 / 16);
            tablicaBledow[  x  ][ y+1 ][ 0 ].g += (wartosciBledow[ 0 ].g * 5 / 16);
            tablicaBledow[  x  ][ y+1 ][ 0 ].b += (wartosciBledow[ 0 ].b * 5 / 16);
            tablicaBledow[  x  ][ y+1 ][ 1 ].r += (wartosciBledow[ 1 ].r * 5 / 16);
            tablicaBledow[  x  ][ y+1 ][ 1 ].g += (wartosciBledow[ 1 ].g * 5 / 16);
            tablicaBledow[  x  ][ y+1 ][ 1 ].b += (wartosciBledow[ 1 ].b * 5 / 16);
        }
        if(x+1>=0 && x+1<szerokosc/2){                      // propaguj 1/16 w prawo dol
            tablicaBledow[ x+1 ][ y+1 ][ 0 ].r += (wartosciBledow[ 0 ].r / 16);
            tablicaBledow[ x+1 ][ y+1 ][ 0 ].g += (wartosciBledow[ 0 ].g / 16);
            tablicaBledow[ x+1 ][ y+1 ][ 0 ].b += (wartosciBledow[ 0 ].b / 16);
            tablicaBledow[ x+1 ][ y+1 ][ 1 ].r += (wartosciBledow[ 1 ].r / 16);
            tablicaBledow[ x+1 ][ y+1 ][ 1 ].g += (wartosciBledow[ 1 ].g / 16);
            tablicaBledow[ x+1 ][ y+1 ][ 1 ].b += (wartosciBledow[ 1 ].b / 16);
        }
    }
}
//
void obliczIPropagujBlad(SDL_Color oryginal, SDL_Color malowany, int x, int y){
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

    propagujBlad(wartosciBledow, x, y);
}

SDL_Color uzyskajKolorPoprawionyOBlod(SDL_Color oryginalny, int x, int y){
    SDL_Color bledyDoDalszejPropagacji[2] = {{0,0,0,255},{0,0,0,255}};

    // oblicz różnice. Propaguj wszystko poniżej 0 i powyżej 255
    int tempR = (int)tablicaBledow[x][y][0].r - (int) tablicaBledow[x][y][1].r + (int) oryginalny.r;
    int tempG = (int)tablicaBledow[x][y][0].g - (int) tablicaBledow[x][y][1].g + (int) oryginalny.g;
    int tempB = (int)tablicaBledow[x][y][0].b - (int) tablicaBledow[x][y][1].b + (int) oryginalny.b;

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
    propagujBlad(bledyDoDalszejPropagacji, x, y);

    return oryginalny;
}

#endif
