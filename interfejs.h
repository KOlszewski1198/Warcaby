#ifndef INTERFEJS_H
#define INTERFEJS_H

#endif // INTERFEJS_H

#include <string>
#include <statystyki_ranking.h>


using namespace std;

/** \brief Wlaczenie Menu Glownego
 *
* Funkcja wlacza sie automatycznie po uruchomienu programu.
*
* Pozwala na dlaszy wybor jednej z funcamentalnych funkcji programu czyli:
* /see void interfejs_nowa_gra()
* /see void interfejs_statystyki()
* /see void interfejs_ranking()
* /see interfejs_ranking();
* /see void interfejs_wczytaj_gre();
*
* A takze dzialan:
* - Wyloguj uzytkownika
* - Wylacz program
*/
void menu();

/** \brief Wybor typu gry.
 *
* Funkcja umozliwia wybor typu rozpoczetej gry, a takze powrot do menu glownego.
*
* \see void gra_2_graczy(string u1, string u2, int **pl, int timen, int wczytanie, int czyj_ruch, Lista_ruchow *g)
* \see void menu();
*/
void interfejs_nowa_gra();

/** \brief Wyswietlanie statystyk gracza.
 *
* Uzytkownik podaje nazwe gracza ktorego statystyki maja zostac wyswietlone, a nastepnie pobiera odpowiednie
* dane z pliku tekstowego o nazwe bedaca nazwa gracza, sortuje je i wypisuje(funcja wypisz_statystyki).
* Po wypisanu pyta czy wypisac ststystyki kolejnego gracza.
* Po zakonczeniu przechodzi do Menu glownego
*
* \see void wypisz_statystyki(string uzytkownik)
* \see void menu()
*/
void interfejs_statystyki();

/** \brief Wyswietlanie rankingu graczy.
 *
* Funkcja pyta o kryterium rankingu graczy, a nastepnie pobiera dane z plikow o nazwach istniejacych graczy
* sortuje je i wyswietla ranking najlepszych graczy.
* Po zakonczeniu powraca do menu glownego
*
* \see void menu();
*/
void interfejs_ranking();

/** \brief Wczytywanie zapisanego stanu gry.
 *
* Funkcja wyswielna zapisane stany gry(funkcja wypisz_zapisane).
* Nastepnie uzytkownik podaje nazwe zapisu ktory chce wczytac.
* Funkcja sprawdza czy zapis istnieje (funcja sprawdz_czy_istnieje_zapis)
* Funkcja wczytuje zapis i kontynuuje gre (funkcja gra_2_graczy)
*
* \see bool sprawdz_czy_istnieje_zapis(string nazwa)
* \see void wypisz_zapisane()
* \see void gra_2_graczy(string u1, string u2, int **pl, int timen, int wczytanie, int czyj_ruch, Lista_ruchow *g)
*/
void interfejs_wczytaj_gre();




/** \brief Umozliwia logowanie sie uzytkownikow.
 *
* Funkcja zostaje automatycznie uruchomiona podczas wlaczania programu, a takze po wylogowaniu.
* Funkcja wypisuje liste dostepnych uzywkownikow, a nastepnie prosi o wybranie nazwy uzytkownika
* na konto ktorego chcemy sie zalogowac.
* Jezeli gracz taki nie istnieje tworzy nowe konto gracza.
* Funkcja kozysta z funkcji wypisz uzytkownikow oraz sprawdz czy istnieje
*
* \see void wypisz_uzytkownikow();
* \see bool sprawdz_czy_istnieje(string nazwa)
* \return nazwa - nazwa zalogowanego gracza
*/
string zaloguj();

/** \brief Wypisuje liste dostepnych uzytkownikow
 *
* Funkcja pobiera z pliku o nazwie uzytkownicy.txt liste dostepnych uzytkownikow, a nastepnie wyswietla ja.
*/
void wypisz_uzytkownikow();

/** \brief Sprawadza czy podany uzytkwonik istnieje
 *
* Funkcja przeszukuje plik uzytkownicy.txt i sprawdza czy uzytkownik o podanej nazwie istnieje.
*
* \param nazwa nazwa poszukiwanego uzytkownika
* \return true lub false istnieje lub nie
*/
bool sprawdz_czy_istnieje(string nazwa);

/** \brief Sprawdza czy podany zapis istnieje
 *
* Funkcja przeszukuje plik zapis.txt w poszukiwaniu czy podany zapis istnieje na liscie zapisow
* \param nazwa nazwa poszukiwanego zapisu
* \return true lub false istnieje lub nie
*/
bool sprawdz_czy_istnieje_zapis(string nazwa);

/** \brief Wypisuje liste dostepnych zapisow
 *
* Funkcja pobiera z pliku o nazwie zapisy.txt liste dostepnych zapisow, a nastepnie wyswietla ja.
*/
void wypisz_zapisane();
