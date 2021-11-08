#include <interfejs.h>
#include <iostream>
#include <fstream>
#include "plansza.h"


using namespace std;
/// Globalna nazwa pierwszego uzytkownika ("0" - jesli niezalogowany)
string uzytkownik="0";
/// Globalna nazwa drugiego uzytkownika ("0" - jesli niezalogowany)
string uzytkownik2="0";
/////Zmienna wyboru kryterium rankingu
char pom;

///Okresla istnienie zapisanych gier
int pom_zapis=1;
/// Nazwa wczytywanego zpisu
string pom2;
///Tablica przechowujaca dane i pionkach na planszy
int **plansza=0;
///Okresla ktory raz zostaje rozpoczeta nowa gra
int time;

int czyj_ruch;

void menu()
{
    system( "cls" );
    ///Zmienna wyboru dzialania
    int x;

    cout<<"Warcaby"<<endl<<endl;

    if(uzytkownik!="0")
    {
        cout<<"Zalogowano jako: "<<uzytkownik<<endl<<endl;
    }
    if(uzytkownik=="0")
    {
        cout<<"Zaloguj sie, aby zaczac gre"<<endl;
        uzytkownik=zaloguj();
    }

    cout<<"Wybierz dzialanie"<<endl;
    cout<<"1. Nowa gra"<<endl;
    cout<<"2. Wczytaj gre"<<endl;
    cout<<"3. Statystyki graczy"<<endl;
    cout<<"4. Ranking uzytkownikow"<<endl;
    cout<<"5. Wyloguj"<<endl;
    cout<<"6. Zakoncz gre"<<endl;
    cin>>x;
    cout<<endl<<endl;

    switch(x)
    {
        case 1: {
                    interfejs_nowa_gra();
                } break;

        case 2: {
                    interfejs_wczytaj_gre();
                }; break;

        case 3: {
                    interfejs_statystyki();
                    menu();
                 }break;

         case 4:{
                    interfejs_ranking();
                    menu();
                }break;

        case 5: {
                    uzytkownik="0";
                    menu();
                } break;

        case 6: exit( 0 );; break;

        default: {cout<<"Bledna wartosc"<<endl;
                menu();}
    }
    return;
}

void interfejs_nowa_gra()
{
    system( "cls" );
    ///Zmienna wyboru dzialania
    int x;

    cout<<"Wybierz dzialanie"<<endl;
    cout<<"1. Tryb dla 2 graczy"<<endl;
    cout<<"2. Powrot"<<endl;
    cin>>x;
    cout<<endl<<endl;

    switch(x)
    {
        case 1: {
                system( "cls" );
                plansza = tworz_plansze();                           //tworzy plansze

                do{                                                 //logowanie 2. gracza
                    cout<<"Gracz 1: "<<uzytkownik<<endl<<"Logowanie na konto 2. gracza"<<endl;
                    uzytkownik2=zaloguj();
                    system( "cls" );
                    if(uzytkownik==uzytkownik2) cout<<"Blad."<<endl<<"Nazwy zalogowanych uzytkownikow dubluja sie"<<endl<<endl;
                }while(uzytkownik==uzytkownik2);

                time=0;
                Lista_ruchow *g;
                gra_2_graczy(uzytkownik, uzytkownik2, plansza, time, 0, 0,g );       //rozpoczyna gre
                menu();
                break; }

        case 2: {
                break; }

        default:{
                cout<<"Bledna wartosc"<<endl;
                interfejs_nowa_gra(); }
    }
    menu();

    return;
}
void interfejs_statystyki()
{
    system( "cls" );
    cout<<"Wybierz uzytkownika z listy"<<endl;
    wypisz_uzytkownikow();
    cin>>uzytkownik2;
    wypisz_statystyki(uzytkownik2);
    uzytkownik2="0";
    do
    {
        cout<<"Nacisnij 'p', aby powrocic do menu"<<endl;
        cout<<"Nacisnij 'n', aby wczytac statystyki kolejnego uzytkownika"<<endl;
        cin>>pom;
    }while(pom!='n' && pom!='p');

    if(pom=='n')
    {
        interfejs_statystyki();
        return;
    }
    if(pom=='p')
    {
        menu();
        return;
    }
}
void interfejs_ranking()
{
    int pom;

    system( "cls" );
    cout<<"Wybierz rodzaj statystyk"<<endl<<endl;
    cout<<"1. Najwiecej rozpoczetych gier"<<endl;
    cout<<"2. Najwiecej wygranych gier"<<endl;
    cout<<"3. Najwiecej procent wygranych gier"<<endl;
    cout<<"4. Najwiecej wykonanych ruchow"<<endl<<endl;

    cin>>pom;

    switch(pom)
    {
        case 1: {
                    wypisz_ranking(1);
                } break;
        case 2: {
                    wypisz_ranking(2);
                } break;
        case 3: {
                     wypisz_ranking(0);
                } break;
        case 4: {
                    wypisz_ranking(6);
                } break;
    }
    return;
}
void interfejs_wczytaj_gre()
{
    system( "cls" );
    wypisz_zapisane();
    if(pom_zapis==0)
    {
        pom_zapis=1;
        menu();
        return;
    }
    cout<<"Wybierz zapis do wczytania"<<endl;
    cin>>pom2;
    while(!sprawdz_czy_istnieje_zapis(pom2))
    {
        cout<<"Podaj wlasciwa nazwe zapisu"<<endl;
        cin>>pom2;
    }

    Lista_ruchow *g=0;
    plansza=przepisz_z_pliku_na_plansze(pom2, czyj_ruch, uzytkownik, uzytkownik2, g);
    gra_2_graczy(uzytkownik, uzytkownik2, plansza, 1, 1, czyj_ruch, g);

    menu();
    return;
}


void wypisz_uzytkownikow()
{
    ///Nazwa wypisywanego uzytkownika
    string  uzytkownik;
    ///Zmienna do otwarcia pliku "uzytkownicy.txt"
    ifstream plik;
    plik.open("uzytkownicy.txt");

    if(!plik.is_open())
    {
        plik.close();
        plik.clear();

        ofstream plik2;
        plik2.open("uzytkownicy.txt");
        plik2.close();
        plik2.clear();
        cout<<"Lista uzytkownikow jest pusta"<<endl;;
        return;
    }

    if(plik.eof()) cout<<"Lista uzytkownikow jest pusta"<<endl;
    else cout<<"Lista uzytkownikow:"<<endl;

    while(!plik.eof())
    {
        plik>>uzytkownik;
        cout<<uzytkownik<<endl;
    }
    cout<<endl;
    plik.close();
    plik.clear();
    return;
}
bool sprawdz_czy_istnieje(string nazwa)
{
    ///Przechowuje nazwe uzytkownika wczytana z pliku
    string pom;
    ///Zmienna do otwarcia pliku "uzytkownicy.txt"
    ifstream plik;
    plik.open("uzytkownicy.txt");

    while(!plik.eof())
    {
        plik>>pom;
        if(pom==nazwa) return true;
    }

    plik.close();
    plik.clear();

    //////Zmienna do ponownego otwarcia pliku "uzytkownicy.txt"
    ofstream plik2;
    plik2.open("uzytkownicy.txt", ios::app);
    plik2<<endl<<nazwa;
    plik2.close();
    plik2.clear();
    return false;
}
string zaloguj()
{

    ///Nazwa uzytkownika do zalogowania
    string nazwa;

    wypisz_uzytkownikow();

    cout<<"Podaj nazwe gracza na ktorego konto chcesz sie zalogowac lub uwtworz nowe podajac nowa nazwe"<<endl;

    do{
        cin>>nazwa;
        system( "cls" );
        if(nazwa=="0") cout<<"0 nie moze byc nazwa uzytkownika"<<endl<<"Podaj inna nazwe"<<endl;
    }while(nazwa=="0");

    if(sprawdz_czy_istnieje(nazwa))
        cout<<"Zalogowano jako: "<<nazwa<<endl;
    else
        cout<<"Utworzono uzytkownika: "<<nazwa<<endl;

    return nazwa;
}
void wypisz_zapisane()
{
    ///Zmienna do otwarcia pliku "zapisy.txt"
    ifstream p1;
    ///Zmienna do wczytywania z pliku
    string pom;
    p1.open("zapisy.txt");
    if(!p1.is_open())
    {
        cout<<"Brak zapisanych stanow gry"<<endl;
        cout<<"Nacisnij dowolny przycisk"<<endl;
        cin>>pom;
        pom_zapis=0 ;
        return;
    }

    cout<<"Lista zapisanych stanow gry"<<endl;
    do
    {
        p1>>pom;
        if(!p1.eof()) cout<<pom<<endl;
    }while(!p1.eof());

    return;
}
bool sprawdz_czy_istnieje_zapis(string nazwa)
{
    ///Zmienna do wczytywania z pliku
    string pom;
    ///Zmienna do otwarcia pliku "zapisy.txt"
    ifstream plik;
    plik.open("zapisy.txt");

    while(!plik.eof())
    {
        plik>>pom;
        if(pom==nazwa)
        {
           plik.close();
           plik.clear();
           return true;
        }
    }

    plik.close();
    plik.clear();
    return false;
}

