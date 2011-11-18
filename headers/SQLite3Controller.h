/* 
 * File:   SQLite3Controller.h
 * Author: tomko
 *
 * Created on 16 listopad 2011, 22:49
 */

#ifndef SQLITE3CONTROLLER_H
#define	SQLITE3CONTROLLER_H

#include "../headers/sqlite3.h"
#include <string>
#include "../headers/SQLException.h"

/**
 * Klasa obsługująca sqlite3. Przydatna, gdy chcemy zbudować obsługę własnej bazy danych.
 */
class SQLite3Controller
{
public:
  /**
   * Konstruktor przyjmujący nazwę bazy danych.
   * @param dbname Nazwa bazy danych.
   */
  SQLite3Controller(std::string dbname);
  /**
   * Funkcja otwierająca bazę danych do obsługi. Musi być wywołana przed wykonaniem zapytań.
   * @return  true jeśli udało się otworzyć bazę, false w przeciwnym wypadku
   */
  bool open();
  /**
   * Funcka zamykająca bazę danych. Przed uruchomieniem funkcji należy zamknąć wszystkie zapytania. Po wywołaniu tej funkcji, aby ponownie móc korzystać z bazy należy ponownie otworzyć bazę.
   * @return true jeśli udało się zamknąć bażę, false w przeciwnym wypadku
   */
  bool close();
  /**
   * Funkcja wkonująca podane zapytanie.
   * @param query Zapytanie do wykonania
   * @return true jeśli zapytanie zostało zakończone powodzeniem, false w przeciwnym wypadku
   */
  bool executeQuery(std::string query) throw(SQLException);
  bool executeSelectQuery();
  bool getNextRecord();
  /**
   * Funkcja zwracająca nazwę używanej bazy danych.
   * @return Nazwa aktualnie używanej bazy danych.
   */
  std::string getDb_name();
  /**
   * Funkcja ustawiająca używaną bazę danych.
   * @param Nazwa bazy danych, którą chcemy ustawić.
   */
  void setDb_name(std::string);
  /**
   * Funkcja zwracająca informację czy dana baza danych jest otwarta.
   * @return true jeśli jest otwarta, false w przeciwnym wypadku.
   */
  bool isOpened(void);
  
  ~SQLite3Controller();
  
private:
  bool opened;
  std::string db_name;
  sqlite3* db_handle;
  //TODO dodaj bool opened
};

#endif	/* SQLITE3CONTROLLER_H */

