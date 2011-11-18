/* 
 * File:   SQLite3ControllerTest.cpp
 * Author: tomko
 *
 * Created on 2011-11-17, 21:38:32
 */

#include <stdlib.h>
#include <iostream>
#include "../headers/SQLite3Controller.h"

// Google GTest Framework Example

// TO INSTALL

// sudo apt-get install libgtest-dev

// sudo apt-get install libgtest0 


// To COMPILE IT

// g++ main.cc -lgtest_main

// TO RUN

// ./a.out

//

// TO GET HELP HOW TO RUN

//./a.out --help

//

// TO FILTER TEST EXECUTION

// ./a.out --gtest-filter=SquareRootTest.PositiveNos

// THIS ONLY RUN SINGLE TEST WHICH IS SPECIFIED.

// FOR MORE INFO, use --help at your test program.

//

// to find out more functions of gtest, just go to /usr/include/gtest

// 


#include "gtest/gtest.h"
#include "../headers/SQLite3Controller.h"

TEST(SQLiteControllerTestConstructor, String)
{
  SQLite3Controller *sql = new SQLite3Controller("a");
  EXPECT_FALSE(sql->isOpened());
  delete sql;
  sql = new SQLite3Controller("");
  EXPECT_FALSE(sql->isOpened());
  delete sql;
}

TEST(Open, ValidDatabases)
{
  SQLite3Controller *sql = new SQLite3Controller("test.sqlite3");
  EXPECT_TRUE(sql->open());
  delete sql;
}

TEST(Open, InvalidDatabases)
{
  SQLite3Controller *sql = new SQLite3Controller("test.sqlite3");
  EXPECT_TRUE(sql->open());
  SQLite3Controller *sql2 = new SQLite3Controller("test.sqlite3");
  EXPECT_TRUE(sql2->open());
  delete sql2;
  delete sql;
  sql = new SQLite3Controller("");
  EXPECT_TRUE(sql->open());
  delete sql;
}

TEST(Close, ValidDatabases)
{
  SQLite3Controller *sql = new SQLite3Controller("test.sqlite3");
  EXPECT_FALSE(sql->close());
  ASSERT_TRUE(sql->open());
  EXPECT_TRUE(sql->close());
  delete sql;
}

int main(int argc, char **argv)
{

  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();

}

