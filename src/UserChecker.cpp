/* 
 * File:   UserChecker.cpp
 * Author: tomko
 * 
 * Created on 19 wrzesień 2011, 14:07
 */

#include "../headers/UserChecker.h"

#include <openssl/sha.h>
#include <cstring>

using namespace std;

//UserChecker::UserChecker()
//{
//  name = "Data/accounts";
//}

UserChecker::~UserChecker()
{
}

bool UserChecker::checkUser(std::string user, std::string pass)
{
  if (!openStorage())
  {
    false;
  }
  bool ok = false;
  string user_file, pass_file;
  while (getNextUser())
  {
    user_file = getUser();
    pass_file = getPass();
    if (user_file == user)
    {
      if (pass_file == sha(pass))
      {
        ok = true;
      }
    }
  }
  closeStorage();
  return ok;
}

bool UserChecker::addUser(std::string user, std::string pass)
{
  string sh = sha(pass);
  saveUser(user, sh);
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