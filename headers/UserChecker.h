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
  UserChecker(std::string nname) :name(nname)
  {
    
  }
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

  /** 
   * Klasa wyjątku w razie braku istnienia pliku lub bazy danych, w którym powinny znajdować się dane użytkowników.
   */
  class NoSpaceException
  {
  private:
    std::string name;
  public:

    std::string getName() const
    {
      return name;
    }
  };
private:
  std::string sha(std::string what);
  /**
   * Prywatny konstruktor, by nie można było stworzyć obiektu bez miejsca do zapisywania konstrukor.
   */
  UserChecker();
protected:
  std::string name;
  /**
   * Funkcja otwierająca miejsce przechowywania.
   * @return true jeśli zakończono powodzeniem, false w przeciwnym wypadku.
   */
  virtual bool openStorage() =0;
  /**
   * Funkcja zwracająca informacje czy są jeszcze niepsrawdzeni użytkownicy i przechodząca do następnego użytkownika.
   * @return true jeśli są, false w przeciwnym wypadku.
   */
  virtual bool getNextUser() =0;
  /**
   * Funkcja zwracająca nazwę aktualnego użytkownika.
   * @return  nazwa aktualnego użytkownika.
   */
  virtual std::string getUser() const =0;
  /**
   * Funkcja zwracająca hasło aktualnego użytkownika.
   * @return  hasło aktualnego użytkownika.
   */
  virtual std::string getPass() const =0;
  /**
   * Funkcja zamykająca miejsce przechowywania.
   */
  virtual void closeStorage() =0;
  /**
   * Funkcja zapisująca użytkownika.
   * @param user nazwa użytkownika.
   * @param pass hasło użytkownika.
   */
  virtual void saveUser(std::string user, std::string pass) const =0;
};

#endif	/* USERCHECKER_H */

