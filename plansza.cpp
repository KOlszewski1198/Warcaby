#include <plansza.h>
#include<iostream>
#include<fstream>
#include <stdlib.h>
#include <windows.h>
#include<interfejs.h>

using namespace std;
/// Czy podczas ruchu wystapilo podwojne bicie
bool czy_podwojne=0;
/// Czy podczas ruchu wystapilo cofniecie ruchu
bool cofniecie=0;
/// Czy podczas ruchu wystapil zapis stanu gry
bool zapis=0;
/// Utwarzona lista dostepnymi biciami
Lista_ruchow *lista_ruchow;
/// Czy w tym ruchu ma nastapic cofniecie ruchu
bool cofnij=0;
/// Zmienna przechowujaca informacje o tym ktorego gracza jest obecnie ruch
int x;

void gra_2_graczy(string u1, string u2, int **pl, int time, int wczytanie, int czyj_ruch, Lista_ruchow *g)
{
    ///Zmienna do zakonczenia dzialania funkcji
    int pom;
    if(wczytanie==0) czyj_ruch=0;
    x=czyj_ruch;
    lista_ruchow=g;

    system( "cls" );
    if(time==0)
    {
        cout<<"Rozpoczeto gre dla 2 graczy"<<endl<<endl;

        dodaj_do_statystyk(u1, 1, 1);//dodaje graczą rozpoczętą partię
        dodaj_do_statystyk(u2, 1, 1);

        dodaj_do_statystyk(u1, 4, 1);//dodaje graczą gry białymi oraz czarnymi
        dodaj_do_statystyk(u2, 5, 1);

        lista_ruchow=tworz_liste_ruchow(pl, czyj_ruch);

        time++;
    }

    do
    {
        do{
            cout<<"Gracz 1: "<<u1<<endl;
            cout<<"Gracz 2: "<<u2<<endl;
            pokaz_plansze(u1, u2, pl);

            if(czyj_ruch%2==0)
            {
                cout<<"Ruch gracza: "<<u1<<endl;
                ruch(1, pl);
                if(cofniecie==0 && zapis==0 && wczytanie==0) dodaj_do_statystyk(u1, 6, 1);
            }
            else
            {
                cout<<"Ruch gracza: "<<u2<<endl;
                ruch(2, pl);
                if(cofniecie==0 && zapis==0 && wczytanie==0) dodaj_do_statystyk(u2, 6, 1);
            }

            if(cofniecie==1)
            {
                cofnij_ruch(pl, czyj_ruch, lista_ruchow);
                system( "cls" );
            }
            if(zapis==1)
            {
                zapisz(lista_ruchow, u1,u2);
            }

        }while(cofniecie==1||zapis==1);

        cofniecie=0;
        zapis=0;
        czyj_ruch++;
        lista_ruchow = dodaj_do_listy_ruchow(pl, czyj_ruch, lista_ruchow);
        system( "cls" );

    }while(sprawdz_czy_koniec(pl)==false);

    pokaz_plansze(u1, u2, pl);
    pokaz_zwyciesce(u1 ,u2 , pl);

    cout<<"Naciśnij dowolny klawisz aby powrocic do menu"<<endl;
    cin>>pom;
    return;
}


int **tworz_plansze()
{

    ///Tablica planszy
    int **T=new int*[8];

    for(int x=0; x<8; x++)
    {
        T[x]=new int[8];
    }

    for(int x=0; x<8; x++)
    {
        for(int y=0; y<8; y++)
        {
            if((x+y)%2==1)
            {
                if(x<=2) T[x][y]=2;
                if(x>=5) T[x][y]=1;
                if(x>2 && x<5) T[x][y]=0;
            }
            else
            {
                T[x][y]=0;
            }
        }
    }

    return T;
}
void pokaz_plansze(string u1, string u2, int **pl)
{
    HANDLE hOut;
    hOut = GetStdHandle( STD_OUTPUT_HANDLE );

    system( "cls" );
    cout<<"Indeks pionkow gracza "<<u1<<": 1"<<endl;
    cout<<"Indeks pionkow gracza "<<u2<<": 2"<<endl;

    cout.width( 9 );
    for(int i=0; i<8; i++)
    {
        cout<<char(65+i);
        cout.width(5);
    }
    cout<<endl;

    cout.width( 46 );
    cout<<"----------------------------------------"<<endl;

    for(int x=7; x>=0; x=x-1)
    {
        cout.width( 3 );
        cout<<(8-(7-x));
        cout.width( 3 );
        cout<<"|";

        for(int y=0; y<8; y++)
        {
            cout.width( 3 );
            if((x+y)%2==1)
            {
                SetConsoleTextAttribute( hOut, 0);
            }
            if(pl[(7-x)][y]==1 || pl[(7-x)][y]==3)
            {
                SetConsoleTextAttribute( hOut, 4);
            }
            if(pl[(7-x)][y]==2 || pl[(7-x)][y]==4)
            {
                SetConsoleTextAttribute( hOut, 9);
            }
            cout<<pl[(7-x)][y];
            SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
            if(y!=7){
            cout.width( 2 );
            cout<<"|";
            }
            else
            {
            cout.width( 3 );
            cout<<"|";
            }
        }

        cout.width( 4 );
        cout<<(8-(7-x));

        cout<<endl;
        cout.width( 6 );
        cout<<"|";

        for(int i=0; i<8;i++)
        {
                cout<<"----";
                if(i==7) cout<<"-";
                cout<<"|";
        }
        cout<<endl;

    }

    //cout<<endl;
    cout.width( 9 );
    for(int i=0; i<8; i++)
    {
        cout<<char(65+i);
        cout.width(5);
    }
    cout<<endl;

    return;
}
void ruch(int n, int **pl)
{
    ///Struktura z wartoscia pola z ktorego ma zastac wykonany ruch
    Pole pocz;
    ///Struktura z wartoscia pola na ktore ma zastac wykonany ruch
    Pole kon;

    if(!(obowiazkowe_pierwsze_bicie(n, pl, pocz, kon)))
    {
        if(cofniecie==0) pocz=wczytaj_wsp_pola_pocz_i_sprawdz(n, pl);

        if(pocz.x==-1)//zakończenie gry
        {
            cofniecie=0;
            zapis=0;
            menu();
            return;
        }
        if(pocz.x==-2 || cofnij==1)//cofnięcie ruchu
        {
            cofniecie=1;
            cofnij=0;
            zapis=0;
            return;
        }
        if(pocz.x==-3)//zapisanie gry
        {
            zapis=1;
            cofniecie=0;
            return;
        }

        kon=wczytaj_wsp_pola_kon_i_sprawdz(n, pl, pocz);
    }

    pl[kon.x][kon.y]=pl[pocz.x][pocz.y]; //wykonuje ruch
    pl[pocz.x][pocz.y]=0;  //
    cofniecie=0;
    zapis=0;
    if(sprawdz_czy_staje_sie_dama(n, kon))
    {
        pl[kon.x][kon.y]=(n+2);
    }

    if(abs(kon.x-pocz.x)!=1) //usuniecie przeciwnego pionka podczas bicia//zmiana pionka na dame
    {
        if(abs(kon.x-pocz.x)==2)//gdy bije sie pionkiem
        {
            pl[((pocz.x+kon.x)/2)][((pocz.y+kon.y)/2)]=0;
        }

        if(abs(kon.x-pocz.x)!=2) //gdy bije sie damą
        {
            if(kon.x>pocz.x && kon.y>pocz.y) pl[(kon.x-1)][(kon.y-1)]=0;
            if(kon.x>pocz.x && kon.y<pocz.y) pl[(kon.x-1)][(kon.y+1)]=0;
            if(kon.x<pocz.x && kon.y<pocz.y) pl[(kon.x+1)][(kon.y+1)]=0;
            if(kon.x<pocz.x && kon.y>pocz.y) pl[(kon.x+1)][(kon.y-1)]=0;
        }

        if(sprawdz_czy_staje_sie_dama(n, kon))
        {
            pl[kon.x][kon.y]=n+2;
        }

        obowiazkowe_drugie_bicie(n, pl, kon);//sprawdza czy istnieje i wymusza wykonanie podwojnych bić

    }
   return;
}
bool sprawdz_czy_koniec(int **pl)
{
    ///Okresla istnienie bialych pionkow na planszy
    bool biale=0;
    ///Okresla istnienie czarnych pionkow na planszy
    bool czarne=0;

    for(int x=0; x<8; x++)
    {
        for(int y=0; y<8; y++)
        {
            if((x+y)%2==1 && pl[x][y]!=0)
            {
                if(pl[x][y]%2==0)
                {
                    if(x+1>=0 && x+1<=7 && y+1>=0 && y+1<=7 && pl[x+1][y+1]==0)
                    biale=1;
                    if(x-1>=0 && x-1<=7 && y+1>=0 && y+1<=7 && pl[x-1][y+1]==0)
                    biale=1;
                    if(x+1>=0 && x+1<=7 && y-1>=0 && y-1<=7 && pl[x+1][y-1]==0)
                    biale=1;
                    if(x-1>=0 && x-1<=7 && y-1>=0 && y-1<=7 && pl[x-1][y-1]==0)
                    biale=1;
                }
                if(pl[x][y]%2==1)
                {
                    if(x+1>=0 && x+1<=7 && y+1>=0 && y+1<=7 && pl[x+1][y+1]==0)
                    czarne=1;
                    if(x-1>=0 && x-1<=7 && y+1>=0 && y+1<=7 && pl[x-1][y+1]==0)
                    czarne=1;
                    if(x+1>=0 && x+1<=7 && y-1>=0 && y-1<=7 && pl[x+1][y-1]==0)
                    czarne=1;
                    if(x-1>=0 && x-1<=7 && y-1>=0 && y-1<=7 && pl[x-1][y-1]==0)
                    czarne=1;
                }
            }
        }
    }

    if(biale==1 && czarne==1) return false;
    else return true;
}
void pokaz_zwyciesce(string u1, string u2, int **pl)
{
    for(int x=0; x<8; x++)
    {
        for(int y=0; y<8; y++)
        {
            if((x+y)%2==1 && pl[x][y]!=0)
            {
                if(pl[x][y]%2==0)
                {
                    cout<<"Zwycieza gracz: "<<u1<<endl;
                    dodaj_do_statystyk(u1, 2, 1);//dodaje graczowi 1 wygraną a gracz 2 przegraną
                    dodaj_do_statystyk(u2, 3, 1);
                }

                if(pl[x][y]%2==1)
                {
                    cout<<"Zwycieza gracz: "<<u2<<endl;
                    dodaj_do_statystyk(u2, 2, 1);//dodaje graczowi 2 wygraną a gracz 1 przegraną
                    dodaj_do_statystyk(u1, 3, 1);
                }

            }
        }
    }
}
Pole przelicz_na_wspolrzedne_tablicy(int x,char y)
{
    ///Struktura z wartoscia pola na ktorym zostaje przeprowadzona operacja przeliczenia
    Pole pom;
    pom.x=((9-x)-1);
    pom.y=(y-65);
    return pom;
}
void przelicz_na_wspolrzedne_planszy(Pole pocz, Pole  kon, int &poczx, int &konx, char &poczy, char &kony)
{
    poczx=8-pocz.x;
    konx=8-kon.x;
    poczy=pocz.y+65;
    kony=kon.y+65;
}
Pole wczytaj_wsp_pola_pocz_i_sprawdz(int n, int **pl)
{
    ///Struktura z wartoscia pola z ktorego ma zastac wykonany ruch
     Pole pole;
     pole.x=-1;
     pole.y=-1;
     int x;
     char y;

     cout<<"Podaj wspolrzedne pionka ktorych chcesz wykonac ruch (np.4 A) "<<endl;
     cout<<"Dodatkowo:"<<endl;
     cout<<"11. Zapis"<<endl;
     cout<<"12. Cofnij ruch"<<endl;
     cout<<"13. Wyjscie do menu"<<endl<<endl;;

     cin>>x;

     if(x==13)
     {
         pole.x=-1;
         return pole;
     }
     if(x==12)
     {
         pole.x=-2;
         return pole;
     }
     if(x==11)
     {
         pole.x=-3;
         return pole;
     }

     cin>>y;

     if(!(((x>=1 && x<=8) && (y>='A' && y<='H'))))
     {
         cout<<"Nieprawidlowy ruch"<<endl;

         cout<<"Najpierw podaj wartosc kolumny(1-8) nastepnie litere wiersza(A-H)"<<endl<<endl;;
         cin.clear(); //zabezpieczenie przed podaniem litery zamiast liczby
         cin.sync(); //

         pole=wczytaj_wsp_pola_pocz_i_sprawdz(n, pl);

         return pole;
     }


     pole = przelicz_na_wspolrzedne_tablicy(x,y);


     if(!((pl[pole.x][pole.y])==(n) || (pl[pole.x][pole.y])==(n+2))  ||  pl[pole.x][pole.y]==0 || (pole.x+pole.y)%2!=1)
     {
         cout<<"Bledny ruch"<<endl<<"Wybierz swojego pionka("<<n<<" lub "<<n+2<<")"<<endl;
         pole = wczytaj_wsp_pola_pocz_i_sprawdz(n, pl);
         return pole;
     } //sprawdza czy na polu stoi pionek gracza//

     return pole;
}
Pole wczytaj_wsp_pola_kon_i_sprawdz(int n,int **pl, Pole pocz)
{
    ///Struktura z wartoscia pola na ktore ma zastac wykonany ruch
    Pole pom;
    pom.x=-1;
    pom.y=-1;

    ///Zmienna do wyboru wspolrzednej X pola na ktore ma zostac wykonany ruch
    int x;
    ///Zmienna do wyboru wspolrzednej Y pola na ktore ma zostac wykonany ruch
    char y;

    if(pocz.x==-1||pocz.x==-2||pocz.x==-3)///////////////////////
    {

        return pom;
    }

    cout<<"Podaj wspolrzedne pola na ktore chcesz wykonac ruch (np.4 A) "<<endl;
    if(czy_podwojne==0)
    {
        cout<<"Dodatkowo:"<<endl;
        cout<<"11. Powrot do wyboru pionka"<<endl;
    }
    if(cofniecie==1)
    {
        return pom;
    }


    cin>>x;

    if(x==11 && czy_podwojne==0) {
           ruch(n, pl);
           return pom;
           }
    cin>>y;

    if(!(((x>=1 && x<=8) && (y>='A' && y<='H')) ||  (x==11)))
    {
        cout<<"Nieprawidlowy ruch"<<endl;

        cout<<"Najpierw podaj wartosc kolumny(1-8) nastepnie litere wiersza(A-H)"<<endl<<endl;;
        cin.clear(); //zabezpieczenie przed podaniem litery zamiast liczby
        cin.sync(); //

        pom=wczytaj_wsp_pola_kon_i_sprawdz(n,pl, pocz);

        return pom;
    }//sprawdza czy podano dobry format pola

    pom = przelicz_na_wspolrzedne_tablicy(x,y);


    if(!czy_dozwolony_ruch(pocz, pom, pl, n))//sprawdza czy ruch jest dozwolony
    {
        cout<<"Bledny ruch..."<<endl<<endl;
        pom=wczytaj_wsp_pola_kon_i_sprawdz(n,pl, pocz);
        return pom;
    }


    return pom;
}
bool czy_dozwolony_ruch(Pole pocz, Pole kon, int **pl, int n)
{
    if((pocz.x+pocz.y)%2!=1) return 0;//sprawdza czy pole poczatkowe jest czarne
    if((pl[pocz.x][pocz.y])!=(n) && (pl[pocz.x][pocz.y])!=(n+2)) return 0; //sprawdza czy na polu poczatkowym stoi pionek gracza
    if((kon.x+kon.y)%2!=1) return 0; //sprawdza czy pole koncowe jest czarne
    if(pl[kon.x][kon.y]!=0) return 0;  //sprawdza czy pole koncowe jest puste
    if(abs(pocz.x-kon.x)!=abs(pocz.y-kon.y)) return 0; //sprawdza czy ruch bedzie wykonany po przekatnej

    if(pl[pocz.x][pocz.y]==n) //czy ruch zwyklym pionkiem jest poprawny
    {
       if(abs(pocz.x-kon.x)==1 && abs(pocz.y-kon.y)==1) //dla ruch bez bicia
       {
            if(n==1 && pocz.x>kon.x) return 1;//sprawdza czy ruch gracza 1 jest do przodu
            if(n==2 && pocz.x<kon.x) return 1;//sprawdza czy ruch gracza 2 jest do przodu
       }
       if((abs(pocz.x-kon.x)==2 && abs(pocz.y-kon.y)==2))  //dla ruchu z biciem
        {
            if(((pl[((pocz.x+kon.x)/2)][((pocz.y+kon.y)/2)])%2)!=(n%2) && (((pl[((pocz.x+kon.x)/2)][((pocz.y+kon.y)/2)]))!=0))
            {//spawdza jaki pionek ma być zbity
                return 1;
            }
        }
       return 0;
    }

    if(pl[pocz.x][pocz.y]==(n+2)) //czy ruch damą jest poprawny
    {
        bool czy_pola_sa_puste=1;
        Pole pierwsze_zajete;
        Pole pom;

        if(pocz.x>kon.x)// sprawdza czy ruch damą do przodu jest dozwolony// gdzie stoi pion do bicia
        {
            pom.x=pocz.x-1;
            if(pocz.y>kon.y) pom.y=pom.y-1;
            if(pocz.y<kon.y) pom.y=pom.y+1;
            for(int i=1; i<(abs(pocz.x-kon.x)-1); i++)
            {
                if(pl[pom.x][pom.y]!=0)
                {
                    if(czy_pola_sa_puste)
                    {
                        pierwsze_zajete.x=pom.x;
                        pierwsze_zajete.y=pom.y;

                    }
                    czy_pola_sa_puste=0;
                }
                pom.x--;
                if(pocz.y>kon.y) pom.y--;
                if(pocz.y<kon.y) pom.y++;
            }

        }
        if(pocz.x<kon.x)// sprawdza czy ruch damą do tyłu jest dozwolony
        {
            pom.x=pocz.x+1;
            if(pocz.y>kon.y) pom.y=pocz.y-1;
            if(pocz.y<kon.y) pom.y=pocz.y+1;
            for(int i=1; i<(abs(pocz.x-kon.x)); i++)
            {
                if(pl[pom.x][pom.y]!=0)
                {
                    if(czy_pola_sa_puste)
                    {
                        pierwsze_zajete.x=pom.x;
                        pierwsze_zajete.y=pom.y;

                    }
                    czy_pola_sa_puste=0;
                }
                pom.x++;
                if(pocz.y>kon.y) pom.y--;
                if(pocz.y<kon.y) pom.y++;
            }

        }
        if(czy_pola_sa_puste) return 1;

        if(!czy_pola_sa_puste)
        {
            if(pierwsze_zajete.x==(kon.x+1)) return 1;
            if(pierwsze_zajete.x==(kon.x-1)) return 1;
            else return 0;
        }
    }



    return 0;
}
bool sprawdz_czy_staje_sie_dama(int n, Pole kon)
{
    if(n==1 && kon.x==0)
    {
        return 1;
    }
    if(n==2 && kon.x==7)
    {
        return 1;
    }
    else return 0;
}
Dostepne_bicia *sprawdz_czy_istnieje_bicie(int n, Pole pocz, int **pl)
{
    ///Struktura z wartoscia pola z ktorego ma zastac wykonany ruch i na ktore ma zostac wykonany ruch
    Pole kon, pom;
    Dostepne_bicia *g = 0;
    Dostepne_bicia *p = 0;

    ///Struktura z wartoscia pola z ktorego ma zastac wykonany ruch i na ktore ma zostac wykonany ruch po X w wartosci podawanej przez uzytkownika
    int poczx, konx;
    ///Struktura z wartoscia pola z ktorego ma zastac wykonany ruch i na ktore ma zostac wykonany ruch po Y w wartosci podawanej przez uzytkownika
    char poczy, kony;



    if(pl[pocz.x][pocz.y]==1 || pl[pocz.x][pocz.y]==2)
    {
        if((pocz.x+2)>=0 && (pocz.y+2)>=0 && (pocz.x+2)<=7 && (pocz.y+2)<=7 && pl[pocz.x+2][pocz.y+2]==0)
    {
        kon.x=(pocz.x+2);
        kon.y=(pocz.y+2);
        if(czy_dozwolony_ruch(pocz, kon, pl, n))
        {
            if(g==0)
            {
                g=new Dostepne_bicia;
                p=g;
            }
            else
            {
                p->n=new Dostepne_bicia;
                p=p->n;
            }

            przelicz_na_wspolrzedne_planszy(pocz, kon, poczx, konx, poczy, kony);
            p->x1=poczx;
            p->y1=poczy;
            p->x2=konx;
            p->y2=kony;
        }
    }
        if((pocz.x-2)>=0 && (pocz.y+2)>=0 && (pocz.x-2)<=7 && (pocz.y+2)<=7 && pl[pocz.x-2][pocz.y+2]==0)
    {
        kon.x=(pocz.x-2);
        kon.y=(pocz.y+2);
        if(czy_dozwolony_ruch(pocz, kon, pl, n))
        {
            if(g==0)
            {
                g=new Dostepne_bicia;
                p=g;
            }
            else
            {
                p->n=new Dostepne_bicia;
                p=p->n;
            }

            przelicz_na_wspolrzedne_planszy(pocz, kon, poczx, konx, poczy, kony);
            p->x1=poczx;
            p->y1=poczy;
            p->x2=konx;
            p->y2=kony;
        }
    }
        if((pocz.x+2)>=0 && (pocz.y-2)>=0 && (pocz.x+2)<=7 && (pocz.y-2)<=7 && pl[pocz.x+2][pocz.y-2]==0)
    {
        kon.x=(pocz.x+2);
        kon.y=(pocz.y-2);
        if(czy_dozwolony_ruch(pocz, kon, pl, n))
        {
            if(g==0)
            {
                g=new Dostepne_bicia;
                p=g;
            }
            else
            {
                p->n=new Dostepne_bicia;
                p=p->n;
            }

            przelicz_na_wspolrzedne_planszy(pocz, kon, poczx, konx, poczy, kony);
            p->x1=poczx;
            p->y1=poczy;
            p->x2=konx;
            p->y2=kony;
        }
    }
        if((pocz.x-2)>=0 && (pocz.y-2)>=0 && (pocz.x-2)<=7 && (pocz.y-2)<=7 && pl[pocz.x-2][pocz.y-2]==0)
    {
        kon.x=(pocz.x-2);
        kon.y=(pocz.y-2);
        if(czy_dozwolony_ruch(pocz, kon, pl, n))
        {
            if(g==0)
            {
                g=new Dostepne_bicia;
                p=g;
            }
            else
            {
                p->n=new Dostepne_bicia;
                p=p->n;
            }

            przelicz_na_wspolrzedne_planszy(pocz, kon, poczx, konx, poczy, kony);
            p->x1=poczx;
            p->y1=poczy;
            p->x2=konx;
            p->y2=kony;
        }
    }
    }

    if(pl[pocz.x][pocz.y]==3 || pl[pocz.x][pocz.y]==4)
    {
        pom.x=pocz.x;
        pom.y=pocz.y;
        for(int i=0; i<7; i++)
        {
            pom.x++;
            pom.y++;

            if((pom.x)>=0 && (pom.y)>=0 && (pom.x)<=7 && (pom.y)<=7 && pl[pom.x][pom.y]==0 && pl[pom.x-1][pom.y-1]%2!=(n%2) && pl[pom.x-1][pom.y-1]!=0)
            {
                if(czy_dozwolony_ruch(pocz, pom, pl, n))
                {

                    if(g==0)
                    {
                        g=new Dostepne_bicia;
                        p=g;
                    }
                    else
                    {
                        p->n=new Dostepne_bicia;
                        p=p->n;
                    }

                    przelicz_na_wspolrzedne_planszy(pocz, pom, poczx, konx, poczy, kony);
                    p->x1=poczx;
                    p->y1=poczy;
                    p->x2=konx;
                    p->y2=kony;
                }
            }

        }

        pom.x=pocz.x;
        pom.y=pocz.y;
        for(int i=0; i<7; i++)
        {
            pom.x--;
            pom.y++;

            if((pom.x)>=0 && (pom.y)>=0 && (pom.x)<=7 && (pom.y)<=7 && pl[pom.x][pom.y]==0 && pl[pom.x+1][pom.y-1]%2!=(n%2) && pl[pom.x+1][pom.y-1]!=0)
            {
                if(czy_dozwolony_ruch(pocz, pom, pl, n))
                {
                    if(g==0)
                    {
                        g=new Dostepne_bicia;
                        p=g;
                    }
                    else
                    {
                        p->n=new Dostepne_bicia;
                        p=p->n;
                    }

                    przelicz_na_wspolrzedne_planszy(pocz, pom, poczx, konx, poczy, kony);
                    p->x1=poczx;
                    p->y1=poczy;
                    p->x2=konx;
                    p->y2=kony;
                }
            }

        }

        pom.x=pocz.x;
        pom.y=pocz.y;
        for(int i=0; i<7; i++)
        {
            pom.x++;
            pom.y--;

            if((pom.x)>=0 && (pom.y)>=0 && (pom.x)<=7 && (pom.y)<=7 && pl[pom.x][pom.y]==0 && pl[pom.x-1][pom.y+1]%2!=(n%2) && pl[pom.x-1][pom.y+1]!=0)
            {
                if(czy_dozwolony_ruch(pocz, pom, pl, n))
                {
                    if(g==0)
                    {
                        g=new Dostepne_bicia;
                        p=g;
                    }
                    else
                    {
                        p->n=new Dostepne_bicia;
                        p=p->n;
                    }

                    przelicz_na_wspolrzedne_planszy(pocz, pom, poczx, konx, poczy, kony);
                    p->x1=poczx;
                    p->y1=poczy;
                    p->x2=konx;
                    p->y2=kony;
                }
            }

        }

        pom.x=pocz.x;
        pom.y=pocz.y;
        for(int i=0; i<7; i++)
        {
            pom.x--;
            pom.y--;

            if((pom.x)>=0 && (pom.y)>=0 && (pom.x)<=7 && (pom.y)<=7 && pl[pom.x][pom.y]==0 && pl[pom.x+1][pom.y+1]%2!=(n%2) && pl[pom.x+1][pom.y+1]!=0)
            {
                if(czy_dozwolony_ruch(pocz, pom, pl, n))
                {
                    if(g==0)
                    {
                        g=new Dostepne_bicia;
                        p=g;
                    }
                    else
                    {
                        p->n=new Dostepne_bicia;
                        p=p->n;
                    }

                    przelicz_na_wspolrzedne_planszy(pocz, pom, poczx, konx, poczy, kony);
                    p->x1=poczx;
                    p->y1=poczy;
                    p->x2=konx;
                    p->y2=kony;
                }
            }

        }
    }

    if(p!=0) p->n=0;
    return g;
}
void wypisz_dostepne_bicia(Dostepne_bicia *g)
{
    HANDLE hOut;
    hOut = GetStdHandle( STD_OUTPUT_HANDLE );
    Dostepne_bicia *p = 0;
    p=g;

    while(p!=0)
    {
        cout<<endl;
        SetConsoleTextAttribute( hOut, 4);
        cout<<"Dostepne obowiazkowe bicie pionkiem: "<<p->x1<<" "<<p->y1<<" na pole: "<<p->x2<<" "<<p->y2<<endl<<endl;
        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
        p=p->n;
    };
    delete p;
}
void obowiazkowe_drugie_bicie(int n, int **pl, Pole kon)
{
    ///Struktura z wartoscia pola z ktorego ma zastac wykonany ruch
    Pole pocz;
    ///Struktura z wartoscia pola na ktore ma zastac wykonany ruch
    Pole pom;
    ///Czy istanieje drugie bicie
    bool spr=0;
    ///Lista bic
    Dostepne_bicia *g = 0;
    ///Czy istnieje kolejene bicie (wiecej niz 2)
    bool spr2=false;

    if(sprawdz_czy_staje_sie_dama(n, kon))///////////////////////
    {
        pl[kon.x][kon.y]=(n+2);
    }


        if(pl[kon.x][kon.y]==3 || pl[kon.x][kon.y]==4)
        {
            pl[kon.x][kon.y]=pl[kon.x][kon.y]-2;
            spr=1;
        }
        g=sprawdz_czy_istnieje_bicie(n, kon, pl);
        if(spr==1)
        {
            pl[kon.x][kon.y]=pl[kon.x][kon.y]+2;
            spr=0;
        }



    if(g!=0)
    {
       czy_podwojne=1;
       spr=0;
       pokaz_plansze("1","2", pl);
       wypisz_dostepne_bicia(g);
       pocz.x=kon.x;
       pocz.y=kon.y;


        do
        {
           kon = wczytaj_wsp_pola_kon_i_sprawdz(n,pl, pocz);
           Dostepne_bicia *p = 0;
           p=g;

          do
           {
               pom=przelicz_na_wspolrzedne_tablicy(p->x2, p->y2);
               if(pom.x==kon.x && pom.y==kon.y) spr =1;
               p=p->n;
           } while(p!=0);

           delete p;

        }while(spr==0);

       pl[kon.x][kon.y]=pl[pocz.x][pocz.y]; //wykonuje ruch
       pl[pocz.x][pocz.y]=0;  //
       pl[((pocz.x+kon.x)/2)][((pocz.y+kon.y)/2)]=0;

       czy_podwojne=0;
       obowiazkowe_drugie_bicie(n, pl, kon);
    }
    delete g;

    return;
}
bool obowiazkowe_pierwsze_bicie(int n, int **pl, Pole &pocz, Pole &kon)
{
    bool spr=0;
    ///Struktura z wartoscia pola z ktorego ma zastac wykonany ruch
    Pole pom;
    ///Struktura z wartoscia pola na ktore ma zastac wykonany ruch
    Pole pom2;

    Dostepne_bicia *g = 0;
    Dostepne_bicia *p = 0;
    Dostepne_bicia *m = new Dostepne_bicia;

    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
           if(pl[i][j]==n || pl[i][j]==(n+2))//////////////////
           {
              pom.x=i;
              pom.y=j;
              p=sprawdz_czy_istnieje_bicie(n, pom, pl);//zwraca liste dostepnych bić z pola, który wypadł w pentli
              if(p!=0)//jeżeli lista możliwych bić z tego pola nie jest pusta to dokleja ją na koniec listy;
              {
                  if(g==0)
                  {
                      g=p;
                      m=p;
                  }
                  else
                  {
                      while(m->n!=0)
                      {
                          m=m->n;
                      };
                      m->n=p;
                  }
              }
           }
        }
    }


    if(g!=0)
    {

       czy_podwojne=1;
       spr=0;
       pokaz_plansze("1","2", pl);
       wypisz_dostepne_bicia(g);
        Dostepne_bicia *p = 0;

        do
        {
           pocz= wczytaj_wsp_pola_pocz_i_sprawdz(n, pl);
           if(pocz.x==-1||pocz.x==-2||pocz.x==-3)
           { 
               cofnij=1;
               return 0;
           }
           kon = wczytaj_wsp_pola_kon_i_sprawdz(n,pl, pocz);
           p=g;

          do
           {
               pom2= przelicz_na_wspolrzedne_tablicy(p->x1, p->y1);
               pom=przelicz_na_wspolrzedne_tablicy(p->x2, p->y2);

               if(pom.x==kon.x && pom.y==kon.y && pom2.x==pocz.x && pom2.y==pocz.y) spr =1;
               p=p->n;
           } while(p!=0);


        }while(spr==0);

        delete p;
        spr=0;
        czy_podwojne=0;
        delete g;


        return 1;
    }
    return 0;
}
int ** przepisz_z_pliku_na_plansze(string nazwa,int  &czyj_ruch, string &u,string &u1, Lista_ruchow *&g)
{
    Lista_ruchow *p6=0;

    ///Zmienna do przepisywania z pliku
    int ilosc_pom;
    ///Zmienna plikowa
    ifstream plik;
    plik.open(nazwa.c_str());
    int pom;

    plik>>u;
    plik>>u1;

    while(!plik.eof())
    {
        if(g==0)
        {
            g=new Lista_ruchow;
            p6=g;
        }
        else
        {
            p6->n=new Lista_ruchow;
            p6=p6->n;
        }

        if(!plik.eof())
        {
            plik>>pom;
            p6->war=pom;

            plik>>pom;
            p6->ilosc=pom;

            plik>>pom;
            p6->czyj_ruch=pom;
        }
    }
    p6->n=0;
    plik.close();
    plik.clear();


    int **T=new int*[8];

    for(int x=0; x<8; x++)
    {
        T[x]=new int[8];
    }

    p6=g;
    do
    {
        p6=p6->n;
    }while(p6->n!=0);

    ilosc_pom=p6->ilosc;

    p6=g;
    if(ilosc_pom!=-1)
    {
        for(int x=0; x<((((ilosc_pom+1)*64))); x++)
        {
           p6=p6->n;
        }
    }

    for(int x=0; x<8; x++)
    {
        for(int y=0; y<8; y++)
        {
            T[x][y]=p6->war;
            czyj_ruch = p6->czyj_ruch;
            p6=p6->n;
        }
    }
    return T;
}
