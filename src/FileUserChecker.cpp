/* 
 * File:   FileUserChecker.cpp
 * Author: tomko
 * 
 * Created on 8 marzec 2012, 22:25
 */

#include "../headers/FileUserChecker.h"
#include <fstream>
#include <string>

void FileUserChecker::saveUser(std::string user, std::string pass) const
{
  std::ofstream file(name, std::ios::ate | std::ios::app);
  if (!file.good())
  {
    file.close();
    file.open(name);
  }
  file << user;
  file << " ";
  file << pass;
  file << "\n";
  file.close();
}

bool FileUserChecker::openStorage()
{
  in_file.open(name.c_str());
  return in_file.good();
}

bool FileUserChecker::getNextUser()
{
  if (in_file.good() && !in_file.eof())
  {
    in_file >> tmp_user;
    in_file >> tmp_pass;
    return true;
  }
  return false;
}

std::string FileUserChecker::getUser() const
{
  return tmp_user;
}

std::string FileUserChecker::getPass() const
{
  return tmp_pass;
}

void FileUserChecker::closeStorage()
{
  in_file.close();
}

