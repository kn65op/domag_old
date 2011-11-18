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
   * Funkcja wkonująca podane zapytanie. Jeśli wykonanie nie uda się, zostanie wyrzucony wyjątek SQLException z opisem błedu.
   * @param query Zapytanie do wykonania
   * @throws SQLException w przypadku błędu. 
   */
  void executeQuery(std::string query) throw(SQLException);
  /**
   * Funkcja wkonująca podane zapytanie typu select. Aby otrzymać pierwszy i kolejne rekordy należy zastosować metodę getNextRecord. Jeśli wykonanie nie uda się, zostanie wyrzucony wyjątek SQLException z opisem błedu.
   * @param query Zapytanie do wykonania
   * @throws SQLException w przypadku błędu. 
   */
  void executeSelectQuery(std::string query) throw(SQLException);
  /**
   * Funkcja pozwalająca na otrzymanie kolejnych rekordów dla zapytań typu select. Należy wywołać tą metodę przed pierszym pobraniem danych.
   * @return true jeśli są jeszcze jakieś rekordy do przetworzenia, false jeśli nie ma już więcej rekordów.
   */
  bool getNextRecord();
  /**
   * Funkcja zwracająca nazwę używanej bazy danych.
   * @return Nazwa aktualnie używanej bazy danych.
   */
  std::string getDb_name();
  /**
   * Funkcja zamykająca dostęp do bazy, jeśli nie chcemy pobierać więcej rekordów.
   */
  void clearSelectQuery();
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
  sqlite3_stmt* stmt;
  
  void prepareStatement(std::string query) throw(SQLException);
  void clearStatement();
};

#endif	/* SQLITE3CONTROLLER_H */

