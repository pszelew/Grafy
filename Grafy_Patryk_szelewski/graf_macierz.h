#ifndef GRAF_LISTA_H_INCLUDED
#define GRAF_LISTA_H_INCLUDED
#include "graf.h"




class graf_macierz: public graf
{
        private:
            wezel_docelowy **_macierz;
            unsigned int n;
            unsigned int m=0;
        public:
            graf_macierz(int wierzcholki); //wczytanie grafu
            ~graf_macierz();
            virtual void dodaj_krawedz(int a, int b, int waga);
};



graf_macierz::graf_macierz(int wierzcholki) : n(wierzcholki)
{
    _macierz = new wezel_docelowy*[n];   //tworzymy macierz n x n, stanowiaco macierz sasiedztwa
    for(unsigned int i=0;i<n;++i)
    {
        _macierz[i]= new wezel_docelowy[n];
    }

}



graf_macierz::~graf_macierz()
{
    for(unsigned int i=0; i<n; i++)
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

#endif
