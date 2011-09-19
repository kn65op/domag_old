/* 
 * File:   UserChecker.h
 * Author: tomko
 *
 * Created on 19 wrzesień 2011, 14:07
 */

#ifndef USERCHECKER_H
#define	USERCHECKER_H

#include <string>

class UserChecker
{
public:
  UserChecker();
  UserChecker(const UserChecker& orig);
  virtual ~UserChecker();
  
  bool checkUser(std::string user, std::string pass);
  bool addUser(std::string user, std::string pass);
private:
  std::string filename;
  std::string sha(std::string what);
};

#endif	/* USERCHECKER_H */

