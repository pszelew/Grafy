#ifndef KOLEJKA_H_INCLUDED
#define KOLEJKA_H_INCLUDED
struct element_kopca
{
    int element=0;
    int priorytet=0;
};

class kolejka_priorytetowa
{
private:
    element_kopca * kopiec;
    int n; //ilosc elementow kopca
public:
    kolejka_priorytetowa(int max);
    ~kolejka_priorytetowa();
    int pierwszy_element();
    int pierwszy_priorytet();
    void set_pierwszy(element_kopca x){kopiec[0]=x;};
    void set_ostatni(element_kopca x){kopiec[n]=x;};
    void dodaj(int elem, int prio);
    void usun();
    bool pusta();
};

kolejka_priorytetowa::kolejka_priorytetowa(int max)
{
    kopiec = new element_kopca[max]; //tablica dynamiczna stanowiaca nasza kolejke priorytetowa
    n=0; // tworzymy pusty kopiec
}

kolejka_priorytetowa::~kolejka_priorytetowa()
{
    delete [] kopiec;
}

int kolejka_priorytetowa::pierwszy_element()
{
    return kopiec[0].element;
}
int kolejka_priorytetowa::pierwszy_priorytet()
{
    return kopiec[0].priorytet;
}


void kolejka_priorytetowa::dodaj(int elem, int prio) //operacja dodania elementu do kopca wedlug priorytetu
{
    int i=n;
    int j=(i-1)/2;
    n++;
    while(i > 0 && kopiec[j].priorytet < prio)
    {
        kopiec[i]=kopiec[j]; //zamieniamy elementy miejscamu
        i=j;
        j=(i-1)/2;
    }
    kopiec[i].priorytet = prio;
    kopiec[i].element = elem;
}

void kolejka_priorytetowa::usun() //usuwap pierwszy elementy kolejki -> z gory
{
    int i=0;
    int j=1;
    int prio;
    int elem;

    if(n>0)
    {
        n--;
        prio=kopiec[n].priorytet;
        elem=kopiec[n].element;
        while(j<n)
        {
            if(j+1<n && kopiec[j+1].priorytet > kopiec[j].priorytet)
                j++;
            if(prio >= kopiec[j].priorytet)
                break;
            kopiec[i] = kopiec[j];
            i = j;
            j = 2*j+1;
        }
        kopiec[i].priorytet = prio;
        kopiec[i].element = elem;
    }
}

bool kolejka_priorytetowa::pusta()
{
    if(n)
        return false;
    return true;
}


#endif // KOLEJKA_H_INCLUDED
