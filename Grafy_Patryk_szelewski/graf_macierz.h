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
            virtual bool czy_krawedz(int a, int b);
            virtual int ilosc_sasiadow(int a);
           virtual void test_efektywnosci(int ilosc_wierzcholkow, int gestosc_grafu);
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


bool graf_macierz::czy_krawedz(int a, int b)
{
    if(_macierz[a][b]._numer==1)
        return true;
    return false;
}

int graf_macierz::ilosc_sasiadow(int a)
{
    int j=0;
    for(int i=0;i<n;i++)
    {
        if(_macierz[a][i]._numer==1)
            j++;
    }
    return j;
}

int graf_macierz::waga_krawedzi(int a, int b) //zwracamy wage krawedzi a->b
{
    return _macierz[a][b]._waga;
}



 void graf_macierz::dijkstra(std::string nazwa_pliku)
 {
    std::fstream wyniki;
    wyniki.open( nazwa_pliku, std::ios::out|std::ios::app);
    bool tab_QS[n]; //jesli false -> jest w Q, jesli true -> jest w S
    int tab_koszty_dojscia[n]; //tablica zawierajaca koszty przejscia
    int tab_poprzedniki[n]; //tablica poprzednikow
    int x, y, z, swa; //zmienne pomocnicza
    int stos[n];
    int kopiec[n];
    int wierzcholki_kopca[n];
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


        while(true)                   // W petli idziemy w dó³ kopca, przywracajac go
        {
            l_dziecko  = 2*rodzic + 1; // Pozycja lewego potomka
            p_dziecko = l_dziecko + 1; // Pozycja prawego potomka
            if(l_dziecko >= dlugosc_kopca)
                break;     // Konczymy, jeœli lewy potomek poza kopcem
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
            rodzic = min_idx;              // i przechodzimy na poziom ni¿szy kopca
        }


        tab_QS[x]=true; //przenosimy wierzcholek z q do s

        for(int i=0; i<n;i++) //iteracja po wszystkich sasiadach wierzcholka u
        {
            if(_macierz[x][i]._numer==1)
            {
            y=i;  //numer wierzcholka sasiada -> y
            if(tab_QS[y]==false)    //jesli sasiad jest w q
            {
                z=_macierz[x][y]._waga;
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
 }

void graf_macierz::test_efektywnosci(int ilosc_wierzcholkow, int gestosc_grafu)
{
    std::fstream testy;
    testy.open( "testy_efektywnosci_macierze.txt", std::ios::out|std::ios::app);
    std::chrono::high_resolution_clock::time_point t1;
    std::chrono::high_resolution_clock::time_point t2;
    int liczba_krawedzi_docelowo=0;
    int a,b,waga;
    srand(time(NULL));
    ///////////////////////////////////////////////
    //wczytanie okreslonego grafu z pliku
    graf_macierz temp(ilosc_wierzcholkow, 0);
    liczba_krawedzi_docelowo=((gestosc_grafu)*ilosc_wierzcholkow*(ilosc_wierzcholkow-1))/200;

    if(gestosc_grafu==100)
    {
        for(int i=0;i<ilosc_wierzcholkow;i++)
        {
            for(int j=0;j<ilosc_wierzcholkow;j++)
            {
                if(i!=j&&temp.czy_krawedz(i,j)==false)
                {
                    waga=rand()%1000;
                    temp.dodaj_krawedz(i,j,waga);
                }
            }
        }
    }

    else
        for(int i=0;i<liczba_krawedzi_docelowo;i++)
        {
            do
            {
                a=rand()%ilosc_wierzcholkow;
            }
            while(temp.ilosc_sasiadow(a)==n-1);
            do
            {
                b=rand()%ilosc_wierzcholkow;
            }
            while(b==a||temp.czy_krawedz(a,b));

            waga=rand()%1000; //ustalamy wagi tylko do 1000
            temp.dodaj_krawedz(a, b, waga);
        }
    /////////////////////////////////////////////
    t1 = std::chrono::high_resolution_clock::now();
    temp.dijkstra("wyniki_macierze.txt"); //dijkstra dla okreslonego wczesniej grafu
    t2 = std::chrono::high_resolution_clock::now();

    testy << n<< ";"<<gestosc_grafu<< ";"<<std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<std::endl;

    testy.close();
}


#endif
