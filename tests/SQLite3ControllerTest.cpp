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

TEST(executeQuery, CreatingInserting)
{
  SQLite3Controller *sql = new SQLite3Controller("test.sqlite3");
  ASSERT_TRUE(sql->open());
  EXPECT_THROW(sql->executeQuery("lolek"), SQLException);
  //EXPECT_NO_THROW(sql->executeQuery("DROP TABLE first;"));
  ASSERT_NO_THROW(sql->executeQuery("CREATE TABLE first (a INTEGER PRIMARY KEY);"));
  ASSERT_THROW(sql->executeQuery("CREATE TABLE first (a INTEGER PRIMARY KEY);"), SQLException);
  ASSERT_NO_THROW(sql->executeQuery("INSERT INTO first values (1);"));
  ASSERT_NO_THROW(sql->executeQuery("INSERT INTO first values (2);"));
  ASSERT_THROW(sql->executeQuery("INSERT INTO first values (1);"), SQLException);
  ASSERT_THROW(sql->executeQuery("INSERT INTO b values (2);"), SQLException);
  EXPECT_NO_THROW(sql->executeQuery("DROP TABLE first;"));
  EXPECT_THROW(sql->executeQuery("DROP TABLE first;"), SQLException);
  delete sql;
}

TEST(executeSelectQuery, selecting)
{
  SQLite3Controller *sql = new SQLite3Controller("test.sqlite3");
  ASSERT_TRUE(sql->open());
  EXPECT_THROW(sql->executeSelectQuery("lolek"), SQLException);
  ASSERT_NO_THROW(sql->executeQuery("CREATE TABLE first (id integer primary key);"));
  ASSERT_NO_THROW(sql->executeQuery("INSERT INTO first values (1);"));
  ASSERT_NO_THROW(sql->executeQuery("INSERT INTO first values (2);"));
  EXPECT_THROW(sql->executeSelectQuery("SELECT lol FROM first;"), SQLException);
  EXPECT_THROW(sql->executeSelectQuery("SELECT * FROM afirst;"), SQLException);
  EXPECT_NO_THROW(sql->executeSelectQuery("SELECT * from first;"));
  EXPECT_NO_THROW(sql->executeQuery("DROP TABLE first;"));
  delete sql;
}

TEST(getNextRecord, gettingRows)
{
  SQLite3Controller *sql = new SQLite3Controller("test.sqlite3");
  ASSERT_TRUE(sql->open());
  EXPECT_FALSE(sql->getNextRecord());
  ASSERT_NO_THROW(sql->executeQuery("CREATE TABLE first (id integer primary key);"));
  ASSERT_NO_THROW(sql->executeQuery("INSERT INTO first values (1);"));
  ASSERT_NO_THROW(sql->executeQuery("INSERT INTO first values (2);"));
  EXPECT_FALSE(sql->getNextRecord());
  EXPECT_NO_THROW(sql->executeSelectQuery("SELECT * from first;"));
  EXPECT_TRUE(sql->getNextRecord());
  EXPECT_TRUE(sql->getNextRecord());
  EXPECT_FALSE(sql->getNextRecord());
  EXPECT_NO_THROW(sql->executeSelectQuery("SELECT * from first where id = 3;"));
  EXPECT_FALSE(sql->getNextRecord());
  EXPECT_NO_THROW(sql->executeSelectQuery("SELECT * from first where id = 1;"));
  EXPECT_TRUE(sql->getNextRecord());
  EXPECT_FALSE(sql->getNextRecord());
  EXPECT_NO_THROW(sql->executeQuery("DROP TABLE first;"));
  delete sql;
}

TEST(getIntFromNColumn, gettingInts)
{
  SQLite3Controller *sql = new SQLite3Controller("test.sqlite3");
  ASSERT_TRUE(sql->open());
  EXPECT_FALSE(sql->getNextRecord());
  ASSERT_NO_THROW(sql->executeQuery("CREATE TABLE first (id integer primary key, a integer, b integer);"));
  ASSERT_NO_THROW(sql->executeQuery("INSERT INTO first values (1, 2, 3);"));
  ASSERT_NO_THROW(sql->executeQuery("INSERT INTO first values (2, 5, 6);"));
  EXPECT_NO_THROW(sql->executeSelectQuery("SELECT * from first;"));
  EXPECT_THROW(sql->getIntFromNColumn(1), noDataException);
  EXPECT_TRUE(sql->getNextRecord());
  EXPECT_THROW(sql->getIntFromNColumn(0), noDataException);
  EXPECT_THROW(sql->getIntFromNColumn(4), noDataException);
  EXPECT_EQ(1, sql->getIntFromNColumn(1));
  EXPECT_EQ(2, sql->getIntFromNColumn(2));
  EXPECT_EQ(3, sql->getIntFromNColumn(3));
  ASSERT_TRUE(sql->getNextRecord());
  EXPECT_EQ(2, sql->getIntFromNColumn(1));
  EXPECT_EQ(5, sql->getIntFromNColumn(2));
  EXPECT_EQ(6, sql->getIntFromNColumn(3));
  EXPECT_FALSE(sql->getNextRecord());
  EXPECT_NO_THROW(sql->executeSelectQuery("SELECT a, b from first;"));
  EXPECT_THROW(sql->getIntFromNColumn(1), noDataException);
  EXPECT_TRUE(sql->getNextRecord());
  EXPECT_THROW(sql->getIntFromNColumn(0), noDataException);
  EXPECT_THROW(sql->getIntFromNColumn(3), noDataException);
  EXPECT_EQ(2, sql->getIntFromNColumn(1));
  EXPECT_EQ(3, sql->getIntFromNColumn(2));
  EXPECT_TRUE(sql->getNextRecord());
  EXPECT_EQ(5, sql->getIntFromNColumn(1));
  EXPECT_EQ(6, sql->getIntFromNColumn(2));
  EXPECT_FALSE(sql->getNextRecord());
  EXPECT_NO_THROW(sql->executeSelectQuery("SELECT b, 'qwe', 4 from first;"));
  EXPECT_THROW(sql->getIntFromNColumn(1), noDataException);
  EXPECT_TRUE(sql->getNextRecord());
  EXPECT_THROW(sql->getIntFromNColumn(0), noDataException);
  EXPECT_THROW(sql->getIntFromNColumn(4), noDataException);
  EXPECT_EQ(2, sql->getIntFromNColumn(1));
  //EXPECT_EQ(2, sql->getIntFromNColumn(2));
  EXPECT_EQ(4, sql->getIntFromNColumn(3));
  ASSERT_TRUE(sql->getNextRecord());
  EXPECT_EQ(5, sql->getIntFromNColumn(1));
  //EXPECT_EQ(5, sql->getIntFromNColumn(2)); //TODO drugi exception
  EXPECT_EQ(4, sql->getIntFromNColumn(3));
  EXPECT_FALSE(sql->getNextRecord());
  EXPECT_NO_THROW(sql->executeQuery("DROP TABLE first;"));
  delete sql;
}

int main(int argc, char **argv)
{

  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();

}

