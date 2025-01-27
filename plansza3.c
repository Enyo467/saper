#include "plansza3.h"

void przegrana(char plansza_wla[MAX_T][MAX_T][14], char plansza_wys[MAX_T][MAX_T][14], int dlugosc, int szerokosc)
{
    for(int i = 0; i < dlugosc; i++)
    {
        for(int j = 0; j < szerokosc; j++)
        {
            if(strcmp(plansza_wla[i][j], "\033[31m[*]\033[0m") == 0)
                strcpy(plansza_wys[i][j], "\033[31m[*]\033[0m");
        }
    }
}

int czy_koniec(char plansza_wys[MAX_T][MAX_T][14], int dlugosc, int szerokosc, int miny)
{
    int pola = 0; //ilosc odkrytych pol
    int bomb = 0;
    for(int i = 0; i < dlugosc; i++)
    {
        for(int j = 0; j < szerokosc; j++)
        {
            if(strcmp(plansza_wys[i][j], "[#]") != 0)
            {
                if(strcmp(plansza_wys[i][j], "\033[34m[f]\033[0m") == 0)
                    bomb++;
                pola++;
            }
        }
    }
    if(pola == (dlugosc*szerokosc) && bomb == miny)
        return 1; //1 to koniec gry, wygrana
    return 0;
}

void sortowanie(int licznik, int najlepszy[1000], char imiona[1000][25])
{
    for(int i = 0; i < licznik - 1; i++)
    {
        for(int j = 0; j < licznik - i - 1; j++)
        {
            if(najlepszy[j] < najlepszy[j+1])
            {
                int temp = najlepszy[j];
                najlepszy[j] = najlepszy[j+1];
                najlepszy[j+1] = temp;
                char teemp[25];
                strcpy(teemp, imiona[j]);
                strcpy(imiona[j], imiona[j+1]);
                strcpy(imiona[j+1], teemp);
            }
        }
    }
    printf("TOP 5 GRACZY:\n");
    for(int i = 0; i < 5 && i < licznik; i++)
        printf("%d. %d - %s\n", i+1, najlepszy[i], imiona[i]);
}