/* 
 * File:   DBController.cpp
 * Author: tomko
 * 
 * Created on 16 listopad 2011, 22:51
 */

#include "../headers/DBController.h"
#include "../headers/SQLException.h"

#include <string>

using namespace std;

DBController::DBController(string dbname) :
sql(dbname)
{
  db_name = dbname;
  valid = sql.open();
}

bool DBController::checkTables()
{
  try
  {
    string check_articles = "select id, name, grup_id form articles;";
    sql.executeSelectQuery(check_articles);
    sql.clearSelectQuery();
    string check_groups = "select id, name form groups;";
    sql.executeSelectQuery(check_groups);
    sql.clearSelectQuery();
  }
  catch (SQLException sql)
  {
    return false;
  }
  return true;
}

bool DBController::createTables()
{
  try
  {
    string create_articles = "create table articles"
            "("
            " id integer primary key autoincrement,"
            " name text not null,"
            " group_id not null"
            ");";
    sql.executeQuery(create_articles);
    string create_groups = "create table groups"
            "("
            " id integer primary key autoincrement,"
            " name text not null"
            ");";
    sql.executeQuery(create_groups);
  }
  catch (SQLException)
  {
    return false;
  }
  return true;
}

bool DBController::dropTables()
{
    try
  {
    string drop_articles = "drop table if exists articles;";
    sql.executeQuery(drop_articles);
    string drop_groups = "drop table if exists groups;";
    sql.executeQuery(drop_groups);
  }
  catch (SQLException)
  {
    return false;
  }
  return true;
}

bool DBController::isValid()
{
  return valid;
}

DBController::~DBController()
{
  sql.close();
}