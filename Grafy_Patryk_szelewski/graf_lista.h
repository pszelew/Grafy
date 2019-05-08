#ifndef GRAF_LISTA_H_INCLUDED
#define GRAF_LISTA_H_INCLUDED
#include "graf.h"

class graf_lista: public graf
{
    private:
        lista<wezel_docelowy> *_tablica; //tablica list sasiedztwa
        int n=0;
        int m=0;
        int start=0;
    public:
        graf_lista(int wierzcholki, int startowy); //wczytanie grafu
        virtual ~graf_lista();
        virtual void dodaj_krawedz(int a, int b, int waga);
        virtual bool czy_krawedz(int a, int b);
        virtual int ilosc_sasiadow(int a);
        virtual int waga_krawedzi(int a, int b);
        int wartosc(int a, int b){return _tablica[a].zwroc_wartosc(b)._numer;};
        virtual void dijkstra(std::string nazwa_pliku);
      //  virtual void test_efektywnosci(int ilosc_wierzcholkow, int gestosc_grafu);
};


graf_lista::graf_lista(int wierzcholki, int startowy) : n(wierzcholki), start(startowy)
{
    _tablica=new lista<wezel_docelowy> [n]; //tablica list sasiedztwa
}


graf_lista::~graf_lista()
 {
    for(int i=0;i<n;i++)
    {
        _tablica[i].wyczysc();
    }
    delete[] _tablica;

 }


void graf_lista::dodaj_krawedz(int a, int b, int waga)
{
    wezel_docelowy temp;
    wezel_docelowy temp_2;
    temp._numer=b;
    temp._waga=waga;
    temp_2._numer=a;
    temp_2._waga=waga;
    _tablica[a].dodaj(temp);
    _tablica[b].dodaj(temp_2);
    m++;
}


bool graf_lista::czy_krawedz(int a, int b)
{
    for(int i=0; i<ilosc_sasiadow(a);i++)
    {
        if(_tablica[a].zwroc_wartosc(i)._numer==b)
            return true;
    }

    return false;

}

int graf_lista::ilosc_sasiadow(int a)
{
    int i=0;
    element<wezel_docelowy> *temp=_tablica[a].glowa_listy();
    while(temp!=NULL)
    {
        i++;
        temp=temp->nastepny;
    }
    return i;
}

int graf_lista::waga_krawedzi(int a, int b) //zwracamy wage krawedzi a->b
{
    int i=0;
    while(_tablica[a].zwroc_wartosc(i)._numer!=b)
    {
        i++;
    }

    return _tablica[a].zwroc_wartosc(i)._waga;
}


 void graf_lista::dijkstra(std::string nazwa_pliku)
 {
    std::fstream wyniki;
    wyniki.open( nazwa_pliku, std::ios::out|std::ios::app);
    bool tab_QS[n]; //jesli false -> jest w Q, jesli true -> jest w S
    int tab_koszty_dojscia[n]; //tablica zawierajaca koszty przejscia
    int tab_poprzedniki[n]; //tablica poprzednikow
    int x, y, z, swa; //zmienne pomocnicza
    int stos[n];
    int kopiec[n]; //tablica na ktorej budujemy kopiec
    int wierzcholki_kopca[n]; //przechowuje pozycje wierzcholkow w kopcu
    int dlugosc_kopca=n;
    int rodzic;
    int l_dziecko;
    int p_dziecko;
    int dziecko;
    int min_idx; //indeks blizszego dziecka
    int min_d; //minimalna odleglosc od dziecka

    //Inicjalizujemy tablice zgodnie z algorytmem Dijkstry

    for(int i=0;i<n;i++)
    {
        tab_QS[i]=false;
        tab_koszty_dojscia[i]=INT_MAX;
        tab_poprzedniki[i]=-1;
        kopiec[i]=i; //wypelniamy dowolnymi wierzcholkami
        wierzcholki_kopca[i]=i; //wierzcholki ustawione po kolei
    }
    tab_koszty_dojscia[start]=0;
    //ustawiamy kopiec -> zamieniamy element pierwszy i ostatni

    swa = kopiec[0];
    kopiec[0] = kopiec[start];
    kopiec[start] = swa;          // odtwarzamy wlasnosci kopca po ustawieniu kosztu dotarcia z inf do 0
    wierzcholki_kopca[start] = 0;
    wierzcholki_kopca[0] = start;

    for(int i=0;i<n;i++) //petla glowna -> sciezki w grafie -> dopoki Q nie jest puste
    {
        x = kopiec[0]; // wybieramy najmniejszy element kopca
        kopiec[0]=kopiec[--dlugosc_kopca]; //usuwamy korzen kopca oraz odtwarzamy  kopiec
        wierzcholki_kopca[kopiec[0]]=0;
        rodzic = 0; //ustawiamy


        while(true)                   // W petli idziemy w dół kopca, przywracajac go
        {
            l_dziecko  = 2*rodzic + 1; // Pozycja lewego potomka
            p_dziecko = l_dziecko + 1; // Pozycja prawego potomka
            if(l_dziecko >= dlugosc_kopca)
                break;     // Konczymy, jeśli lewy potomek poza kopcem
            min_d = tab_koszty_dojscia[kopiec[l_dziecko]];          // minimalna odleglosc od potomka
            min_idx = l_dziecko;
            if((p_dziecko < dlugosc_kopca) && min_idx > tab_koszty_dojscia[kopiec[p_dziecko]])
            {
                min_d = tab_koszty_dojscia[kopiec[p_dziecko]];
                min_idx = p_dziecko;
            }

            if(tab_koszty_dojscia[kopiec[rodzic]] <= min_d)
                break;

            swa = kopiec[rodzic];
            kopiec[rodzic] = kopiec[min_idx];
            kopiec[min_idx] = swa;

            wierzcholki_kopca[kopiec[rodzic]] = rodzic;
            wierzcholki_kopca[kopiec[min_idx]] = min_idx;      // na danym poziomie
            rodzic = min_idx;              // i przechodzimy na poziom niższy kopca
        }


        tab_QS[x]=true; //przenosimy wierzcholek z q do s

        for(element<wezel_docelowy> *temp = _tablica[x].glowa_listy(); temp; temp=temp->nastepny) //iteracja po wszystkich sasiadach wierzcholka u
        {
            y=temp->rekord._numer;  //numer wierzcholka sasiada -> y
            if(tab_QS[y]==false)    //jesli sasiad jest w q
            {
                z=temp->rekord._waga;
                if(tab_koszty_dojscia[y]>((tab_koszty_dojscia[x])+(z)))
                {
                    tab_koszty_dojscia[y]=tab_koszty_dojscia[x]+z;
                    tab_poprzedniki[y]=x;

                    for(dziecko = wierzcholki_kopca[y]; dziecko; dziecko = rodzic)
                    {
                        rodzic = dziecko / 2;
                        if(tab_koszty_dojscia[kopiec[rodzic]] <= tab_koszty_dojscia[kopiec[dziecko]])
                            break;

                        swa = kopiec[rodzic];
                        kopiec[rodzic] = kopiec[dziecko];
                        kopiec[dziecko] = swa;
                        wierzcholki_kopca[kopiec[rodzic]] = rodzic;
                        wierzcholki_kopca[kopiec[dziecko]] = dziecko;
                    }
                }
            }
        }

    }

    swa=0;
    for(int i = 0; i < n; i++)
    {
        wyniki <<i<<", "<< tab_koszty_dojscia[i];
        wyniki <<", ";

        for(int j = i; j > -1; j = tab_poprzedniki[j])
        {
            stos[swa] = j;
            swa++;
        }
        while(swa!=0)
        {
            wyniki << stos[--swa];
            if(swa>0)
                wyniki<<", ";
        }
        wyniki << std::endl;

    }
    wyniki.close();
 }


#endif
