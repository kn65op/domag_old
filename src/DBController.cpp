/* 
 * File:   DBController.cpp
 * Author: tomko
 * 
 * Created on 16 listopad 2011, 22:51
 */

#include "../headers/DBController.h"

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
  string check_articles = "select id, name, grup_id form articles;";
  try
  {
    sql.executeQuery(check_articles);
  }
  catch ()
}


