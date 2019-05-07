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
    int wierzcholkow[]={10, 50 , 100, 500, 1000};
    int gestosci[]={25, 50, 75, 100};
    float percentage=0;
    int opcja, opcja_2;
    graf_lista *temp_lista;
    graf_macierz *temp_macierz;
    std::string nazwa;
    remove("testy_efektywnosci_listy.txt");
    remove("testy_efektywnosci_macierze.txt");
    remove("wyniki_listy25.txt");
    remove("wyniki_macierze25.txt");
    remove("wyniki_listy50.txt");
    remove("wyniki_macierze50.txt");
    remove("wyniki_listy75.txt");
    remove("wyniki_macierze75.txt");
    remove("wyniki_listy100.txt");
    remove("wyniki_macierze100.txt");
    remove("wyniki.txt");
    std::fstream dane;
    dane.open( "dane.txt", std::ios::in);

    std::cout<<"Start programu:"<<std::endl;
    std::cout<<"0->wczytaj dane z pliku"<<std::endl;
    std::cout<<"1->test wydajnosci ok.45min"<<std::endl;
    std::cin >> opcja;
    if(std::cin.fail())
        return -1;
    switch(opcja)
    {
        case 0:
            std::cout<<"Podaj nazwe pliku do wczytania: ";
            std::cin>> nazwa;
            if(std::cin.fail())
                return -1;
            std::cout<<"Podaj sposob zapisu grafu: "<<std::endl;
            std::cout<<"0->listy sasiedztwa"<<std::endl;
            std::cout<<"1->macierz sasiedztwa"<<std::endl;
            std::cin >> opcja_2;
            if(std::cin.fail())
                return -1;
            dane>> m>>n>>start; //krawedzie, wierzcholki, wierzcholek startowy
            if(std::cin.fail())
                return -1;
            switch(opcja_2)
            {
                case 0:
                    temp_lista=new graf_lista(n, start);
                    for(int i=0; i<m;i++) //wczytanie grafow
                    {
                        dane >> a >> b >> waga;
                        temp_lista->dodaj_krawedz(a, b, waga);
                    }
                    temp_lista->dijkstra("wyniki.txt");
                    break;
                default:
                    temp_macierz=new graf_macierz(n, start);
                    for(int i=0; i<m;i++) //wczytanie grafow
                    {
                        dane >> a >> b >> waga;
                        temp_macierz->dodaj_krawedz(a, b, waga);
                    }
                    temp_macierz->dijkstra("wyniki.txt");
            }

            if(opcja_2==0)
                delete temp_lista;
            else
                delete temp_macierz;
            break;
        default:
            for(int i=0;i<5;i++)
                for(int j=0;j<4;j++)
                {
                    std::cout<<percentage<<"% ukonczenia"<<std::endl;
                    test_efektywnosci::test<graf_lista>(wierzcholkow[i],gestosci[j]);
                    percentage+=2.5;
                    std::cout<<percentage<<"% ukonczenia"<<std::endl;
                    test_efektywnosci::test<graf_macierz>(wierzcholkow[i],gestosci[j]);
                    percentage+=2.5;
                }

            std::cout<<"100% ukonczenia"<<std::endl;
    }


    return 0;

}

