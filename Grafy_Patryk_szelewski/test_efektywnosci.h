#ifndef TEST_EFEKTYWNOSCI_H_INCLUDED
#define TEST_EFEKTYWNOSCI_H_INCLUDED

class test_efektywnosci
{
    public:
    template <class typ>
    static void test(int ilosc_wierzcholkow, int gestosc_grafu);
};

template <class typ>
void test_efektywnosci::test(int ilosc_wierzcholkow, int gestosc_grafu)
{
    std::fstream testy;
    testy.open( "testy_efektywnosci.txt", std::ios::out|std::ios::app);
    std::chrono::high_resolution_clock::time_point t1;
    std::chrono::high_resolution_clock::time_point t2;
    long long czas=0;
    long long liczba_krawedzi_docelowo=0;
    int a,b,c,d,waga;
    lista<int> wierzcholki_poczatkowe;
    lista<int> wierzcholki_koncowe [ilosc_wierzcholkow];
    int dlugosc_listy_poczatkowych=0;
    int dlugosc_listy_koncowych [ilosc_wierzcholkow];
    typ* temp;
    srand(time(NULL));

    ///////////////////////////////////////////////
    //wczytanie okreslonego grafu z pliku

    liczba_krawedzi_docelowo=((gestosc_grafu)*ilosc_wierzcholkow*(ilosc_wierzcholkow-1))/200;

    for(int g=0;g<100;g++)
    {
        temp=new typ(ilosc_wierzcholkow, 0); //nowy graf
        for(int i=0;i<ilosc_wierzcholkow;i++)
        {
            dlugosc_listy_koncowych[i]=0;
        }
        //wczytujemy liste wierzcholkow poczatkowych
        for(int i=0;i<ilosc_wierzcholkow;i++)
        {
            wierzcholki_poczatkowe.dodaj(i);
            dlugosc_listy_poczatkowych++;
        }
        //wczytujemy liste wierzcholkow koncowych
        for(int i=0;i<ilosc_wierzcholkow;i++)
        {
            for(int j=0;j<ilosc_wierzcholkow;j++)
            {
                if(i!=j)
                {
                    wierzcholki_koncowe[i].dodaj(j);
                    dlugosc_listy_koncowych[i]++;
                }
            }
        }


        for(int i=0;i<liczba_krawedzi_docelowo;i++)
        {
            a=rand()%dlugosc_listy_poczatkowych;
            c=wierzcholki_poczatkowe.zwroc_wartosc(a);
            b=rand()%dlugosc_listy_koncowych[c];
            d=wierzcholki_koncowe[c].zwroc_wartosc(b);
            waga=rand()%1000; //ustalamy wagi tylko do 1000
            temp->dodaj_krawedz(c, d, waga);

            //ustawiamy listy, tak jak powinny byc

            wierzcholki_koncowe[c].usun(b);
            dlugosc_listy_koncowych[c]--;
            if(wierzcholki_koncowe[c].glowa_listy()==NULL)
            {
                wierzcholki_poczatkowe.usun(a);
                dlugosc_listy_poczatkowych--;
            }
        }

        /////////////////////////////////////////////
        std::string tmp;
        sprintf((char*)tmp.c_str(), "%d", gestosc_grafu);
        std::string str = tmp.c_str();
        std::string nazwa_pliku="wyniki_listy" + str + ".txt";
        t1 = std::chrono::high_resolution_clock::now();
        temp->dijkstra(nazwa_pliku); //dijkstra dla okreslonego wczesniej grafu
        t2 = std::chrono::high_resolution_clock::now();
        czas+=std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        //konczenie petli
        wierzcholki_poczatkowe.wyczysc();
        for(int i=0;i<ilosc_wierzcholkow;i++)
          wierzcholki_koncowe[i].wyczysc();
        dlugosc_listy_poczatkowych=0;
        delete temp;
    }

    testy << ilosc_wierzcholkow<< ";"<<gestosc_grafu<< ";"<<czas<<std::endl;
    testy.close();
}

#endif // TEST_EFEKTYWNOSCI_H_INCLUDED
