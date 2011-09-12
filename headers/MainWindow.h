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
  virtual ~MainWindow();
private:
  std::string program_name;
  Gtk::VBox main_vbox;
  Gtk::HBox main_hbox; //TODO: do zmiany byc może
  Glib::RefPtr<Gtk::ActionGroup> action_group;
  Glib::RefPtr<Gtk::UIManager> ui_manager;
  
  void init();
  void initMainVbox();
  Gtk::Widget* initMenu();
  void menu_file_quit();
};

#endif	/* MAINWINDOW_H */

