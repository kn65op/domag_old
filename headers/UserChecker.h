/* 
 * File:   UserChecker.h
 * Author: tomko
 *
 * Created on 19 wrzesień 2011, 14:07
 */

#ifndef USERCHECKER_H
#define	USERCHECKER_H

#include <string>

/**
 *  Klasa odpowiadająca za sprawdzanie użytkowników. Możliwosć przechowywania danych w pliku jak i w bazie.
 */

class UserChecker
{
public:
  /**
   * Konstrukor.
   */
  UserChecker();
  /**
   * Destruktor.
   */
  virtual ~UserChecker();
  
  /**
   * Funkcja sprawdzająca czy dane użytkownika są prawidłowe.
   * @param user Nazwa użytkownika.
   * @param pass Hasło użytkownika.
   * @return true, jeśli dane są poprawne, false w przeciwnym wypadku.
   */
  bool checkUser(std::string user, std::string pass);
  /**
   * Funkcja dodająca nowego użytkownika
   * @param user Nazwa użytkownika.
   * @param pass Hazwa użytkownika.
   * @return true, jeśli poprawnie dodano, false w przeciwnym wypadku.
   */
  bool addUser(std::string user, std::string pass);
private:
  std::string filename;
  std::string sha(std::string what);
};

#endif	/* USERCHECKER_H */

