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
  
  int a(int b);
  ~DBController();
private:
  std::string db_name;
};

#endif	/* DBCONTROLLER_H */

