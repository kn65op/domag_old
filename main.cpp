/* 
 * File:   main.cpp
 * Author: tomko
 *
 * Created on 12 wrzesień 2011, 13:56
 */

#include <cstdlib>

#include <gtkmm-3.0/gtkmm.h>

#include "headers/MainWindow.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{
  Gtk::Main gin(argc, argv);
  
  MainWindow mw;
  
  Gtk::Main::run(mw);

  return 0;
}

