// funkcje do redukcji kolorów i tworzenia palet
#include "GK2025-Paleta.h"
#include "GK2025-Zmienne.h"
#include "GK2025-Funkcje.h"

/*
** Narzucona 1, 2, 3 to są przepisane
** funkcje z początku pdf'a
** Mają za zadanie pokazać najprostsze
** mechanizmy działania
*/
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
/*
** Kolory 24 bitowe są skanami ekranu,
** (R8G8B8)
** Kolory 8 i 6 bitowe są danymi wyjściowymi
** (R2G2B2)/(Grey6)
*/
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

/*
** Poniżej to co się możesz spodziewać
** z 6bit koloru do standardu.
** z 6 bit szarego do standardu.
*/
SDL_Color z6Kdo24K(Uint8 kolor6bit){
    SDL_Color kolor;
    int R, G, B;
    int nowyR, nowyG, nowyB;

    nowyR = (kolor6bit&(0b00110000))>>4;
    nowyG = (kolor6bit&(0b00001100))>>2;
    nowyB = (kolor6bit&(0b00000011));

    R = nowyR*255.0/3.0;
    G = nowyG*255.0/3.0;
    B = nowyB*255.0/3.0;

    kolor.r = R;
    kolor.g = G;
    kolor.b = B;

    return kolor;

}
SDL_Color z6Sdo24K(Uint8 kolor6bit){
    SDL_Color kolor;
    int Grey;
    int nowyGrey;

    nowyGrey = (kolor6bit&(0b00111111));

    Grey = nowyGrey*255.0/64.0;

    kolor.r = Grey;
    kolor.g = Grey;
    kolor.b = Grey;

    return kolor;

}
/*
** A tutaj:
** z standardu konwersja na 6 bit kolor
** z standardu konwersja na 6 bit szary
*/
Uint8 z24Kdo6K(SDL_Color kolor){
    Uint8 kolor6bit;
    int R, G, B;
    int nowyR, nowyG, nowyB;

    R = kolor.r;
    G = kolor.g;
    B = kolor.b;

    /*
    ** Poniżej dzielimy otrzymane wartości
    ** przez maksymalny zakres (255)
    ** i mnożymy potem przez to ile chcemy
    ** różnych "progów" / "bitów"
    ** mieć na wyjściu. -1. (bo 0 też jest)
    */
    nowyR = round(R*3.0/255.0);
    nowyG = round(G*3.0/255.0);
    nowyB = round(B*3.0/255.0);
    /*
    ** przesunięcia bitowe + 00 na końcu bo nikomu nie ufam.
    ** przez to wyżej (ilość_bitów -1 ) bity nie powinny się pokrywać
    */
    kolor6bit = 00 | (nowyR<<4) | (nowyG<<2) | (nowyB);

    return kolor6bit;

}
Uint8 z24Kdo6S(SDL_Color kolor){
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

// narysowanie narzuconych palet barw
void paletaNarzucona8(){
    Uint8 kolor8bit, szary8bit;
    SDL_Color kolor, nowyKolor, nowySzary;
    // narysowanie za pomocą palety czegoś w celach demonstracyjnych
    for(int y=0; y<wysokosc/2; y++){
        for(int x=0; x<szerokosc/2; x++){
            kolor = getPixel(x, y);
            kolor8bit = z24Kdo8K(kolor);
            nowyKolor = z8Kdo24K(kolor8bit);
            setPixel(x+szerokosc/2, y, nowyKolor.r, nowyKolor.g, nowyKolor.b);
        }
    }
    /*
    ** Dodanie do palety każdego
    ** możliwego koloru w kolejności
    */
    for(int k=0; k<256; k++){
        paleta8k[k] = z8Kdo24K(k);
    }
    /*
    ** Narysowanie wskazanej palety
    */
    narysujPalete8bit(0, 210, paleta8k);
}
void paletaNarzucona6(){
    Uint8 kolor6bit, szary6bit;
    SDL_Color kolor, nowyKolor, nowySzary;

    // narysowanie czegoś w celach demonstracyjnych
    for(int y=0; y<wysokosc/2; y++){
        for(int x=0; x<szerokosc/2; x++){
            // probkowanie pixelow
            kolor = getPixel(x, y);
            // zamiana probki na 6bit kolor
            kolor6bit = z24Kdo6K(kolor);
            // odczytanie z 6k na malowalny pixel
            nowyKolor = z6Kdo24K(kolor6bit);
            setPixel(x + szerokosc /2 , y, nowyKolor.r, nowyKolor.g, nowyKolor.b);
            nowySzary = z6Sdo24K(kolor6bit);
            setPixel(x + szerokosc /2 , y + wysokosc /2, nowySzary.r, nowySzary.g, nowySzary.b);
        }
    }

    // przeiterowanie po każdej dopuszczalnej przez nas wartości bitowej
    for(int k=0; k<64; k++){
        paleta6k[k] = z6Kdo24K(k);
        paleta6s[k] = z6Sdo24K(k);
    }
    narysujPalete6bit(0, wysokosc/2, paleta6k);
    narysujPalete6bit(szerokosc/2, wysokosc/2, paleta6s);
}

void narysujPalete8bit(int px, int py, SDL_Color pal[]){
    int x, y;
    // Dla każdego z 256 kolorów
    for(int k=0; k<256; k++){
        // wyznacz proporcje palety
        y = k / 32;
        x = k % 32;


        // narysuj kwadrat wielkości sqr_size
        for(int xx=0; xx<sqr_size; xx++){
            for(int yy=0; yy<sqr_size; yy++){
                setPixel(x * sqr_size + xx + px,
                         y * sqr_size + yy + py,
                         pal[k].r, pal[k].g, pal[k].b);
            }
        }
    }
}

void narysujPalete6bit(int px, int py, SDL_Color pal[]){
    int x, y;
    // Dla każdego z 64 kolorów
    for(int k=0; k<64; k++){
        // wyznacz proporcje palety
        y = k / 8;
        x = k % 8;


        // narysuj kwadrat wielkości sqr_size
        for(int xx=0; xx<sqr_size; xx++){
            for(int yy=0; yy<sqr_size; yy++){
                setPixel(x * sqr_size + xx + px,
                         y * sqr_size + yy + py,
                         pal[k].r, pal[k].g, pal[k].b);
            }
        }
    }
}
/*
** Zwraca pozycje danego koloru w
** palecie 8K. Jak nie ma, to dodaje
** nowy kolor do palety i podnosi
** "ileKolorow" licznik.
*/
int sprawdzKolor8(SDL_Color kolor){
    if(ileKolorow8 > 0){
        for(int k=0; k<ileKolorow8; k++){
            if(porownajKolory(kolor, paleta8[k])){
                return k;
            }
        }
    }
    return dodajKolor8(kolor);
}
/*
** Porównuje .r, .g, .b, standardowych kolorów (24)
** Funkcja nie zależy od tego, czy 6 czy 8 bitów.
*/
bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2){
    if(kolor1.r != kolor2.r)
        return false;
    if(kolor1.g != kolor2.g)
        return false;
    if(kolor1.b != kolor2.b)
        return false;

    return true;
}
/*
** Dodaje kolor na następne miejsce w palecie
** Następnie zwraca wartość indeksu.
*/
int dodajKolor8(SDL_Color kolor){
    int aktualnyKolor = ileKolorow8;
    paleta8[aktualnyKolor] = kolor;
    if(ileKolorow8<256){
        cout<<aktualnyKolor<<": [";
        cout<<(int)kolor.r<<","<<(int)kolor.g<<","<<(int)kolor.b;
        cout<<"]"<<endl;
    }
    ileKolorow8++;
    return aktualnyKolor;
}
/*
** Dodaje kolor na następne miejsce w palecie
** Następnie zwraca wartość indeksu.
*/
int dodajKolor6(SDL_Color kolor){
    int aktualnyKolor = ileKolorow6;
    paleta6[aktualnyKolor] = kolor;
    if(ileKolorow6<64){
        cout<<aktualnyKolor<<": [";
        cout<<(int)kolor.r<<","<<(int)kolor.g<<","<<(int)kolor.b;
        cout<<"]"<<endl;
    }
    ileKolorow6++;
    return aktualnyKolor;
}
/*
** Wyczyszczenie palet jako indeksów
** kolorów i "ileKolorow"
*/
void czyscPalete8(){
    for(int k=0; k<ileKolorow8; k++)
        paleta8[k] = {0, 0, 0};
    ileKolorow8 = 0;
}
void czyscPalete6(){
    for(int k=0; k<ileKolorow6; k++)
        paleta6[k] = {0, 0, 0};
    ileKolorow6 = 0;
}
/*
** Informuje użytkownika, czy w pierwszej
** ćwiartce jest obrazek korzystający nie
** większej ilości kolorów od tej
** mieszczącej się w palecie8 (256)
*/
void paletaDedykowana8(){
    czyscPalete8();

    int indexKoloru;    // dla pierwszego => 0;
    SDL_Color kolor;
    /*
    ** Dla każdego piksela w pierwszej ćwiartce
    ** Zmierz Pixel. Sprawdź dany kolor w palecie8.
    */
    for(int y=0; y<wysokosc/2; y++){
        for(int x=0; x<szerokosc/2; x++){
            kolor = getPixel(x, y);
            indexKoloru = sprawdzKolor8(kolor);
        }
    }
    cout <<endl << "ile kolorow: " << ileKolorow8 << endl;
    /*
    ** Jeśli ilość kolorow jest mniejsza niż pojemnosc palety
    ** to poinformuj o tym uzytkownika
    */
    if(ileKolorow8 <= 256){
        cout << "Paleta spelnia ograniczenia 8-bit / piksel" << endl;
        narysujPalete8bit(0, 210, paleta8);
    }else{
        cout << "Paleta przekracza ograniczenia 8-bit / piksel" << endl;
    }
}

void czyscPalete(){
    for(int k=0; k<ileKolorow8; k++){
        paleta8[k] = {0, 0, 0};
    }
    ileKolorow8 = 0;
    for(int k=0; k<256; k++){
        paleta8s[k] = {0, 0, 0};
        paleta8k[k] = {0, 0, 0};

    }
    for(int k=0; k<ileKolorow6; k++){
        paleta6[k] = {0, 0, 0};
    }
    ileKolorow6 = 0;
    for(int k=0; k<65; k++){
        paleta6k[k] = {0, 0, 0};
        paleta6s[k] = {0, 0, 0};
    }
}

void narysujPalete3b(int px, int py, SDL_Color pal3b[]){
    int x,y;
    for(int k=0; k<8; k++){
        y = k/32;
        x = k%32;

        for(int xx=0; xx<40; xx++){
            for(int yy=0; yy<40; yy++){
                setPixel(x*40+xx+px, y*40+yy+py, pal3b[k].r, pal3b[k].g, pal3b[k].b);
            }
        }

    }
}

void narysujPalete_6bit_64odcienie_szarego(int px, int py, SDL_Color pal6b[]){
    int x,y;
    for(int k=0; k<64; k++){
        y = k/8;
        x = k%8;

        for(int xx=0; xx<40; xx++){
            for(int yy=0; yy<40; yy++){
                setPixel(x*40+xx+px, y*40+yy+py, pal6b[k].r, pal6b[k].g, pal6b[k].b);
            }
        }

    }
}





