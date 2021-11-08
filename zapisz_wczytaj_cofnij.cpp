#include "zapisz_wczytaj_cofnij.h"
#include <iostream>
#include <fstream>

using namespace std;

Lista_ruchow* tworz_liste_ruchow(int **pl, int czyj_ruch)
{
    Lista_ruchow *g=0;
    Lista_ruchow *p=0;

    for(int x=0; x<8; x++)
    {
        for(int y=0; y<8; y++)
        {
            if(g==0)
            {
                g=new Lista_ruchow;
                p=g;
            }
            else
            {
                p->n=new Lista_ruchow;
                p=p->n;
            }

            p->war = pl[x][y];
            p->ilosc=-32;
            p->czyj_ruch=-32;
        }
    }
    p->n=0;
    p->ilosc=-1;
    p->czyj_ruch=czyj_ruch;


    return g;
}
Lista_ruchow* dodaj_do_listy_ruchow(int **pl, int czyj_ruch, Lista_ruchow *g)
{
    int ilosc_pom;
    Lista_ruchow *p=0;
    p=g;


    do
    {
        p=p->n;
    }while(p->n!=0);

    ilosc_pom=((p->ilosc)+1);

    for(int x=0; x<8; x++)
    {
        for(int y=0; y<8; y++)
        {
           p->n=new Lista_ruchow;
           p=p->n;

           p->war = pl[x][y];
           p->ilosc=-32;
           p->czyj_ruch=-32;
        }
    }
    p->n=0;
    p->ilosc=ilosc_pom;
    p->czyj_ruch=czyj_ruch;

    return g;
}
void cofnij_ruch(int **&pl, int &czyj_ruch, Lista_ruchow *&g)
{
    int ilosc_pom;
    Lista_ruchow *p=0;
    Lista_ruchow *p2=0;
    int pom=0;
    p=g;

    do
    {
        p=p->n;
    }while(p->n!=0);

    ilosc_pom=p->ilosc;
    if(ilosc_pom==-1)
    {
        cout<<"Wykonujesz pierwszy ruch w rozgrywce"<<endl<<"Brak ruchow do cofniecia"<<endl<<endl;
        return;
    }
    p=g;

    if(ilosc_pom!=0)
    {
        for(int x=0; x<((ilosc_pom*64)-1); x++)
        {
          p=p->n;
        }
    }

    for(int x=0; x<8; x++)
    {
        for(int y=0; y<8; y++)
        {
            if(ilosc_pom!=0 || x!=0||y!=0) p=p->n;
            pl[x][y]=p->war;
            czyj_ruch = p->czyj_ruch;

        }
    }
    p2=p->n;
    p->n=0;

    for(int x=0; x<64; x++)
    {
        Lista_ruchow *pom2=p2;
        p2=p2->n;
        delete pom2;
    }


    return;
}
void zapisz(Lista_ruchow *g, string u, string u1)
{
    string nazwa;
    char nadpis='0';
    Lista_ruchow *p=0;
    p=g;

    cout<<"Podaj nazwe pliku do ktorego ma zostac zapisany stan gry"<<endl;
    cin>>nazwa;
    nazwa="zap_"+nazwa+".txt";
    cout<<endl;

    ifstream p1;
    p1.open(nazwa.c_str());

    while(p1.is_open() && nadpis!='t')
    {
        cout<<"Uwaga plik zapisu o podanej nazwie juz istnieje."<<endl<<"Czy chcesz go nadpisac? (spowoduje to utrate wczesniejszego stanu)"<<endl<<"(t/n)?"<<endl;
        cin>>nadpis;
        while(!(nadpis=='t' || nadpis=='n'))
        {
            cout<<"Podaj poprawna wartosc"<<endl;
            cout<<"(t/n)?"<<endl;
            cin>>nadpis;
        }
        cout<<endl;

        if(nadpis=='n')
        {
            cout<<"Podaj nazwe pliku do ktorego ma zostac zapisany stan gry"<<endl;
            cin>>nazwa;
            nazwa="zap_"+nazwa+".txt";
            p1.close();
            p1.clear();
            ifstream p1;
            p1.open(nazwa.c_str());
        }
    }

    p1.close();
    p1.clear();
    ofstream p2;
    p2.open(nazwa.c_str());

    p2<<u<<endl;
    p2<<u1<<endl;
    while(p!=0)
    {
        p2<<p->war<<" "<<p->ilosc<<" "<<p->czyj_ruch;
        p=p->n;
        if(p!=0) p2<<endl;
    }

    if(nadpis!='t')
    {
        ofstream p3;
        p3.open("zapisy.txt", ios::app);
        p3<<nazwa<<" ";
        p3.close();
        p3.clear();
    }

    p2.close();
    p2.clear();
    nadpis='0';
    return;
}


