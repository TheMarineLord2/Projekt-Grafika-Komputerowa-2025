####################
#STRUKTURA PROJEKTU#
####################

PROJEKT W SZAROSCI / PROJEKT W KOLORZE

PALETA DEDYKOWANA / PALETA NARZUCONA

//pomocnicze

###############
#STANDARYZACJA#
###############

Due to maths being mathy and theory on its way.

r:0.168736 -> R: 3,57/6 -> 3 bytes
g:0,331264 -> G: 1,80/6 -> 2 bytes
b:0.5      -> B: 1,20/6 -> 1 byte

Maski:
R: 0b11100000
G: 0b00011000
B: 0b00000100

#######################################
#RZECZY_WYMAGANE_DLA_OBU_PALET_KOLOROW#
#######################################

//////////KONWERTERY KOLOROW//////////

/* converting scanned color to 6b_color */
Uint8 converter24to6(SDL_Color scanned);
/* converting scanned color to 6b_gray */
Uint8 converter24to6_grey(SDL_Color scanned);
/* converting 6b_color to print_color */
SDL_Color converter6to24(Uint8 6bit_color);
/* converting 6b_color to print_gray*/
SDL_Color converter6to24_grey(Uint8 6bit_grey);


//////////SKANNER KOLOROW/////////////

/* reseting index of scanned colors*/
void resetPalette();
void 



bool areColorsIdenticall(SDL_Color color1, SDL_Color color2)






//////////PALETA DEDYKOWANA//////////

//////////PALETA NARZUCONA//////////