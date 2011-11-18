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
   * Funkcja tworząca bazę danych, która jest wymagana przez aplikację. Aktualna zawartość bazy danych jest kasowana.
   * @return true jeśli udało się stworzyć bazę, false w przeciwnym wypadku.
   */
  bool createTables();
  /**
   * Funkcja zwracająca informację czy baza działa prawidłowo.
   * @return true jeśli baza działa prawidłowo, false w przeciwnym wypadku.
   */
  bool isValid();
private:
  std::string db_name;
  bool valid;
};

#endif	/* DBCONTROLLER_H */

