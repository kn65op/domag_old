/* 
 * File:   MainWindow.cpp
 * Author: tomko
 * 
 * Created on 12 wrzesień 2011, 15:19
 */

#include <iostream>

#include "../headers/MainWindow.h"

using namespace std;

MainWindow::MainWindow()
{
  init();
}

MainWindow::~MainWindow()
{
}

void MainWindow::init()
{
  program_name = "Domag";
  set_title(program_name);
  set_default_size(800, 600);
  add(main_vbox);
  initMainVbox();
  show_all_children(true);
}

void MainWindow::initMainVbox()
{
  Gtk::Widget *pMenuBar = initMenu();
  if (pMenuBar)
  {
    main_vbox.pack_start(*pMenuBar, Gtk::PACK_SHRINK);
  }
  //main_vbox.pack_start(main_hbox, Gtk::PACK_SHRINK);
}

Gtk::Widget* MainWindow::initMenu()
{
  //przyciski menu
  action_group = Gtk::ActionGroup::create();
  //menu plik
  action_group->add(Gtk::Action::create("MenuFile", "_Plik"));
  action_group->add(Gtk::Action::create("Exit", Gtk::Stock::QUIT), sigc::mem_fun(*this, &MainWindow::menu_file_quit));

  //tworzenie uimanager
  ui_manager = Gtk::UIManager::create();
  ui_manager->insert_action_group(action_group);
  add_accel_group(ui_manager->get_accel_group());

  Glib::ustring ui_info = "<ui>"
          " <menubar name='MenuBar'>"
          "   <menu action='MenuFile'>"
          "     <menuitem action='Exit'/>"
          "   </menu>"
          " </menubar>"
          "</ui>";
  try
  {
    ui_manager->add_ui_from_string(ui_info);
  } catch (const Glib::Error& ex)
  {
    std::cerr << "building menus failed: " << ex.what();
  }
  return ui_manager->get_widget("/MenuBar");
  
}

void MainWindow::menu_file_quit()
{
  //TODO: jakieś czeki
  
  hide();
}