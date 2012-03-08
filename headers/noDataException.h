/* 
 * File:   noDataException.h
 * Author: tomko
 *
 * Created on 18 listopad 2011, 17:47
 */

#ifndef NODATAEXCEPTION_H
#define	NODATAEXCEPTION_H

class NoDataException
{
public:
  /**
   * Kontruktor.
   */
  NoDataException();
  /**
   * Destruktor.
   */
  virtual ~NoDataException() throw();
private:

};

#endif	/* NODATAEXCEPTION_H */

