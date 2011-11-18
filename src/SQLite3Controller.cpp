/* 
 * File:   SQLite3Controller.cpp
 * Author: tomko
 * 
 * Created on 16 listopad 2011, 22:49
 */

#include "../headers/SQLite3Controller.h"
#include "../headers/sqlite3.h"
#include "../headers/Helper.h"

#include <string>

using namespace std;

SQLite3Controller::SQLite3Controller(string dbname)
{
  db_name = dbname;
  stmt = NULL;
  db_handle = NULL;
  opened = false;
  is_row = false;
}

bool SQLite3Controller::open()
{
  if (opened)
  {
    return opened;
  }
  if (sqlite3_open(db_name.c_str(), &db_handle) == SQLITE_OK && db_handle)
  {
    opened = true;
  }
  return opened;
}

bool SQLite3Controller::close()
{
  if (opened && sqlite3_close(db_handle) == SQLITE_OK) //KWP ewentualnie co zrobić z busy?
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

void SQLite3Controller::executeQuery(std::string query) throw (SQLException)
{
  prepareStatement(query);
  int n = sqlite3_step(stmt);
  clearStatement();
  if (n != SQLITE_DONE)
  {
    throw SQLException(Helper::intToString(n));
  }
}

void SQLite3Controller::executeSelectQuery(std::string query) throw (SQLException)
{
  prepareStatement(query);
}

void SQLite3Controller::prepareStatement(std::string query) throw (SQLException)
{
  int n = sqlite3_prepare_v2(db_handle, query.c_str(), -1, &stmt, NULL);
  if (!stmt && n != SQLITE_OK)
  {
    clearStatement();
    throw SQLException("Bład");
  }
}

bool SQLite3Controller::getNextRecord()
{
  if (stmt && sqlite3_step(stmt) == SQLITE_ROW)
  {
    is_row = true;
    return true;
  }
  clearStatement();
  return false;
}

void SQLite3Controller::clearSelectQuery()
{
  clearStatement();
}

void SQLite3Controller::clearStatement()
{
  sqlite3_finalize(stmt);
  stmt = NULL;
  is_row = false;
}

int SQLite3Controller::getType(int n) throw (NoDataException)
{
  if (n < 0 || n > sqlite3_column_count(stmt) - 1) throw NoDataException();
  if (is_row)
  {
    return sqlite3_column_type(stmt, n);
  }
  throw NoDataException();
}

int SQLite3Controller::getIntFromNColumn(int n) throw (NoDataException, WrongDataException)
{
  int type = getType(n);
  if (type == SQLITE_NULL)
  {
    return 0;
  }
  if (type == SQLITE_INTEGER)
  {
    return sqlite3_column_int(stmt, n);
  }
  throw WrongDataException();
}

string SQLite3Controller::getStringFromNColumn(int n) throw (NoDataException, WrongDataException)
{
  int type = getType(n);
  if (type == SQLITE_NULL)
  {
    return "";
  }
  if (type == SQLITE_TEXT)
  {
    return string(reinterpret_cast<const char*> (sqlite3_column_text(stmt, n)));
  }
  throw WrongDataException();
}

double SQLite3Controller::getDoubleFromNColumn(int n) throw (NoDataException, WrongDataException)
{
  int type = getType(n);
  if (type == SQLITE_NULL)
  {
    return 0.0;
  }
  if (type == SQLITE_FLOAT)
  {
    return sqlite3_column_double(stmt, n);
  }
  throw WrongDataException();
}