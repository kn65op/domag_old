/* 
 * File:   noDataException.h
 * Author: tomko
 *
 * Created on 18 listopad 2011, 17:47
 */

#ifndef NODATAEXCEPTION_H
#define	NODATAEXCEPTION_H

#include <exception>

class noDataException : public std::exception
{
public:
  noDataException();
  virtual ~noDataException() throw();
private:

};

#endif	/* NODATAEXCEPTION_H */

