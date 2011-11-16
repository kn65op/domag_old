/* 
 * File:   DBController.h
 * Author: tomko
 *
 * Created on 16 listopad 2011, 22:51
 */

#ifndef DBCONTROLLER_H
#define	DBCONTROLLER_H

#include <string>

class DBController
{
public:
  DBController(std::string dbname);
private:
  std::string db_name;
};

#endif	/* DBCONTROLLER_H */

