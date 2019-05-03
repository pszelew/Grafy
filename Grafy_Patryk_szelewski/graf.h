#ifndef GRAF_H_INCLUDED
#define GRAF_H_INCLUDED
struct wezel_docelowy //wezel docelowy bedacy elementem macierzy
{
    int _numer=0;
    int _waga=0;
};


class graf //interfejs grafu
{
    public:
        virtual void dodaj_krawedz(int a, int b, int waga)=0;
};

#endif // GRAF_H_INCLUDED
