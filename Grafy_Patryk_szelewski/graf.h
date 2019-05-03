#ifndef GRAF_H_INCLUDED
#define GRAF_H_INCLUDED
#include <fstream>
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
        virtual int waga_krawedzi(int a, int b)=0;
};

#endif // GRAF_H_INCLUDED
