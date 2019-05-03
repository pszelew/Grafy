#ifndef LISTA_H
#define LISTA_H
#include <iostream>
#include <cstdlib>
#include <string>

template<class typ> class element;
template<class typ> class lista;


template <class typ>
class lista
{
private:
	element<typ> *header; // wskaznik na pierwszy element listy
	element<typ> *tail; // wskaznik na ostatni element listy
public:
    element<typ> * glowa_listy(){return header;};
    element<typ> * ogon_listy(){return tail;};
	lista(){header=NULL; tail=NULL;}; // konstruktor listy
	~lista(){}; // destruktor listy
	void dodaj(typ elem);	// dodaje element na koniec listy
	void usun(int pozycja); // usuwa n-ty element listy
	typ zwroc_wartosc(int pozycja); // zwraca n-ty element listy
	void wyczysc(); // usuwa wszystkie elementy listy
	bool czy_pusta();
};


template <class typ>
class element
{
public:
	typ rekord;
	element *nastepny;

	element(typ elem)
	{
		rekord = elem;
		nastepny = NULL;
	}
};



template <class typ>
void lista<typ>::dodaj(typ elem)
{
    element<typ> *temp = new element<typ>(elem);
    if(header==NULL) //jesli lista jest pusta
    {
        header = tail = temp;
    }
    else // jesli na liscie juz cos jest
    {
        tail->nastepny=temp;
        tail=temp;
    }
}

template <class typ>
typ lista<typ>::zwroc_wartosc(int pozycja)
{   std::string wyjatek;
    if(header==NULL) //jesli lista jest pusta
    {
        wyjatek = "Brak polaczenia";
        throw wyjatek;
    }
    else // jesli na liscie juz cos jest
    {
        int i = 0;
        element<typ> *temp=header;
        while(i<pozycja&&temp->nastepny!=NULL)
        {
            temp=temp->nastepny;
            i++;
        }
        if(i==pozycja)
            return(temp->rekord);
        else
            {
                wyjatek = "Brak wierzcholka";
                throw wyjatek;
            }
    }
}


template <class typ>
void lista<typ>::usun(int pozycja)
{
    std::string wyjatek;
    if(header==NULL) //jesli lista jest pusta
    {
        wyjatek = "Brak usuwanego elementu";
        throw wyjatek;
    }
    else // jesli na liscie juz cos jest
    {
        int i=0;
        int j=0;
        element<typ> *temp=header;
        element<typ> *temp2=NULL;
        while(i<pozycja&&temp->nastepny!=NULL)
        {
            temp2=temp;
            temp=temp->nastepny;
            i++;
            j++;
        }
        if(i==0)
        {
            header=header->nastepny;
            delete(temp);
        }
        else if(i==pozycja)
        {
            temp2->nastepny=temp->nastepny;
            delete(temp);
        }
        else
        {
            wyjatek="Brak usuwanego elementu";
            throw wyjatek;
        }
    }
}

template <class typ>
void lista<typ>::wyczysc()
{

        element<typ> *temp=header;

        while(temp!=NULL)
        {
            header=header->nastepny;
            delete(temp);
            temp=header;
        }

}

template <class typ>
bool lista<typ>::czy_pusta()
{
    if(header==NULL)
        return 1;
    return 0;
}

#endif


