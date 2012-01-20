/* 
 * File:   SQLite3Controller.cpp
 * Author: tomko
 * 
 * Created on 16 listopad 2011, 22:49
 */

#include "../headers/SQLite3Controller.h"
#include "../headers/sqlite3.h"
#include <tomko/Helper.h>

#include <string>

using namespace std;

SQLite3Controller::SQLite3Controller(string dbname)
{
  db_name = dbname;
  stmt_no_select = NULL;
  stmt_select = NULL;
  db_handle = NULL;
  opened = false;
  is_row = false;
  is_select = false;
}

bool SQLite3Controller::open()
{
  if (db_name == "")
  {
    return false;
  }
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

/*string SQLite3Controller::getDb_name(void)
{
  return db_name;
}

void SQLite3Controller::setDb_name(string db_name)
{
  this->db_name = db_name;
}*/

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
  prepareStatement(query, &stmt_no_select);
  int n = sqlite3_step(stmt_no_select);
  clearStatement(stmt_no_select);
  if (n != SQLITE_DONE)
  {
    throw SQLException(Helper::intToString(n));
  }
}

void SQLite3Controller::executeSelectQuery(std::string query) throw (SQLException)
{
  if (is_select)
  {
    throw SQLException("Nie zakończone poprzednie zapytanie");
  }
  prepareStatement(query, &stmt_select);
  is_select = true;
}

void SQLite3Controller::prepareStatement(std::string query, sqlite3_stmt **stmt) throw (SQLException)
{
  int n = sqlite3_prepare_v2(db_handle, query.c_str(), -1, stmt, NULL);
  if (!(*stmt) && n != SQLITE_OK)
  {
    clearStatement(*stmt);
    throw SQLException("Bład");
  }
}

bool SQLite3Controller::getNextRecord()
{
  if (stmt_select && sqlite3_step(stmt_select) == SQLITE_ROW)
  {
    is_row = true;
    return true;
  }
  clearSelectQuery();
  return false;
}

void SQLite3Controller::clearSelectQuery()
{
  clearStatement(stmt_select);
  is_row = false;
  is_select = false;
}

void SQLite3Controller::clearStatement(sqlite3_stmt *stmt)
{
  sqlite3_finalize(stmt);
  stmt = NULL;
}

int SQLite3Controller::getType(int n) throw (NoDataException)
{
  if (n < 0 || n > sqlite3_column_count(stmt_select) - 1) throw NoDataException();
  if (is_row)
  {
    return sqlite3_column_type(stmt_select, n);
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
    return sqlite3_column_int(stmt_select, n);
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
    return string(reinterpret_cast<const char*> (sqlite3_column_text(stmt_select, n)));
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
    return sqlite3_column_double(stmt_select, n);
  }
  throw WrongDataException();
}