#ifndef PLANSZA_H
#define PLANSZA_H

#endif // PLANSZA_H
#include <iostream>
#include <zapisz_wczytaj_cofnij.h>


using namespace std;

/** \brief Struktura pola planszy.
 *
* Struktura zawierajaca informacje o okreslonym polu na planszy
*/
struct Pole
{
    /// Wartosci indeksow X i Y w tablicy planszy
    int x,y;
};


/** \brief Element listy z dostepnymi biciami.
 *
* Element listy dynamicznej zawirajacej informacje o dostepnych biciach.
*/
struct Dostepne_bicia
{
    /// Indeksy X pol z ktorego i na ktore moze zostac wykanane bicie
    int x1, x2;
    /// Indeksy Y pol z ktorego i na ktore moze zostac wykanane bicie
    char y1, y2;
    /// Wskaźnik na następny element list
    Dostepne_bicia *n;
};


/** \brief Steruje rozgrywka dwoch graczy.
 *
* Funkcja zostaje automatycznie uruchomiona po wyborze gry 2 graczy w funkcji "interfejs_nowa_gra"
* Steruje rozgrywka. Przydziela ruch gracza. Dodaje wartosci do statystyk graczy. Uruchamia funkcje "ruch", "pokaz_plansze", a takze "tworz_plansze".
* Ponad to po każdym ruchu uruchamia funkcje sprawdzajaca czy nastal koniec rozgrywki (funcja sprawdz_czy_koniec)
* oraz uruchamia funkcje pokaz_zyciezce po rozegranej grze.
*
* \param u1 pierwszy uzytkownik ktory uczestniczy w grze
* \param u2 drugi uzytkownik ktory uczestniczy w grze
* \param **pl plansza rozgrywki
* \param wczytanie czy gra zostala wczytana czy rozpoczeta od nowa
* \param timen czy funkcje zosatje uruchomiona pierwszy raz
* \param czyj_ruch ktory gracz bedzie wykonywal ruch
* \param *g lista ruchow ktore zostaly juz wykonane
*
* \see void interfejs_nowa_gra()
* \see void ruch(int n, int **pl)
* \see void pokaz_plansze(string u1, string u2, int **pl)
* \see int **tworz_plansze()
* \see bool sprawdz_czy_koniec(int **pl)
* \see void pokaz_zwyciesce(string u1, string u2, int **pl)
*/
void gra_2_graczy(string u1, string u2, int **pl, int timen, int wczytanie, int czyj_ruch, Lista_ruchow *g);

/** \brief Tworzy nowa plansze.
 *
* Podfunkcja funcji gra_2_graczy uruchmiana tylko na poczatku rozgrywki.
* Funkcja tworzy plansze z poczatkowym ustawieniem pionkow.
*
* \see void gra_2_graczy(string u1, string u2, int **pl, int timen, int wczytanie, int czyj_ruch, Lista_ruchow *g)
* \return **pl - plansza rozgrywki
*/
int **tworz_plansze();

/** \brief Wyswietla plansze
 *
* Wyswietla obecny wyglad planszy.
* Funkcja uruchamiana po kazdym ruchu, wczytaniu, cofnieciu, zapisie oraz po uruchomieniu nowej gry.
*
* \param u1 pierwszy uzytkownik ktory uczestniczy w grze
* \param u2 drugi uzytkownik ktory uczestniczy w grze
* \param **pl - obecny wyglad planszy
*/
void pokaz_plansze(string u1, string u2,int **pl);

/** \brief Wykonywanie ruchu.
 *
* Podfunkcja funcji gra_2_graczy.
* Funkcja odpowiada za caloksztalt operacji dotyczacych wykonania ruchu.
* Przy pomocu podfunkcji wyczytuje pole z ktorego ma byc wykonany ruch (funcja wczytaj_wsp_pola_kon_i_sprawdz), pole na ktore ma byc wykonany ruch (funcja Pole wczytaj_wsp_pola_pocz_i_sprawdz) i sprawdza czy ruch ten jest dozwolony (funkcja czy_dozwolony_ruch).
* Jezeli jest wykonuje go.
* Ponad to sprawdza czy pionek po wykonanym ruchu nie staje sie dama (sprawdz_czy_staje_sie_dama).
* Odpowiada za respektowanie obowiazkowych bic (obowiazkowe_pierwsze_bicie) i podwojnych być (obowiazkowe_drugie_bicie).
*
* \param n indeks pionkow gracza wykonujacego ruch
* \param **pl tablica z obecnym wygladem planszy
*
* \see bool obowiazkowe_pierwsze_bicie(int n, int **pl, Pole &pocz, Pole &kon)
* \see void obowiazkowe_drugie_bicie(int n, int **pl, Pole kon)
* \see bool czy_dozwolony_ruch(Pole pocz, Pole kon, int **pl, int n)
* \see bool sprawdz_czy_staje_sie_dama(int n, Pole kon)
* \see Pole wczytaj_wsp_pola_kon_i_sprawdz(int n, int **pl, Pole pocz)
* \see Pole wczytaj_wsp_pola_pocz_i_sprawdz(int n, int **pl)
*/
void ruch(int n, int **pl);

/** \brief Sprawdza czy gra nie zosala rozegrana.
 *
* Funcja sprawdza czy zostal spelniony jeden z warunkow rozegrania gry.
* Jesli tak zwarca true. Jesli nie false.
*
* \param **pl tablica z obecnym wygladem planszy
* \return true/false
*/
bool sprawdz_czy_koniec(int **pl);

/** \brief Pokazuje zwyciezce gry.
 *
* Funkcja zostaje uruchomiona po zwtuceniu wartosci "1" przez funkcje "sprawdz_czy_koniec".
* Funkcja wysietla zwyciezce rozgrywki i dodaje to zdarzenie do statystyk.
*
* \param u1 pierwszy uzytkownik ktory uczestniczy w grze
* \param u2 drugi uzytkownik ktory uczestniczy w grze
* \param **pl tablica z obecnym wygladem planszy
* \see bool sprawdz_czy_koniec(int **pl)
*/
void pokaz_zwyciesce(string u1, string u2, int **pl);

/** \brief Przelicza wartosc pola podana przez gracza na wartosc w tablicy.
 *
* Funkcja przelicza podana przez gracza wartosc pola na pole odopwiadajace mu w tablicy z wygladem planszy.
* Np. 3 B na 5 1.
*
* \param x pierwsza wspolrzedna pionka
* \param y druga wspolrzedna pionka
* \return pom zmiennna okreslajaca pole na ktorym ma zostac przeprowadzona operacja
*/
Pole przelicz_na_wspolrzedne_tablicy(int x, char y);

/** \brief Przelicza wartosci w tablicy na wartosc pola jakie podaje gracz.
 *
* Funkcja przelicza dwie wartosci pol w tablicy na wartosc pola jakie podaje gracz.
* Np. 5 1 na 3 B.
*
* \param pocz pierwsza przeliczana wartosc wejsciowa
* \param kon  druga przeliczana wartosc wejsciowa
* \param &poczx pierwsza wyjsciowa wartosc pola po wspolrzednej X
* \param &konx druga wyjsciowa wartosc pola po wspolrzednej X
* \param &poczy pierwsza wyjsciowa wartosc pola po wspolrzednej Y
* \param &kony druga wyjsciowa wartosc pola po wspolrzednej Y
*/
void przelicz_na_wspolrzedne_planszy(Pole pocz, Pole  kon, int &poczx, int &konx, char &poczy, char &kony);

/** \brief Sprawdza czy wspolrzedne poczatkowe ruchu sa poprawne.
 *
* Funkcja prosi o podanie pola z ktorego ma zostac wykonany ruch, a nastepnie
* sprawdza czy wspolrzedne pola sa poprawne.
*
* \param n okresla indeks pionkow gracza wykonujacego ruch
* \param **pl plansza rozgrywki
* \return pole - wspolrzedne podanego pola (jesli jest poprawne)
*/
Pole wczytaj_wsp_pola_pocz_i_sprawdz(int n, int **pl);

/** \brief Sprawdza czy wspolrzedne koncowe ruchu sa poprawne.
 *
* Funkcja prosi o podanie pola na ktore ma zostac wykonany ruch, a nastepnie
* sprawdza czy wspolrzedne pola sa poprawne.
* Oraz czy ruch, ktory chce wykonac gracz bedzie doswolony (funcja czy_dozwolony_ruch)
*
*
* \param n okresla indeks pionkow gracza wykonujacego ruch
* \param **pl plansza rozgrywki
* \param pocz struktura z indeksem pola z ktorego ma zostac wykonany ruch
* \return pole - wspolrzedne podanego pola (jesli jest poprawne)
* \see bool czy_dozwolony_ruch(Pole pocz, Pole kon, int **pl, int n)
*/
Pole wczytaj_wsp_pola_kon_i_sprawdz(int n, int **pl, Pole pocz);

/** \brief Sprawdza czy ruch z podanych pol jest dozwolony.
 *
* Funkcja analizuje czy ruch miedzy polami podanymi jako wartosci wejsciowe bedzie dozwolony.
* Dozwolony - true, niedozwolony - false.
*
* \param pocz struktura z indeksem pola z ktorego ma zostac wykonany ruch
* \param kon struktura z indeksem pola na ktore ma zostac wykonany ruch
* \param **pl tablica z obecnym wygladem planszy
* \param n okresla indeks pionkow gracza wykonujacego ruch
* \return true/false
*/
bool czy_dozwolony_ruch(Pole pocz, Pole kon, int **pl, int n);

/** \brief Sprawdza czy pionek nie staje sie dama
 *
* Po wykonaniu ruchu funkcjasprawdza czy pionek nie powienien byc zamieniony na dame.
* Staje sie - true, nie staje sie - false.
*
* \param kon struktura z indeksem pola na ktore ma zostac wykonany ruch
* \param n okresla indeks pionkow gracza wykonujacego ruch
* \return true/false
*/
bool sprawdz_czy_staje_sie_dama(int n, Pole kon);

/** \brief Sprawdza czy pionek nie staje sie dama
 *
* Funkcja przeszukuje tablice planszy poszukujac dostepnych byc.
* Jesli istnieje tworzy liste zawierajaca dane o ruchu
*
* \param pocz struktura z indeksem pola z ktorego ma zostac wykonany ruch
* \param **pl tablica z obecnym wygladem planszy
* \param n okresla indeks pionkow gracza wykonujacego ruch
* \return *g lista dostepnych bic
* \see struct Dostepne_bicia
*/
Dostepne_bicia * sprawdz_czy_istnieje_bicie(int n, Pole pocz, int **pl);

/** \brief Wypisuje dostepne bicia
 *
* Funkcja wypisuje liste dostepnych bic utworzana w funcji "sprawdz_czy_istnieje_bicie"
*
* \param *g lista dostepnych bic
*
* \see struct Dostepne_bicia
* \see sprawdz_czy_istnieje_bicie
*/
void wypisz_dostepne_bicia(Dostepne_bicia *g);

/** \brief Sprawdza czy nie wystepuje drugie bicie.
 *
* Funkcja analizuje tablice planszy czy nie wystepuje obowiazkowe drugie bicie.
* Funkcja uzywa podfunkcji "sprawdz_czy_istnieje_bicie".
* Jesli istnieje tworzy liste zawierajaca dane o ruchu
*
* \param kon struktura z indeksem pola z ktorego ma zostac wykonany ruch
* \param **pl tablica z obecnym wygladem planszy
* \param n okresla indeks pionkow gracza wykonujacego ruch
* \see Dostepne_bicia * sprawdz_czy_istnieje_bicie(int n, Pole pocz, int **pl)
*/
void obowiazkowe_drugie_bicie(int n, int **pl, Pole kon);

/** \brief Sprawdza czy nie wystepuje pierwsze bicie.
 *
* Funkcja analizuje tablice planszy czy nie wystepuje obowiazkowe pierwsze bicie.
* Funkcja uzywa podfunkcji "sprawdz_czy_istnieje_bicie".
* Jesli istnieje tworzy liste zawierajaca dane o ruchu i wymusza jego wykananie.
*
* \param pocz struktura z indeksem pola z ktorego ma zostac wykonany ruch
* \param kon struktura z indeksem pola na ktore ma zostac wykonany ruch
* \param **pl tablica z obecnym wygladem planszy
* \param n okresla indeks pionkow gracza wykonujacego ruch
* \return true/false
*/
bool obowiazkowe_pierwsze_bicie(int n, int **pl, Pole &pocz, Pole &kon);
/** \brief Wczytuje plansze z pliku.
 *
* Po wczytaniu gry funkcja tworzy tablice a nastepnie przepisuje do niej dane z pliku zapisu ktorego nazwa zostala podana jako argument funkcji.
* Ponad to tworzy liste ruchow ktore zosatly juz wykonane o ktorych informacja jest zawarta w pliku oraz wczytuje ktorego gracza jest ruch.
*
* \param nazwa nazwa zapisanej gry
* \param &czyj_ruch ktory gracz bedzie wykonywal ruch
* \param &u1 pierwszy uzytkownik ktory uczestniczy w grze
* \param &u2 drugi uzytkownik ktory uczestniczy w grze
* \param *g lista dostepnych bic
*
* \return **tab wyglad zapisanej panszy
*
* \see int **tworz_plansze();
* \struct Lista_ruchow
*/
int ** przepisz_z_pliku_na_plansze(string nazwa,int  &czyj_ruch, string &u,string &u1, Lista_ruchow *&g);
