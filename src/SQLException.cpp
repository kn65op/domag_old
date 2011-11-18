/* 
 * File:   SQLException.cpp
 * Author: tomko
 * 
 * Created on 18 listopad 2011, 16:12
 */

#include "../headers/SQLException.h"

using namespace std;

SQLException::SQLException(string error) :
exception()
{
  this->error = error;
}

SQLException::~SQLException() throw()
{
}

std::string SQLException::getError()
{
  return error;
}

