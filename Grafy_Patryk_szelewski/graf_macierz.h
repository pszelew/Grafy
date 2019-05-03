#ifndef GRAF_MACIERZ_H_INCLUDED
#define GRAF_MACIERZ_H_INCLUDED
#include "graf.h"




class graf_macierz: public graf
{
        private:
            wezel_docelowy **_macierz;
            int n=0;
            int m=0;
            int start=0;
        public:
            graf_macierz(int wierzcholki, int startowy); //wczytanie grafu
            ~graf_macierz();
            virtual void dodaj_krawedz(int a, int b, int waga);
            virtual void dijkstra(std::string nazwa_pliku);
            virtual int waga_krawedzi(int a, int b);
};



graf_macierz::graf_macierz(int wierzcholki, int startowy) : n(wierzcholki), start(startowy)
{
    _macierz = new wezel_docelowy*[n];   //tworzymy macierz n x n, stanowiaco macierz sasiedztwa
    for(int i=0;i<n;++i)
    {
        _macierz[i]= new wezel_docelowy[n];
    }

}



graf_macierz::~graf_macierz()
{
    for(int i=0; i<n; i++)
         delete[] _macierz[i];
    delete[] _macierz;
}


void graf_macierz::dodaj_krawedz(int a, int b, int waga)
{
    _macierz[a][b]._numer=1;
    _macierz[a][b]._waga=waga;
    _macierz[b][a]._numer=1;
    _macierz[b][a]._waga=waga;
    m++;
}

int graf_macierz::waga_krawedzi(int a, int b) //zwracamy wage krawedzi a->b
{
    return _macierz[a][b]._waga;
}



void graf_macierz::dijkstra(std::string nazwa_pliku)
 {





 }


#endif
