/* 
 * File:   WrongDataException.h
 * Author: tomko
 *
 * Created on 18 listopad 2011, 17:55
 */

#ifndef WRONGDATAEXCEPTION_H
#define	WRONGDATAEXCEPTION_H

#include <exception>

class WrongDataException : public std::exception
{
public:
  /**
   * Konstruktor.
   */
  WrongDataException();
  /**
   * Destruktor.
   */
  virtual ~WrongDataException() throw();
private:

};

#endif	/* WRONGDATAEXCEPTION_H */

