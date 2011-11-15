/* 
 * File:   UserChecker.cpp
 * Author: tomko
 * 
 * Created on 19 wrzesień 2011, 14:07
 */

#include "../headers/UserChecker.h"

#include <cstring>
#include <sstream>
#include <fstream>
#include <openssl/sha.h>

using namespace std;

UserChecker::UserChecker()
{
  filename = "Data/accounts";
}

UserChecker::UserChecker(const UserChecker& orig)
{
}

UserChecker::~UserChecker()
{
}

bool UserChecker::checkUser(std::string user, std::string pass)
{
  bool ok = false;
  ifstream file(filename);
  if (!file.good())
  {
    return false;
  }
  string user_file, pass_file;
  while (!ok && !file.eof())
  {
    file >> user_file;
    file >> pass_file;
    if (user_file == user)
    {
      if (pass_file == sha(pass))
      {
        ok = true;
      }
    }
  }
  file.close();
  return ok;
}

bool UserChecker::addUser(std::string user, std::string pass)
{
  ofstream file(filename, ios::ate | ios::app);
  if (!file.good())
  {
    file.close();
    file.open(filename);
  }
  file << user;
  file << " ";
  string sh = sha(pass);
  file << sh;
  file << "\n";
  file.close();
  return true;
}

string UserChecker::sha(std::string what)
{
  char *w = new char[what.size()+1];
  strncpy(w, what.c_str(), what.size());
  w[what.size()] = '\0';
  int a = strlen(w);
  
  char out[SHA256_DIGEST_LENGTH * 2];

  SHA256_CTX context;
  unsigned char md[SHA256_DIGEST_LENGTH];

  SHA256_Init(&context);
  SHA256_Update(&context, (unsigned char*) w, strlen(w));
  SHA256_Final(md, &context);

  int i;
  //tmp.setf(ios::hex, ios::basefield);
  for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
  {
    sprintf(out+2*i, "%02x", md[i]);
 //   printf("% 02x ", md[i]);
    //tmp += md[i];
    //tmp << hex << md[i];
  }
  //printf("\n");
  string tmp(out);
  return tmp;
}