#include "plansza1.h"

void tworzenie_planszy(char plansza_wla[MAX_T][MAX_T][14], int a, int b, int miny, int szerokosc, int dlugosc)
{
    int bomby = 0;
    srand(time(NULL));

    while(bomby < miny)
    {
        int x = rand() % dlugosc;
        int y = rand() % szerokosc;
        if(x != a && y != b)
        {
            if(strcmp(plansza_wla[x][y], "\033[31m[*]\033[0m") != 0)
            {
                strcpy(plansza_wla[x][y], "\033[31m[*]\033[0m");
                bomby++;
            }
        } 
    } //ustawienie bomb

    for(int i = 0; i < dlugosc; i++)
    {
        for(int j = 0; j < szerokosc; j++)
        {
            int ile_bomb = 0;
            if(strcmp(plansza_wla[i][j], "\033[31m[*]\033[0m") != 0)
            {
                for(int m = -1; m < 2; m++)
                {
                    for(int n = -1; n < 2; n++)
                    {
                        int ni = i + m;
                        int nj = j + n;
                        if(ni > -1 && ni < dlugosc && nj > -1 & nj < szerokosc)
                        {
                            if(strcmp(plansza_wla[ni][nj], "\033[31m[*]\033[0m") == 0)
                                ile_bomb++;
                        }
                    }
                }
                switch(ile_bomb)
                {
                    case 1: strcpy(plansza_wla[i][j], "[1]"); break;
                    case 2: strcpy(plansza_wla[i][j], "[2]"); break;
                    case 3: strcpy(plansza_wla[i][j], "[3]"); break;
                    case 4: strcpy(plansza_wla[i][j], "[4]"); break;
                    case 5: strcpy(plansza_wla[i][j], "[5]"); break;
                    case 6: strcpy(plansza_wla[i][j], "[6]"); break;
                    case 7: strcpy(plansza_wla[i][j], "[7]"); break;
                    case 8: strcpy(plansza_wla[i][j], "[8]"); break;
                }
            }
            
        }
    } //przypisanie polom ile bomb jest dookola nich
}

int odkrywanie_planszy(char plansza_wla[MAX_T][MAX_T][14], char plansza_wys[MAX_T][MAX_T][14], char opcja, int x, int y, int odwiedzona[MAX_T][MAX_T], int dlugosc, int szerokosc)
{
    odwiedzona[x][y] = 1;
    if(opcja == 'r')
    {
        strcpy(plansza_wys[x][y], plansza_wla[x][y]);
        if(strcmp(plansza_wla[x][y], "\033[31m[*]\033[0m") == 0 || strcmp(plansza_wla[x][y], "[*]") == 0)
        {
            return 1;
        }
        else if(strcmp(plansza_wla[x][y], "[ ]") == 0)
        {
            for(int i = -1; i < 2; i++)
            {
                for(int j = -1; j < 2; j++)
                {
                    int nx = x + i;
                    int ny = y + j;
                    if(nx > -1 && nx < dlugosc && ny > -1 && ny < szerokosc && odwiedzona[nx][ny] == 0)
                        odkrywanie_planszy(plansza_wla, plansza_wys, opcja, nx, ny, odwiedzona, dlugosc, szerokosc);
                }
            }
            return 0;
        }
        else
        {
            return 0;
        }
    }
    else if(opcja == 'f')
    {
        if(strcmp(plansza_wys[x][y], "\033[34m[f]\033[0m") == 0 || strcmp(plansza_wys[x][y], "[f]") == 0)
            strcpy(plansza_wys[x][y], "[#]");
        else if(strcmp(plansza_wys[x][y], "[#]") == 0)
            strcpy(plansza_wys[x][y], "\033[34m[f]\033[0m");
        return 0;
    }
    odwiedzona[x][y] = 0;
    return 0;
}

void wypisanie_planszy(char plansza_wys[MAX_T][MAX_T][14], int dlugosc, int szerokosc)
{
    system("cls");
    for(int i = 0; i <= dlugosc; i++)
    {
        if(i == 0)
        {
            printf("      ");
            for(int j = 1; j <= szerokosc; j++)
                printf("%2i ", j);
            printf("\n\n");
        }
        else
        {
            printf("%3i   ", i);
            for(int j = 1; j <= szerokosc; j++)
            {
                printf("%s", plansza_wys[i-1][j-1]);
            }
            printf("\n");
        }
    }
    printf("\n");
}
