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

class SQLite3Controller
{
public:
  /**
   * Konstruktor 
   * @param dbname lolek
   */
  SQLite3Controller(std::string dbname);
  /**
   * Funkcja open
   * @return  opens
   */
  bool open();
  bool close();
  bool executeQuery();
  bool executeSelectQuery();
  bool getNextRecord();
  
private:
  std::string db_name;
  sqlite3* db_handle;
};

#endif	/* SQLITE3CONTROLLER_H */

