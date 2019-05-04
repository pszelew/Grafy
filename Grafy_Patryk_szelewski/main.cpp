#include "main.h"





int main()
{
    int n; //ilosc wierzcholkow
    int m; //ilosc krawedzi
    int start; // wierzcholek poczatkowy
    int a; //krawedz startowa
    int b; //krawedz koncowa
    int waga; //waga krawedzi
    remove("wyniki.txt");
    std::fstream dane;

    dane.open( "dane.txt", std::ios::in);



    dane >> m >> n >> start;
    graf_macierz graf_na_macierzach(n, start);    //utworzenie macierzy na listach


    for(int i=0; i<m;i++) //wczytanie grafow
    {
        dane >> a >> b >> waga;
        graf_na_macierzach.dodaj_krawedz(a, b, waga);
    }



    graf_na_macierzach.dijkstra("wyniki.txt");




}

