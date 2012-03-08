/* 
 * File:   FileUserChecker.h
 * Author: tomko
 *
 * Created on 8 marzec 2012, 22:25
 */

#ifndef FILEUSERCHECKER_H
#define	FILEUSERCHECKER_H

#include "../headers/UserChecker.h"
#include <fstream>
#include <string>

class FileUserChecker : public UserChecker
{
public:
  FileUserChecker(std::string nname) :UserChecker(nname)
  {
    
  }

private:
  std::ifstream in_file;
  std::string tmp_user;
  std::string tmp_pass;
protected:
  /**
   * Funkcja otwierająca miejsce przechowywania.
   * @return true jeśli zakończono powodzeniem, false w przeciwnym wypadku.
   */
  virtual bool openStorage();
  /**
   * Funkcja zwracająca informacje czy są jeszcze niepsrawdzeni użytkownicy i przechodząca do następnego użytkownika.
   * @return true jeśli są, false w przeciwnym wypadku.
   */
  virtual bool getNextUser();
  /**
   * Funkcja zwracająca nazwę aktualnego użytkownika.
   * @return  nazwa aktualnego użytkownika.
   */
  virtual std::string getUser() const;
  /**
   * Funkcja zwracająca hasło aktualnego użytkownika.
   * @return  hasło aktualnego użytkownika.
   */
  virtual std::string getPass() const;
  /**
   * Funkcja zamykająca miejsce przechowywania.
   */
  virtual void closeStorage() ;
  /**
   * Funkcja zapisująca użytkownika.
   * @param user nazwa użytkownika.
   * @param pass hasło użytkownika.
   */
  virtual void saveUser(std::string user, std::string pass) const;

};

#endif	/* FILEUSERCHECKER_H */

