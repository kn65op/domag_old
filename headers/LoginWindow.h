/* 
 * File:   LoginWindow.h
 * Author: tomko
 *
 * Created on 12 wrzesień 2011, 15:49
 */

#ifndef LOGINWINDOW_H
#define	LOGINWINDOW_H

#include <gtkmm-3.0/gtkmm.h>
#include <string>

class LoginWindow : public Gtk::Window
{
public:
  LoginWindow();
  virtual ~LoginWindow();
  
  bool isCorrect();
private:
  std::string program_name;
  Gtk::Button ok, exit_but, new_user;
  Gtk::Entry login, pass;
  Gtk::Label login_lab, pass_lab;
  Gtk::VBox main_vbox;
  Gtk::HBox main_hbox, login_hbox, pass_hbox;
  bool login_ok;
  
  void init();
};

#endif	/* LOGINWINDOW_H */

