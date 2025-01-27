#ifndef PLANSZA_1
#define PLANSZA_1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAX_Z 8 //max znakow podanych
#define MAX_T 50 //max tablicy
#define MIN_T 9 //min tablicy

void tworzenie_planszy(char plansza_wla[MAX_T][MAX_T][14], int a, int b, int miny, int szerokosc, int dlugosc);
int odkrywanie_planszy(char plansza_wla[MAX_T][MAX_T][14], char plansza_wys[MAX_T][MAX_T][14], char opcja, int x, int y, int odwiedzona[MAX_T][MAX_T], int dlugosc, int szerokosc);
void wypisanie_planszy(char plansza_wys[MAX_T][MAX_T][14], int dlugosc, int szerokosc);

#endif