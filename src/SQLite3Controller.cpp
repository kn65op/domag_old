/* 
 * File:   SQLite3Controller.cpp
 * Author: tomko
 * 
 * Created on 16 listopad 2011, 22:49
 */

#include "../headers/SQLite3Controller.h"
#include "../headers/sqlite3.h"

#include <string>

using namespace std;

SQLite3Controller::SQLite3Controller(string dbname)
{
  db_name = dbname;
}

bool SQLite3Controller::open()
{
  if (sqlite3_open(db_name.c_str(), &db_handle) == SQLITE_OK && db_handle)
  {
    return true;
  }
  return false;
}

bool SQLite3Controller::close()
{
  if (sqlite3_close(db_handle) == SQLITE_OK) //KWP ewentualnie co zrobić z busy?
  {
    return true;
  }
  return false;
}

string SQLite3Controller::getDb_name(void)
{
  return db_name;
}

void SQLite3Controller::setDb_name(string db_name)
{
  this->db_name = db_name;
}

bool SQLite3Controller::isOpened(void)
{
  return opened;
}


SQLite3Controller::~SQLite3Controller()
{
  close();
}