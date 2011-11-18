/* 
 * File:   SQLException.h
 * Author: tomko
 *
 * Created on 18 listopad 2011, 16:12
 */

#ifndef SQLEXCEPTION_H
#define	SQLEXCEPTION_H

#include <exception>
#include <string>

class SQLException :public std::exception
{
public:
  SQLException(std::string);
  ~SQLException() throw();
  std::string getError();
private:
  std::string error;
};

#endif	/* SQLEXCEPTION_H */

