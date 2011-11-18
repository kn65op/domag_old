/* 
 * File:   Helper.cpp
 * Author: tomko
 * 
 * Created on 18 listopad 2011, 16:50
 */

#include "../headers/Helper.h"

#include <sstream>

using namespace std;

Helper::Helper()
{
  
}

string Helper::intToString(int n)
{
  stringstream ss;
  ss << n;
  return ss.str();
}
