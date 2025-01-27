#include "plansza2.h"

void pozostale_bomby(char plansza_wys[MAX_T][MAX_T][14], int dlugosc, int szerokosc, int miny)
{
    for(int i = 0; i < dlugosc; i++)
    {
        for(int j = 0; j < szerokosc; j++)
        {
            if(strcmp(plansza_wys[i][j], "\033[34m[f]\033[0m") == 0)
                miny--;
        }
    }
    printf("Pozostale bomby:%2i\n", miny);
}

int liczenie_pkt(char plansza_wys[MAX_T][MAX_T][14], int dlugosc, int szerokosc, int poziom)
{
    int odkryte_pola = 0;
    
    for(int i = 0; i < dlugosc; i++)
    {
        for(int j = 0; j < szerokosc; j++)
        {
            if(strcmp(plansza_wys[i][j], "[#]") != 0 && strcmp(plansza_wys[i][j], "\033[34m[f]\033[0m") != 0)
                odkryte_pola++;
        }
    }
    int pkt = poziom * odkryte_pola;
    return pkt;
}