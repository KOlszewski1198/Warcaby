#include <statystyki_ranking.h>
#include <fstream>
#include <iostream>

using namespace std;

void wypisz_statystyki(string u)
{
    system( "cls" );
    ///zmienna plikowa
    ifstream plik;
    ///Zmienna do przepisywania z pliku
    double pom;
    ///Zmienna do przepisywania z pliku w konkretnych przypadkach
    double pom2;
    ///zmienna plikowa
    string nazwa_pliku;
    nazwa_pliku=u+".txt";

    plik.open(nazwa_pliku.c_str());

    cout<<"Statystyki gracza: "<<u<<endl<<endl;

    if(!plik.is_open())
    {
        cout<<"Brak statystyk"<<endl;
        cout<<"Gracz nie bral udzialu w zadnej grze lub nie istnieje"<<endl<<endl;
        plik.close();
        plik.clear();
        return;
    }
    else
    {
        plik>>pom;
        cout<<"Gry rozpoczete: "<<pom<<endl;

        plik>>pom;
        cout<<"Gry wygrane: "<<pom<<endl;

        plik>>pom2;
        cout<<"Gry przegrane: "<<pom2<<endl;

        cout<<"Procent zwyciestw: "<<(pom/(pom+pom2))*100<<"%"<<endl;

        plik>>pom;
        cout<<"Gry bialymi: "<<pom<<endl;

        plik>>pom;
        cout<<"Gry czarnymi: "<<pom<<endl;

        plik>>pom;
        cout<<"Wykononych ruchow: "<<pom<<endl<<endl;
    }
    plik.close();
    plik.clear();

    return;
}
void dodaj_do_statystyk(string u, int x, double inf)
{
    ///Wartosci poszczegolnych statystyk
    double pom1=0,pom2=0,pom3=0,pom4=0,pom5=0,pom6=0;
    string nazwa_pliku;
    ///Zmienna kryterium ststystyki
    int licz=1;

    nazwa_pliku=u+".txt";

    ifstream plik;
    plik.open(nazwa_pliku.c_str());

    if(!plik.eof())
    {
        plik>>pom1;
        if(licz==x)
        {
            pom1=pom1+inf;
        }
        licz++;

        plik>>pom2;
        if(licz==x)
        {
            pom2=pom2+inf;
        }
        licz++;

        plik>>pom3;
        if(licz==x)
        {
            pom3=pom3+inf;
        }
        licz++;

        plik>>pom4;
        if(licz==x)
        {
            pom4=pom4+inf;
        }
        licz++;

        plik>>pom5;
        if(licz==x)
        {
            pom5=pom5+inf;
        }
        licz++;

        plik>>pom6;
        if(licz==x)
        {
            pom6=pom6+inf;
        }
    }

    plik.close();
    plik.clear();

    u=u+".txt";

    ofstream plik2;
    plik2.open(nazwa_pliku.c_str());

    plik2<<pom1<<" ";
    plik2<<pom2<<" ";
    plik2<<pom3<<" ";
    plik2<<pom4<<" ";
    plik2<<pom5<<" ";
    plik2<<pom6<<" ";

    plik.close();
    plik.clear();
    return;
}

void wypisz_ranking(int x)
{
    system( "cls" );

    switch(x)
    {
        case 1: {
                  cout<<"Najwiecej rozpoczetych gier"<<endl;
                } break;
        case 2: {
                  cout<<"Najwiecej wygranych gier"<<endl;
                } break;
        case 0: {
                  cout<<"Najwiecej procent wygranych gier"<<endl;
                } break;
        case 6: {
                  cout<<"Najwiecej wykonanych ruchow"<<endl;
                } break;
    }


    ///Zmiene do przepisywania z pliku
    int pom=0, pom_3, pom_4;
    ///Zmiena do przepisywania z pliku
    string pom_2;
    ifstream plik;
    plik.open("uzytkownicy.txt");

    if(!plik.is_open())
    {
        cout<<"Bład otwarcia pliku uzytkowników"<<endl;
        return;
    }

    while(!plik.eof())
    {
        plik>>pom_2;
        pom++;
    }
    plik.close();
    plik.clear();

    Ranking T[pom];
    pom=0;
    plik.open("uzytkownicy.txt");
    while(!plik.eof())
    {
        plik>>T[pom].u;
        pom++;
    }
    plik.close();
    plik.clear();


    if(x!=0)
    {
        for(int i=0; i<pom; i++)
        {
            pom_2=T[i].u;
            pom_2=pom_2+".txt";
            plik.open(pom_2.c_str());

            if(plik.is_open())
            {
                for(int j=1; j<=x; j++)
                {
                    plik>>pom_3;
                }

                T[i].war=pom_3;
            }
            else
            {
                T[i].war=0;
            }

            plik.close();
            plik.clear();
        }
    }
    if(x==0)
    {
        for(int i=0; i<pom; i++)
        {
            pom_2=T[i].u;
            pom_2=pom_2+".txt";
            plik.open(pom_2.c_str());

            if(plik.is_open())
            {
                for(int j=1; j<=2; j++)
                {
                    if(j==1) plik>>pom_4;
                    if(j==2) plik>>pom_3;
                }

                if(pom_4==0) T[i].war=0;
                else T[i].war=((pom_3)/(pom_4))*100;
            }
            else
            {
                T[i].war=0;
            }
            plik.close();
            plik.clear();
        }
    }

    sortuj_tab(T, pom);

    cout<<endl<<"nr | nazwa uzywkownika | wartoschgjghjghjhgjghjgh"<<endl;
    cout<<"--------------------------------"<<endl;

    for(int i=0; i<pom; i++)
    {
        if(T[i].war!=0)
        {
            if((i+1)!=10) cout<<(i+1)<<". | ";
            if((i+1)==10) cout<<(i+1)<<".| ";

            cout.width( 11 );
            cout<<T[i].u<<"       |";
            cout.width( 4 );
            cout<<T[i].war<<endl;
        }
        else
        {
            if((i+1)!=10) cout<<(i+1)<<". | ";
            if((i+1)==10) cout<<(i+1)<<".| ";

            cout.width( 16 );
            cout<<"----------------- | -----"<<endl;
        }
    }

    for(int i=0; i<(10-pom); i++)
    {
        if((i+1)!=10) cout<<(i+1)<<". | ";
        if((i+1)==10) cout<<(i+1)<<".| ";

        cout.width( 16 );
        cout<<"----------------- | -----"<<endl;
    }

    do
    {
        cout<<endl<<"Nacisnij 'p', aby powrocic do menu"<<endl;
        cin>>pom_2;
    }while(pom_2!="p");

    return;
}
void sortuj_tab(Ranking T[], int roz)
{
    ///Struktura zawierajaca pobrane z pliku informacje do rankingu
    Ranking pom;

    for(int i=0;i<roz;i++)
    {
        for(int j=1;j<roz-i;j++)
        {
            if(T[j-1].war<T[j].war)
            {
                pom.u=T[j-1].u;
                pom.war=T[j-1].war;
                T[j-1].u=T[j].u;
                T[j-1].war=T[j].war;
                T[j].u=pom.u;
                T[j].war=pom.war;
            }
        }
    }
}
