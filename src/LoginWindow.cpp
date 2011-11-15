/* 
 * File:   LoginWindow.cpp
 * Author: tomko
 * 
 * Created on 12 wrzesień 2011, 15:49
 */

#include "../headers/LoginWindow.h"
#include "../headers/UserChecker.h"

using namespace std;

LoginWindow::LoginWindow() :
ok("OK"),
exit_but("Wyjdź"),
new_user("Stwórz nowego użytkownika"),
login_ok(false),
login_lab("Użytkownik:", Gtk::ALIGN_END),
pass_lab("Hasło:", Gtk::ALIGN_END)
{
  initButtons();
  init();
}

LoginWindow::~LoginWindow()
{
}

void LoginWindow::init()
{
  program_name = "Domag - zaloguj się";
  set_title(program_name);

  ok.set_size_request(200, 30);
  exit_but.set_size_request(200, 30);
  new_user.set_size_request(200, 30);
  
  add(main_vbox);
  pass.set_visibility(false);
  main_vbox.pack_start(login_hbox, Gtk::PACK_SHRINK, 10);
  login_hbox.pack_start(login_lab, Gtk::PACK_SHRINK, 10);
  login_hbox.pack_start(login, Gtk::PACK_EXPAND_WIDGET, 10);
  pass_hbox.pack_start(pass_lab, Gtk::PACK_SHRINK, 10);
  pass_hbox.pack_start(pass, Gtk::PACK_EXPAND_WIDGET, 10);
  main_vbox.pack_start(pass_hbox, Gtk::PACK_SHRINK, 10);
  main_vbox.pack_start(main_hbox, Gtk::PACK_SHRINK, 10);
  main_hbox.pack_start(ok, Gtk::PACK_SHRINK, 10);
  main_hbox.pack_start(exit_but, Gtk::PACK_SHRINK, 10);
  main_hbox.pack_start(new_user, Gtk::PACK_SHRINK, 10);

  show_all_children(true);
}

bool LoginWindow::isCorrect()
{
  return login_ok;
}

void LoginWindow::initButtons()
{
   ok.signal_clicked().connect( sigc::mem_fun(*this,
              &LoginWindow::ok_clicked) );
   exit_but.signal_clicked().connect( sigc::mem_fun(*this,
              &LoginWindow::exit_clicked) );
   new_user.signal_clicked().connect( sigc::mem_fun(*this,
              &LoginWindow::new_user_clicked) );
}

void LoginWindow::ok_clicked()
{
  //TODO: doppisz
  UserChecker uc;
  if (login_ok = uc.checkUser(login.get_text(), pass.get_text()))
  {
    hide();
  }
}

void LoginWindow::new_user_clicked()
{
  //TODO: doppisz
  UserChecker uc;
  if (login.get_text() != "" && pass.get_text() != "" && uc.addUser(login.get_text(), pass.get_text()))
  {
    Gtk::MessageDialog *info = new Gtk::MessageDialog("Konto utworzono");
    info->set_modal(true);
    info->run();
    delete info;
  }
}

void LoginWindow::exit_clicked()
{
  hide();
}