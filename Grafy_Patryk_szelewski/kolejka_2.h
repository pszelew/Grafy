#ifndef KOLEJKA_2_H_INCLUDED
#define KOLEJKA_2_H_INCLUDED

void heapify(typ *tablica, int pierwszy, int ostatni, int node, bool rosnaco)
{
    int maximum=node;
    int lewy=2*node-pierwszy+1;
    int prawy=2*node-pierwszy+2;
    if(rosnaco) //jesli tworzymy kopiec maksymalny
    {
        if(lewy<=ostatni&&tablica[lewy]>tablica[maximum])
        {
            maximum=lewy;
        }
        if(prawy<=ostatni&&tablica[prawy]>tablica[maximum])
        {
            maximum=prawy;
        }

        if(node!=maximum)
        {
            zamien_elementy(tablica, maximum, node);
            heapify(tablica, pierwszy, ostatni, maximum, rosnaco);
        }
    }
    else //jesli tworzymy kopiec minimalny
    {
        if(lewy<=ostatni&&tablica[lewy]<tablica[maximum])
        {
            maximum=lewy;
        }
        if(prawy<=ostatni&&tablica[prawy]<tablica[maximum])
        {
            maximum=prawy;
        }

        if(node!=maximum)
        {
            zamien_elementy(tablica, maximum, node);
            heapify(tablica, pierwszy, ostatni, maximum, rosnaco);
        }
    }
}
#endif // KOLEJKA_2_H_INCLUDED
