/* 
 * File:   SQLException.h
 * Author: tomko
 *
 * Created on 18 listopad 2011, 16:12
 */

#ifndef SQLEXCEPTION_H
#define	SQLEXCEPTION_H

#include <string>

class SQLException
{
public:
  /**
   * Kontruktor przyjmujący stringa.
   * @param  error Informacja dla użytkownika co było przyczyną błedu.
   */
  SQLException(std::string error);
  /**
   * Destruktor.
   */
  ~SQLException() throw();
  /**
   * Funkcja pozwalająca odczytać komunikat błedu.
   * @return Komunikat błedu.
   */
  std::string getError();
private:
  std::string error;
};

#endif	/* SQLEXCEPTION_H */

