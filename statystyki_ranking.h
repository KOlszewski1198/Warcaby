#ifndef STSTYSTYKI_RANKING_H
#define STSTYSTYKI_RANKING_H
#include <iostream>

#endif // STSTYSTYKI_RANKING_H

using namespace std;

/** \brief Struktura z danymi do rankingu.
 *
* Struktura ktora zawiera informacje o graczach do wyswielanania rankingu wedle okreslonego kryterium.
*/

struct Ranking
{
    /// Imie gracza
    string u;
    /// Wartosc gracza w okreslonym kryterium
    double war;
};


/** \brief Wypisuje statystyki gracza.
 *
* Podfunkcja funkcji "interfejs_statystyki".
* Wypisuje kolejno ststystyki okreslonego gracza.
*
* \param uzytkownik gracz ktorego ststystyki maja zostac wypisane
* \see void interfejs_statystyki()
*/
void wypisz_statystyki(string uzytkownik);

/** \brief Uaktualnia statystyki gracza
 *
* Po wykonanu okreslonej czynnosci statystycznej funkcja zwieksza jej wartosc w pliku o nazwie uzytkownika.
*
* \param u nazwa uzytkownika
* \param x numer pozycji statystyki, ktora ma zostac zmodyfikowana
* \param inf wartosc o jaka ma zostac zwiekszona pozycja w statystyce
*/
void dodaj_do_statystyk(string u, int x, double inf);

/** \brief Wypisuje ranking graczy.
 *
* Podfunkcja funkcji "interfejs_ranking".
* Sortuje liste uzytkownikow na podstawie kryterium rankingowego(funkcja sortuj_tab)
* Wypisuje posortowana liste.
*
* \param x kryterium wypisanej ststystyki
* \see void sortuj_tab(Ranking T[], int roz)
* \see void interfejs_ranking();
*/
void wypisz_ranking(int x);

/** \brief Sortuje tablice graczy.
 *
* Podfunkcja funkcji "wypisz_statystyki".
* Sortuje liste uzytkownikow na podstawie kryterium rankingowego
*
* \param T[] tablica z lista graczy i wartosciami poszczegulnych kryteriow
* \par roz rozmiar tablicy T[]
* \see void wypisz_statystyki(string uzytkownik);
* \see void interfejs_ranking();
*/
void sortuj_tab(Ranking T[], int roz);
