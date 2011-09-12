/* 
 * File:   main.cpp
 * Author: tomko
 *
 * Created on 12 wrzesień 2011, 13:56
 */

#include <cstdlib>

#include <gtkmm-3.0/gtkmm.h>

#include "headers/MainWindow.h"
#include "headers/LoginWindow.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{
  Gtk::Main gin(argc, argv);
  
  LoginWindow lw;
  
  Gtk::Main::run(lw);
  
  if (!lw.isCorrect())
  {
    return 0;
  }
  
  MainWindow mw;
  
  Gtk::Main::run(mw);

  return 0;
}

