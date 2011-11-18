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
  /**
   * Konstruktor inicjujący grafike.
   */
  LoginWindow();
  /**
   * Destruktor.
   */
  virtual ~LoginWindow();
  /**
   * Funkcja zwracajaca wynik logowania.
   * @return true, jeśli użytkownik się zalogował, false w przeciwnym wypadku.
   */
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
  void initButtons();
  void ok_clicked();
  void exit_clicked();
  void new_user_clicked();
};

#endif	/* LOGINWINDOW_H */

