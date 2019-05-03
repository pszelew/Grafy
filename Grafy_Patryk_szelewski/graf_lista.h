#ifndef GRAF_LISTA_H_INCLUDED
#define GRAF_LISTA_H_INCLUDED
#include "lista.h"
#include "graf.h"

class graf_lista
{
    private:
        lista<wezel_docelowy> **_tablica; //tablica list sasiedztwa
        unsigned int n;
        unsigned int m=0;
    public:
        graf_lista(int wierzcholki); //wczytanie grafu
        ~graf_lista();
        virtual void dodaj_krawedz(int a, int b, int waga)
};


virtual graf_lista<typ, n, m>::graf_lista(int wierzcholki)
{
    _tablica=new _tablica *[n]; //tablica list sasiedztwa

    for(i = 0; i < n; i++)
        _tablica[i] = NULL;
}

virtual ~graf_lista()
{
     for(int i=0; i<n; i++)
         _tablica[i].wyczysc();
    delete[] _tablica;
}



void graf_macierz::dodaj_krawedz(int a, int b, int waga)
{
    wezel_docelowy *temp = new wezel_docelowy;
    wezel_docelowy *temp_2 = new wezel_docelowy;
    temp->_numer=b;
    temp->_waga=waga;
    temp_2->_numer=a;
    temp_2->_waga=waga;
    _tablica[a]->dodaj(temp);
    _tablica[b]->dodaj(temp_2);
}




#endif
