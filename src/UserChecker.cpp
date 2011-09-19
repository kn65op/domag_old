/* 
 * File:   UserChecker.cpp
 * Author: tomko
 * 
 * Created on 19 wrzesień 2011, 14:07
 */

#include "../headers/UserChecker.h"

#include <cstring>
#include <fstream>
#include <openssl/evp.h>

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
  string user_file, pass_file;
  while (!ok && !file.eof())
  {
    file >> user_file;
    file >> pass_file;
    if (user_file == user)
    {
      //TODO: sprawdzenie hasła
    }
  }
  file.close();
}

bool UserChecker::addUser(std::string user, std::string pass)
{
  ofstream file(filename, ios::ate | ios::app);
  file << "\n";
  file << user;
  file << " ";
  string sh = sha1(pass);
  file << pass;
  file.close();
}

string UserChecker::sha1(std::string what)
{
  char *w = new char[what.size()+1];
  strncpy(w, what.c_str(), what.size());
  string tmp = "";
  EVP_MD_CTX mdctx;
  const EVP_MD *md;
  unsigned char md_value[EVP_MAX_MD_SIZE];
  unsigned int md_len, i;
  OpenSSL_add_all_digests();
  md = EVP_get_digestbyname("qqq");
  if(!md) {
        printf("Unknown message digest %s\n", "qqq");
        exit(1);
 }
  EVP_MD_CTX_init(&mdctx);
  EVP_DigestInit_ex(&mdctx, md, NULL);
  EVP_DigestUpdate(&mdctx, w, strlen(w));
  EVP_DigestFinal_ex(&mdctx, md_value, &md_len);
  EVP_MD_CTX_cleanup(&mdctx);
  printf("Digest is: ");
  for (i = 0; i < md_len; i++)
  {
    printf("%02x", md_value[i]);
    tmp += md_value[i];
  }
  printf("\n");
  delete [] w;
  return tmp;
}