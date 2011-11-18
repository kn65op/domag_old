/* 
 * File:   DBController.h
 * Author: tomko
 *
 * Created on 16 listopad 2011, 22:51
 */

#ifndef DBCONTROLLER_H
#define	DBCONTROLLER_H

#include <string>

class DBController
{
public:
  /**
   * Konstruktor przyjmujący nazwę bazy danych.
   * @param dbname Nazwa bazy dadnych.
   */
  DBController(std::string dbname);
  /**
   * Destruktor.
   */
  ~DBController();
  /**
   * Funkcja sprawdzająca czy dana baza ma odpowiednią strukturę.
   * @return true jeśli baza jest odpowiednia, false w przeciwnym wypadku.
   */
  bool checkTables();
  /**
   * Funkcja tworząca bazę danych, która jest wymagana przez aplikację. Jeśli w bazie jest choć jedna tabela do utworzenia to należy najpierw usunąć stare tabele.
   * @return true jeśli udało się stworzyć bazę, false w przeciwnym wypadku (również jeśli chociaż jedna tabela do stworzenia istnieje).
   */
  bool createTables();
  /**
   * Funkcja zwracająca informację czy baza działa prawidłowo.
   * @return true jeśli baza działa prawidłowo, false w przeciwnym wypadku.
   */
  bool isValid();
  /**
   * Funkcja usuwająca dane oraz tabele z bazy. Jeśli baza nie posiada tabel, to wciąż jest to uznawane za powodzenie operacji.
   * @return true w przypadku powodzenia, false w przeciwnym wypadku (błędu bazy).
   */
  bool dropTables();
private:
  std::string db_name;
  bool valid;
};

#endif	/* DBCONTROLLER_H */

