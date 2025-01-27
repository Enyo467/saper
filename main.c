#include "plansza1.h"
#include "plansza2.h"
#include "plansza3.h"

#define MIN_T 9 //min tablicy
#define MAX_T 50 //max tablicy
#define MAX_Z 8 //max znakow podanych

int main(int argc, char *argv[])
{
    int poziom, szerokosc, dlugosc, miny;
    char plansza_wys[MAX_T][MAX_T][14]; //plansza ktora sie wyswietla w terminalu
    char plansza_wla[MAX_T][MAX_T][14]; //plansza wlasciwa
    int odwiedzona[MAX_T][MAX_T]; //pilnuje czy dana komorka zostala odwiedzona czy nie
    char ruch[MAX_Z]; //tablica na znaki wpisywane podczas podawanie ruchu
    char opcja; //odkrycie lub oflagowanie
    int a, b, c ; //pierwsza i druga wspolrzedna, c sprawdza czy trafiona na bombe
    int pkt = 0;
    int dobre;
    int opt;
    char *nazwapliku = NULL;
    srand(time(NULL));

    system("cls");

    FILE *plansza;

    while((opt = getopt(argc, argv, "f:")) != -1)
    {
        switch(opt)
        {
            case 'f':
                dobre = 0;
                nazwapliku = optarg;
                poziom = 1;
                char linie[35];
                if(nazwapliku == NULL)
                    {
                        printf("Nie podano sciezki do pliku\n");
                        fclose(plansza);
                        return 1;
                    }
                plansza = fopen(nazwapliku, "r");
                if(plansza == NULL)
                    {
                        printf("Blad otwarcia pliku!\n");
                        fclose(plansza);
                        return 1;
                    }
                if(fscanf(plansza, "%d %d %d", &dlugosc, &szerokosc, &miny) != 3)
                    {
                        printf("Nieprawidlowy format danych.\n");
                        fclose(plansza);
                        return 1;
                    }
                fgets(linie, sizeof(linie), plansza);
                for(int i = 0; i < dlugosc; i++)
                    {
                        fgets(linie, sizeof(linie), plansza);
                        for(int j = 0; j < szerokosc; j++)
                        {
                            odwiedzona[i][j] = 0;
                            strcpy(plansza_wys[i][j], "[#]");
                            strncpy(plansza_wla[i][j], &linie[j*3], 3);
                        }
                    }
                for(int i = 0; i < dlugosc; i++)
                    {
                        for(int j = 0; j < szerokosc; j++)
                        {
                            printf("%s", plansza_wla[i][j]);
                        }
                        printf("\n");
                    } //test
                int powodzenie = 0;
                while(fscanf(plansza," %c %d %d", &opcja, &a, &b) == 3)
                {
                    
                    a-=1;
                    b-=1;
                    wypisanie_planszy(plansza_wys, dlugosc, szerokosc);
                    c = odkrywanie_planszy(plansza_wla, plansza_wys, opcja, a, b, odwiedzona, dlugosc, szerokosc);
                    printf("Ruch: %c %d %d, Wynik %d\n", opcja, a+1, b+1, c);
                    if(c != 1)
                    {
                        dobre++;
                        if(czy_koniec(plansza_wys, dlugosc, szerokosc, miny) == 1)
                        {
                            powodzenie = 1;
                            break;
                        }
                    }
                    else
                    {
                        pkt -=1;
                        break;
                    }
                }
                pkt = pkt + liczenie_pkt(plansza_wys, dlugosc, szerokosc, poziom);
                printf("Liczba poprawnych krokow: %d\nLiczba punktow: %d\nCzy gra zakonczyla sie powodzeniem: %d\n", dobre, pkt, powodzenie);
                fclose(plansza);
                return 0;
                break;
            default:
                printf("Poprawny sposob uzycia: %s -f <sciezka do pliku>\n", argv[0]);
                return 1;
        }
    }


    //WYBOR POZIOMU
    printf("\nWybierz poziom trudnosci:\nLatwy - 1\nSredni - 2\nTrudny - 3\nTryb wlasny - 4\n\n");
    scanf("%i", &poziom);
    while(poziom < 1 || poziom > 4)
    {
        printf("Bledny numer poziomu trudnosci!\nPodaj numer jeszcze raz: \n\n");
        scanf("%i", &poziom);
    }
    if(poziom == 1 )
    {
        szerokosc = 9;
        dlugosc = 9;
        miny = 10;
    }
    else if(poziom == 2)
    {
        szerokosc = 16;
        dlugosc = 16;
        miny = 40;
    }
    else if(poziom == 3)
    {
        szerokosc = 30;
        dlugosc = 16;
        miny = 99;
    }
    else if(poziom == 4)
    {
        printf("Wybierz szerokosc w zakresie od 9 do 30:\n\n");
        scanf("%i", &szerokosc);
        while(szerokosc < 9 || szerokosc > 30)
        {
            printf("Bledna szerokosc!\nPodaj szerokosc jeszcze raz:\n\n");
            scanf("%i", &szerokosc);
        }
        printf("Wybierz dlugosc w zakresie od 9 do 30:\n\n");
        scanf("%i", &dlugosc);
        while(dlugosc < 9 || dlugosc > 30)
        {
            printf("Bledna dlugosc!\nPodaj dlugosc jeszcze raz:\n\n");
            scanf("%i", &dlugosc);
        }
        printf("Wybierz ilosc min, w zakresie od %i do %i:\n\n",(szerokosc*dlugosc)/10, (3*szerokosc*dlugosc)/10 );
        scanf("%i", &miny);
        while(miny < (szerokosc*dlugosc)/10 || miny > (3*szerokosc*dlugosc)/10)
        {
            printf("Bledna ilosc min!\nPodaj ilosc min jeszcze raz:\n\n");
            scanf("%i", &miny);
        }
    }

    getchar(); //usuniecie znaku nowej linii w buforze

    for(int i = 0; i < dlugosc; i++)
    {
        for(int j = 0; j < szerokosc; j++)
        {
            strcpy(plansza_wla[i][j], "[ ]");
            strcpy(plansza_wys[i][j], "[#]");
            odwiedzona[i][j] = 0;
        }
    } //przypisanie wszystkim polom planszy wlasciwej pustych pol, polom planszy wyswietlanej zakrytych pol, statusu nieodwiedzonej komorki

    //wypisanie pierwszej planszy do terminala
    wypisanie_planszy(plansza_wys, dlugosc, szerokosc);
    pozostale_bomby(plansza_wys, dlugosc, szerokosc, miny);
    pkt = liczenie_pkt(plansza_wys, dlugosc, szerokosc, poziom);
    printf("Wynik: %d\n", pkt);

    printf("Podaj swoj pierwszy ruch:\n");
    fgets(ruch, sizeof(ruch), stdin);
    sscanf(ruch, "%c %i %i", &opcja, &a, &b);
    a-=1;
    b-=1;
    tworzenie_planszy(plansza_wla, a, b, miny, szerokosc, dlugosc);
    c = odkrywanie_planszy(plansza_wla, plansza_wys, opcja, a, b, odwiedzona, dlugosc, szerokosc);
    

    while(c != 1)
    {
        wypisanie_planszy(plansza_wys, dlugosc, szerokosc);
        pozostale_bomby(plansza_wys, dlugosc, szerokosc, miny);
        pkt = liczenie_pkt(plansza_wys, dlugosc, szerokosc, poziom);
        printf("Wynik: %d\n", pkt);
        if(czy_koniec(plansza_wys, dlugosc, szerokosc, miny) == 1)
        {
            printf("KONIEC GRY!\nWcisnij ENTER przejsc dalej.\n");
            fgets(ruch, sizeof(ruch), stdin);
            sscanf(ruch, "\n");
            break;
        }
        printf("Podaj kolejny ruch:\n");
        fgets(ruch, sizeof(ruch), stdin);
        sscanf(ruch, "%c %i %i", &opcja, &a, &b);
        a-=1;
        b-=1;
        c = odkrywanie_planszy(plansza_wla, plansza_wys, opcja, a, b, odwiedzona, dlugosc, szerokosc);
    } //dopoki nie trafi sie na bombe

    if(c == 1)
    {
        wypisanie_planszy(plansza_wys, dlugosc, szerokosc);
        printf("KONIEC GRY!\nWcisnij ENTER przejsc dalej.\n");
        fgets(ruch, sizeof(ruch), stdin);
        sscanf(ruch, "\n");
        przegrana(plansza_wla, plansza_wys, dlugosc, szerokosc);
        system("cls");
        wypisanie_planszy(plansza_wys, dlugosc, szerokosc);
    }// jak juz trafi sie na bombe

    //koniec gry, podanie swojego nicku i zapisanie go
    char nick[25];
    FILE *file = fopen("wyniki.txt", "a");
    if(file == NULL)
    {
        printf("Blad otwarcia pliku!\n");
        return 1;
    }

    printf("Podaj swoj nick: ");
    fgets(nick, sizeof(nick), stdin);
    nick[strcspn(nick, "\n")] = '\0';
    fprintf(file, "%d %s\n", pkt, nick);
    
    fclose(file);

    //wypisywanie top5 graczy
    FILE *plik = fopen("wyniki.txt", "r");

    int licznik = 0;
    int najlepszy[1000];
    char imiona[1000][25];

    while(fscanf(plik, "%d %s", &najlepszy[licznik], imiona[licznik]) == 2)
        licznik++;
    fclose(plik);
    
    sortowanie(licznik, najlepszy, imiona);
    
    

    return 0;
}