#ifndef GRAF_H_INCLUDED
#define GRAF_H_INCLUDED
#include <fstream>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
struct wezel_docelowy //wezel docelowy bedacy elementem macierzy
{
    int _numer=0;
    int _waga=0;
};


class graf //interfejs grafu
{
    public:
        virtual void dodaj_krawedz(int a, int b, int waga)=0;
        virtual void dijkstra(std::string nazwa_pliku)=0;
        virtual bool czy_krawedz(int a, int b)=0;
        virtual int ilosc_sasiadow(int a)=0;
        virtual int waga_krawedzi(int a, int b)=0;
        virtual void test_efektywnosci(int ilosc_wierzcholkow, int gestosc_grafu)=0;
};





#endif // GRAF_H_INCLUDED
