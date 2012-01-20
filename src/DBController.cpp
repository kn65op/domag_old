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
    string check_articles = "select article_id, name, group_id from articles;";
    sql.executeSelectQuery(check_articles);
    sql.clearSelectQuery();
    string check_groups = "select group_id, name from groups;";
    sql.executeSelectQuery(check_groups);
    sql.clearSelectQuery();
    string check_users = "select user_id, name from users;";
    sql.executeSelectQuery(check_users);
    sql.clearSelectQuery();
  } catch (SQLException sql)
  {
    return false;
  }
  return true;
}

bool DBController::createTables()
{
  try
  {
    
    string create_groups = "create table groups"
            "("
            " group_id integer primary key autoincrement,"
            " name text not null"
            ");";
    sql.executeQuery(create_groups);
    string create_articles = "create table articles"
            "("
            " article_id integer primary key autoincrement,"
            " name text not null,"
            " group_id not null references gorups(id)"
            ");";
    sql.executeQuery(create_articles);
    string create_users = "create table users"
            "("
            " user_id integer primary key autoincrement,"
            " name text not null"
            ");";
    sql.executeQuery(create_users);
  } catch (SQLException)
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
    string drop_users = "drop table if exists users;";
    sql.executeQuery(drop_users);
  } catch (SQLException)
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
  if (valid)
  {
    sql.close();
  }
}