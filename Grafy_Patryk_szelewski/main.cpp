#include "main.h"
#include <chrono>




int main()
{
    int n; //ilosc wierzcholkow
    int m; //ilosc krawedzi
    int start; // wierzcholek poczatkowy
    int a; //krawedz startowa
    int b; //krawedz koncowa
    int waga; //waga krawedzi
    int wierzcholkow[]={10, 50 , 10, 10, 10};
    int gestosci[]={25, 50, 75, 100};
    remove("testy_efektywnosci_listy.txt");
    remove("wyniki_listy.txt");
    remove("testy_efektywnosci_macierze.txt");
    remove("wyniki_macierze.txt");
    std::fstream dane;
    dane.open( "dane.txt", std::ios::in);
    graf_lista graf_na_listach(0, 0);    //utworzenie macierzy na listach
    graf_macierz graf_na_macierzach(0,0);


   /* for(int i=0; i<m;i++) //wczytanie grafow
    {
        dane >> a >> b >> waga;
        graf_na_listach.dodaj_krawedz(a, b, waga);
    }

*/
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
        {
            graf_na_listach.test_efektywnosci(wierzcholkow[i],gestosci[j]);
            graf_na_macierzach.test_efektywnosci(wierzcholkow[i],gestosci[j]);
        }



}

