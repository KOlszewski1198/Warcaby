#ifndef ZAPISZ_WCZYTAJ_COFNIJ_H
#define ZAPISZ_WCZYTAJ_COFNIJ_H
#include <iostream>

#endif // ZAPISZ_WCZYTAJ_COFNIJ_H

using namespace std;

/** \brief Element listy ruchow.
 *
* Jest struktura listu dynamicznej zawierajacej informacje ukladach pionkow na planszy.
* Pojedynczy element listy zawiera informacje jedynie o jednym polu na szachownicy. Tak wiec 64 elementu listy skladaja sie
* na jeden wyglad planszy.
* Elementy: int ilosc , int czyj_ruch maja okreslona wartosc jednymie przy n*64 elemencie tablicy.
* W pozostalych przypadkach otrzymuja losowa wartosc -32.
*/

struct Lista_ruchow
{
    /// Jaki pionek znajduje sie na polu
    int war;
    /// Ktory to rych w tej rozgrywce
    int ilosc;
    /// Czyj ruch jest obecnie wykonywany
    int czyj_ruch;
    /// Wskaznik nastepnego elementu listy
    Lista_ruchow *n;
};

/** \brief Tworzy liste ruchow.
 *
* Funkcja jest uruchamiana po rozpoczeciu rozgrywki (funkcja gra_2_graczy)
* Funkcja tworzy dynamiczna liste ruchow (struct Lista_ruchow) z poczatkowym ustawiemiem pionkow na planszy.
* Lista ta uaktualniana po kazdym ruchu (funkcja dodaj_do_listy_ruchow)
*
* \param **pl tablica z obecnym wygladem planszy
* \param czyj_ruch okresla, ktory gracz przy danym wygladzie planszy bedzie wykonywal ruch
*
* \see Lista_ruchow * dodaj_do_listy_ruchow(int **pl, int czyj_ruch, Lista_ruchow *g)
* \see void gra_2_graczy(string u1, string u2, int **pl, int timen, int wczytanie, int czyj_ruch, Lista_ruchow *g)
* \see struct Lista_ruchow
* \return *g - lista ruchow
*/
Lista_ruchow * tworz_liste_ruchow(int **pl, int czyj_ruch);

/** \brief Dodaje do lisy ruchow.
 *
* Funkcja dodaje kolejne komorki do dynamicznej listy ruchow (struct Lista_ruchow) po kazdej zmianie wygladu planszy
*
* \param **pl tablica z obecnym wygladem planszy
* \param czyj_ruch okresla, ktory gracz przy danym wygladzie planszy bedzie wykonywal ruch
* \param *&g tablica z lista ruchow
*
* \see struct Lista_ruchow
* \return *g - lista ruchow
*/
Lista_ruchow * dodaj_do_listy_ruchow(int **pl, int czyj_ruch, Lista_ruchow *g);

/** \brief Cofa ruch.
 *
* Funkcja powoduje powrot do wczesniejszego wygladu planszy przy uzyciu listy ruchow.
* Funkcja usuwa ostatnie ustewienie z listy ruchow oraz zmienia gracza ktory wykonuje ruch
*
* \param **pl tablica z obecnym wygladem planszy
* \param &czyj_ruch okresla, ktory gracz przy danym wygladzie planszy bedzie wykonywal ruch
* \param *&g tablica z lista ruchow
*
*/
void cofnij_ruch(int **&pl, int  &czyj_ruch, Lista_ruchow *&g);

/** \brief Zapisuje gre.
 *
* Funkcja zapisuje obecny stan rozgrywki do pliku o ktorego nazwe pyta sie uzywkownika.
* Zapisany plik otrzymije przedrostek "zap_" i przyrostek ".txt".
*
* \param u pierwszy uzytkownik ktory uczestniczy w grze
* \param u1 drugi uzytkownik ktory uczestniczy w grze
* \param *&g tablica z lista ruchow
*
*/
void zapisz(Lista_ruchow *g, string u, string u1);
