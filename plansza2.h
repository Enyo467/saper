#ifndef PLANSZA_2
#define PLANSZA_2

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAX_Z 8 //max znakow podanych
#define MAX_T 50 //max tablicy
#define MIN_T 9 //min tablicy

void pozostale_bomby(char plansza_wys[MAX_T][MAX_T][14], int dlugosc, int szerokosc, int miny);
int liczenie_pkt(char plansza_wys[MAX_T][MAX_T][14], int dlugosc, int szerokosc, int poziom);

#endif