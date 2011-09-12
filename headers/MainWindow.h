/* 
 * File:   MainWindow.h
 * Author: tomko
 *
 * Created on 12 wrzesień 2011, 15:19
 */

#ifndef MAINWINDOW_H
#define	MAINWINDOW_H

#include <gtkmm-3.0/gtkmm.h>

class MainWindow : public Gtk::Window
{
public:
  MainWindow();
  MainWindow(const MainWindow& orig);
  virtual ~MainWindow();
private:

};

#endif	/* MAINWINDOW_H */

