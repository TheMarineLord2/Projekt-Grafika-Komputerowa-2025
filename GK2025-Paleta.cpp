// funkcje do redukcji kolorów i tworzenia palet
#include "GK2025-Paleta.h"
#include "GK2025-Zmienne.h"
#include "GK2025-Funkcje.h"



void narzuconaV1(){
    SDL_Color kolor;
    int R, G, B;
    int kolor8bit;
    int nowyR, nowyG, nowyB;

    for(int y=0; y<wysokosc/2; y++){
        for(int x=0; x<szerokosc/2; x++){
            kolor = getPixel(x,y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            nowyR = R>>5;
            nowyG = G>>5;
            nowyB = B>>6;

            R = nowyR<<5;
            G = nowyG<<5;
            B = nowyB<<6;

            setPixel(x+szerokosc/2, y, R, G, B);
        }
    }
}

void narzuconaV2(){
    SDL_Color kolor;
    int R, G, B;
    int kolor8bit;
    int nowyR, nowyG, nowyB;

    for(int y=0; y<wysokosc/2; y++){
        for(int x=0; x<szerokosc/2; x++){
            kolor = getPixel(x,y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            nowyR = R>>5;
            nowyG = G>>5;
            nowyB = B>>6;

            R = nowyR*255.0/7.0;
            G = nowyG*255.0/7.0;
            B = nowyB*255.0/3.0;

            setPixel(x, y + wysokosc/2, R, G, B);
        }
    }
}


void narzuconaV3(){
    SDL_Color kolor;
    int R, G, B;
    int kolor8bit;
    int nowyR, nowyG, nowyB;

    for(int y=0; y<wysokosc/2; y++){
        for(int x=0; x<szerokosc/2; x++){
            kolor = getPixel(x,y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            nowyR = round(R*7.0/255.0);
            nowyG = round(G*7.0/255.0);
            nowyB = round(B*3.0/255.0);

            R = nowyR*255.0/7.0;
            G = nowyG*255.0/7.0;
            B = nowyB*255.0/3.0;

            setPixel(x + szerokosc/2, y + wysokosc/2, R, G, B);
        }
    }
}


Uint8 z24Kdo8K(SDL_Color kolor){
    Uint8 kolor8bit;
    int R, G, B;
    int nowyR, nowyG, nowyB;

    R = kolor.r;
    G = kolor.g;
    B = kolor.b;

    nowyR = round(R*7.0/255.0);
    nowyG = round(G*7.0/255.0);
    nowyB = round(B*3.0/255.0);

    kolor8bit = (nowyR<<5) | (nowyG<<2) | nowyB;

    return kolor8bit;

}

SDL_Color z8Kdo24K(Uint8 kolor8bit){

    SDL_Color kolor;
    int R, G, B;
    int nowyR, nowyG, nowyB;

    nowyR = (kolor8bit&(0b11100000))>>5;
    nowyG = (kolor8bit&(0b00011100))>>2;
    nowyB = (kolor8bit&(0b00000011));

    R = nowyR*255.0/7.0;
    G = nowyG*255.0/7.0;
    B = nowyB*255.0/3.0;

    kolor.r = R;
    kolor.g = G;
    kolor.b = B;

    return kolor;

}
SDL_Color z6Kdo24K(Uint8 kolor6bit){
    SDL_Color kolor;
    int R, G, B;
    int nowyR, nowyG, nowyB;

    nowyR = (kolor6bit&(0b11000000))>>6;
    nowyG = (kolor6bit&(0b00110000))>>4;
    nowyB = (kolor6bit&(0b00001100))>>2;

    R = nowyR*255.0/3.0;
    G = nowyG*255.0/3.0;
    B = nowyB*255.0/3.0;

    kolor.r = R;
    kolor.g = G;
    kolor.b = B;

    return kolor;

}

SDL_Color z6Kdo24K_Grey(Uint8 kolor6bit){
    SDL_Color kolor;
    int Grey;
    int nowyGrey;

    nowyGrey = (kolor6bit&(0b11111100))>>2;

    Grey = nowyGrey*255.0/64.0;

    kolor.r = Grey;
    kolor.g = Grey;
    kolor.b = Grey;

    return kolor;

}


Uint8 z24Kdo6K(SDL_Color kolor){
    Uint8 kolor6bit;
    int R, G, B;
    int nowyR, nowyG, nowyB;

    R = kolor.r;
    G = kolor.g;
    B = kolor.b;

    nowyR = round(R*3.0/255.0);
    nowyG = round(G*3.0/255.0);
    nowyB = round(B*3.0/255.0);

    kolor6bit = (nowyR<<6) | (nowyG<<4) | (nowyB<<2) | 00;

    return kolor6bit;

}

Uint8 z24Kdo6K_grey(SDL_Color kolor){
    Uint8 szary6bit;
    int R, G, B;
    int nowyGrey;

    R = kolor.r;
    G = kolor.g;
    B = kolor.b;

    nowyGrey = round((R+G+B/3)*(64.0/255.0));

    szary6bit = (nowyGrey<<2) | 00;

    return szary6bit;

}

void paletaNarzucona8(){
    Uint8 kolor8bit, szary8bit;
    SDL_Color kolor, nowyKolor, nowySzary;

    for(int y=0; y<wysokosc/2; y++){
        for(int x=0; x<szerokosc/2; x++){
            kolor = getPixel(x, y);
            kolor8bit = z24Kdo8K(kolor);
            nowyKolor = z8Kdo24K(kolor8bit);
            setPixel(x+szerokosc/2, y, nowyKolor.r, nowyKolor.g, nowyKolor.b);
        }
    }

    for(int k=0; k<256; k++){
        paleta8k[k] = z8Kdo24K(k);
    }
    narysujPalete(0, 210, paleta8k);
}

void paletaNarzucona6(){
    Uint8 kolor6bit, szary6bit;
    SDL_Color kolor, nowyKolor, nowySzary;

    for(int y=0; y<wysokosc/2; y++){
        for(int x=0; x<szerokosc/2; x++){
            kolor = getPixel(x, y);
            kolor6bit = z24Kdo6K(kolor);
            nowyKolor = z6Kdo24K(kolor6bit);
            setPixel(x + szerokosc /2, y, nowyKolor.r, nowyKolor.g, nowyKolor.b);
            nowySzary = z6Kdo24K_Grey(kolor6bit);
            setPixel(x, y + wysokosc /2, nowySzary.r, nowySzary.g, nowySzary.b);
        }
    }

    /*for(int k=0; k<256; k++){
        paleta8k[k] = z8Kdo24K(k);
    }
    narysujPalete(0, 210, paleta8k);*/
}

void narysujPalete(int px, int py, SDL_Color pal8[]){
    int x, y;
    for(int k=0; k<256; k++){
        y = k / 32;
        x = k % 32;

        for(int xx=0; xx<10; xx++){
            for(int yy=0; yy<10; yy++){
                setPixel(x*10+xx+px, y*10+yy+py, pal8[k].r, pal8[k].g, pal8[k].b);
            }
        }
    }
}

int sprawdzKolor(SDL_Color kolor){
    if(ileKolorow > 0){
        for(int k=0; k<ileKolorow; k++){
            if(porownajKolory(kolor, paleta8[k])){
                return k;
            }
        }
    }
    return dodajKolor(kolor);
}

bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2){
    if(kolor1.r != kolor2.r)
        return false;
    if(kolor1.g != kolor2.g)
        return false;
    if(kolor1.b != kolor2.b)
        return false;

    return true;
}

int dodajKolor(SDL_Color kolor){
    int aktualnyKolor = ileKolorow;
    paleta8[aktualnyKolor] = kolor;
    if(ileKolorow<256){
        cout<<aktualnyKolor<<": [";
        cout<<(int)kolor.r<<","<<(int)kolor.g<<","<<(int)kolor.b;
        cout<<"]"<<endl;
    }
    ileKolorow++;
    return aktualnyKolor;
}

void czyscPalete(){
    for(int k=0; k<ileKolorow; k++)
        paleta8[k] = {0, 0, 0};
    ileKolorow = 0;
}

/*void paletaDedykowana8(){
    czyscPalete();
    int indexKoloru;
    SDL_Color kolor;
    for(int y=0; y<wysokosc/2; y++){
        for(int x=0; x<szerokosc/2; x++){
            kolor = getPixel(x, y);
            indexKoloru = sprawdzKolor(kolor);
        }
    }
    cout <<endl << "ile kolorow: " << ileKolorow << endl;

    if(ileKolorow <= 256){
        cout << "Paleta spelnia ograniczenia 8-bit / piksel" << endl;
        narysujPalete(0, 210, paleta8);
    }else{
        cout << "Paleta przekracza ograniczenia 8-bit / piksel" << endl;
    }
}*/






