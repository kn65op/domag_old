/* 
 * File:   main.cpp
 * Author: tomko
 *
 * Created on 12 wrzesień 2011, 13:56
 */

#include <cstdlib>
#include <string>

#include <gtkmm-3.0/gtkmm.h>

#include "headers/MainWindow.h"
#include "headers/LoginWindow.h"
#include "headers/SQLite3Controller.h"

//#define TEST

#ifdef TEST
#include <iostream>
#endif

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{
#ifdef TEST
  SQLite3Controller sql("data.sqlite3");
  cout << sql.open() << "\n";
  sql.executeQuery("CREATE TABLE first (a INTEGER PRIMARY KEY)");
  cout << sql.close() << "\n";  
  
#else
  
  std::string dbname = "data.sqlite3"
  Gtk::Main gin(argc, argv);
  
  LoginWindow lw;
  
  Gtk::Main::run(lw);
  
  if (!lw.isCorrect())
  {
    return 0;
  }
  
  MainWindow mw;
  
  Gtk::Main::run(mw);
#endif

  return 0;
}

