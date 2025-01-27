#ifndef PLANSZA_3
#define PLANSZA_3

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAX_Z 8 //max znakow podanych
#define MAX_T 50 //max tablicy
#define MIN_T 9 //min tablicy

void przegrana(char plansza_wla[MAX_T][MAX_T][14], char plansza_wys[MAX_T][MAX_T][14], int dlugosc, int szerokosc);
int czy_koniec(char plansza_wys[MAX_T][MAX_T][14], int dlugosc, int szerokosc, int miny);
void sortowanie(int licznik, int najlepszy[1000], char imiona[1000][25]);

#endif