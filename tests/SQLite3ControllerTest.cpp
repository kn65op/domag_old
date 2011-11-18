/* 
 * File:   SQLite3ControllerTest.cpp
 * Author: tomko
 *
 * Created on 2011-11-17, 21:38:32
 */

#include <stdlib.h>
#include <iostream>
#include "../headers/SQLite3Controller.h"
#include "../headers/Helper.h"
#include "gtest/gtest.h"

/**
 * SQLiteController
 */
TEST(SQLiteControllerTestConstructor, StringConstructor)
{
  SQLite3Controller *sql = new SQLite3Controller("a");
  EXPECT_FALSE(sql->isOpened());
  delete sql;
  sql = new SQLite3Controller("");
  EXPECT_FALSE(sql->isOpened());
  delete sql;
}

TEST(open, ValidDatabases)
{
  SQLite3Controller *sql = new SQLite3Controller("test.sqlite3");
  EXPECT_TRUE(sql->open());
  delete sql;
}

TEST(open, InvalidDatabases)
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
  EXPECT_NO_THROW(sql->executeQuery("DROP TABLE if exists first;"));
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
  EXPECT_THROW(sql->getIntFromNColumn(0), NoDataException);
  EXPECT_TRUE(sql->getNextRecord());
  EXPECT_THROW(sql->getIntFromNColumn(-1), NoDataException);
  EXPECT_THROW(sql->getIntFromNColumn(3), NoDataException);
  EXPECT_EQ(1, sql->getIntFromNColumn(0));
  EXPECT_EQ(2, sql->getIntFromNColumn(1));
  EXPECT_EQ(3, sql->getIntFromNColumn(2));
  ASSERT_TRUE(sql->getNextRecord());
  EXPECT_EQ(2, sql->getIntFromNColumn(0));
  EXPECT_EQ(5, sql->getIntFromNColumn(1));
  EXPECT_EQ(6, sql->getIntFromNColumn(2));
  EXPECT_FALSE(sql->getNextRecord());
  EXPECT_NO_THROW(sql->executeSelectQuery("SELECT a, b from first;"));
  EXPECT_THROW(sql->getIntFromNColumn(0), NoDataException);
  EXPECT_TRUE(sql->getNextRecord());
  EXPECT_THROW(sql->getIntFromNColumn(-1), NoDataException);
  EXPECT_THROW(sql->getIntFromNColumn(2), NoDataException);
  EXPECT_EQ(2, sql->getIntFromNColumn(0));
  EXPECT_EQ(3, sql->getIntFromNColumn(1));
  EXPECT_TRUE(sql->getNextRecord());
  EXPECT_EQ(5, sql->getIntFromNColumn(0));
  EXPECT_EQ(6, sql->getIntFromNColumn(1));
  EXPECT_FALSE(sql->getNextRecord());
  EXPECT_NO_THROW(sql->executeSelectQuery("SELECT b, 'qwe', 4, 5.5 from first;"));
  EXPECT_THROW(sql->getIntFromNColumn(0), NoDataException);
  EXPECT_TRUE(sql->getNextRecord());
  EXPECT_THROW(sql->getIntFromNColumn(-1), NoDataException);
  EXPECT_THROW(sql->getIntFromNColumn(3), WrongDataException);
  EXPECT_THROW(sql->getIntFromNColumn(4), NoDataException);
  EXPECT_EQ(3, sql->getIntFromNColumn(0));
  EXPECT_THROW(sql->getIntFromNColumn(1), WrongDataException);
  EXPECT_EQ(4, sql->getIntFromNColumn(2));
  EXPECT_TRUE(sql->getNextRecord());
  EXPECT_THROW(sql->getIntFromNColumn(-1), NoDataException);
  EXPECT_THROW(sql->getIntFromNColumn(3), WrongDataException);
  EXPECT_THROW(sql->getIntFromNColumn(4), NoDataException);
  EXPECT_EQ(6, sql->getIntFromNColumn(0));
  EXPECT_THROW(sql->getIntFromNColumn(1), WrongDataException);
  EXPECT_EQ(4, sql->getIntFromNColumn(2));
  EXPECT_FALSE(sql->getNextRecord());
  EXPECT_NO_THROW(sql->executeQuery("DROP TABLE first;"));
  delete sql;
}

TEST(getStringFromNColumn, gettingStrings)
{
  SQLite3Controller *sql = new SQLite3Controller("test.sqlite3");
  ASSERT_TRUE(sql->open());
  EXPECT_FALSE(sql->getNextRecord());
  ASSERT_NO_THROW(sql->executeQuery("CREATE TABLE first (id integer primary key, a text, b text);"));
  ASSERT_NO_THROW(sql->executeQuery("INSERT INTO first values (1, '123', 'qwe');"));
  ASSERT_NO_THROW(sql->executeQuery("INSERT INTO first values (2, '456', 'asd');"));
  EXPECT_NO_THROW(sql->executeSelectQuery("SELECT * from first;"));
  EXPECT_THROW(sql->getStringFromNColumn(0), NoDataException);
  EXPECT_TRUE(sql->getNextRecord());
  EXPECT_THROW(sql->getStringFromNColumn(-1), NoDataException);
  EXPECT_THROW(sql->getStringFromNColumn(3), NoDataException);
  EXPECT_STREQ("123", sql->getStringFromNColumn(1).c_str());
  EXPECT_STREQ("qwe", sql->getStringFromNColumn(2).c_str());
  ASSERT_TRUE(sql->getNextRecord());
  EXPECT_STREQ("456", sql->getStringFromNColumn(1).c_str());
  EXPECT_STREQ("asd", sql->getStringFromNColumn(2).c_str());
  EXPECT_FALSE(sql->getNextRecord());
  EXPECT_NO_THROW(sql->executeSelectQuery("SELECT a, b from first;"));
  EXPECT_THROW(sql->getStringFromNColumn(0), NoDataException);
  EXPECT_TRUE(sql->getNextRecord());
  EXPECT_THROW(sql->getStringFromNColumn(-1), NoDataException);
  EXPECT_THROW(sql->getStringFromNColumn(2), NoDataException);
  EXPECT_STREQ("123", sql->getStringFromNColumn(0).c_str());
  EXPECT_STREQ("qwe", sql->getStringFromNColumn(1).c_str());
  EXPECT_TRUE(sql->getNextRecord());
  EXPECT_STREQ("456", sql->getStringFromNColumn(0).c_str());
  EXPECT_STREQ("asd", sql->getStringFromNColumn(1).c_str());
  EXPECT_FALSE(sql->getNextRecord());
  EXPECT_NO_THROW(sql->executeSelectQuery("SELECT b, 'qwe', 4, 5.5 from first;"));
  EXPECT_THROW(sql->getStringFromNColumn(0), NoDataException);
  EXPECT_TRUE(sql->getNextRecord());
  EXPECT_THROW(sql->getStringFromNColumn(-1), NoDataException);
  EXPECT_THROW(sql->getStringFromNColumn(3), WrongDataException);
  EXPECT_THROW(sql->getStringFromNColumn(4), NoDataException);
  EXPECT_STREQ("qwe", sql->getStringFromNColumn(0).c_str());
  EXPECT_THROW(sql->getStringFromNColumn(2), WrongDataException);
  EXPECT_STREQ("qwe", sql->getStringFromNColumn(1).c_str());
  EXPECT_TRUE(sql->getNextRecord());
  EXPECT_THROW(sql->getStringFromNColumn(-1), NoDataException);
  EXPECT_THROW(sql->getStringFromNColumn(3), WrongDataException);
  EXPECT_THROW(sql->getStringFromNColumn(4), NoDataException);
  EXPECT_STREQ("asd", sql->getStringFromNColumn(0).c_str());
  EXPECT_THROW(sql->getStringFromNColumn(2), WrongDataException);
  EXPECT_STREQ("qwe", sql->getStringFromNColumn(1).c_str());
  EXPECT_FALSE(sql->getNextRecord());
  EXPECT_NO_THROW(sql->executeQuery("DROP TABLE first;"));
  delete sql;
}

TEST(getDoubleFromNColumn, gettingInts)
{
  SQLite3Controller *sql = new SQLite3Controller("test.sqlite3");
  ASSERT_TRUE(sql->open());
  EXPECT_FALSE(sql->getNextRecord());
  ASSERT_NO_THROW(sql->executeQuery("CREATE TABLE first (id float primary key, a float, b float);"));
  ASSERT_NO_THROW(sql->executeQuery("INSERT INTO first values (1.1, 0.2, 3.0);"));
  ASSERT_NO_THROW(sql->executeQuery("INSERT INTO first values (2.5, 0.05, 6.0);"));
  EXPECT_NO_THROW(sql->executeSelectQuery("SELECT * from first;"));
  EXPECT_THROW(sql->getDoubleFromNColumn(0), NoDataException);
  EXPECT_TRUE(sql->getNextRecord());
  EXPECT_THROW(sql->getDoubleFromNColumn(-1), NoDataException);
  EXPECT_THROW(sql->getDoubleFromNColumn(3), NoDataException);
  EXPECT_EQ(1.1, sql->getDoubleFromNColumn(0));
  EXPECT_EQ(0.2, sql->getDoubleFromNColumn(1));
  EXPECT_EQ(3.0, sql->getDoubleFromNColumn(2));
  ASSERT_TRUE(sql->getNextRecord());
  EXPECT_EQ(2.5, sql->getDoubleFromNColumn(0));
  EXPECT_EQ(0.05, sql->getDoubleFromNColumn(1));
  EXPECT_EQ(6.0, sql->getDoubleFromNColumn(2));
  EXPECT_FALSE(sql->getNextRecord());
  EXPECT_NO_THROW(sql->executeSelectQuery("SELECT a, b from first;"));
  EXPECT_THROW(sql->getDoubleFromNColumn(0), NoDataException);
  EXPECT_TRUE(sql->getNextRecord());
  EXPECT_THROW(sql->getDoubleFromNColumn(-1), NoDataException);
  EXPECT_THROW(sql->getDoubleFromNColumn(2), NoDataException);
  EXPECT_EQ(0.2, sql->getDoubleFromNColumn(0));
  EXPECT_EQ(3.0, sql->getDoubleFromNColumn(1));
  EXPECT_TRUE(sql->getNextRecord());
  EXPECT_EQ(0.05, sql->getDoubleFromNColumn(0));
  EXPECT_EQ(6.0, sql->getDoubleFromNColumn(1));
  EXPECT_FALSE(sql->getNextRecord());
  EXPECT_NO_THROW(sql->executeSelectQuery("SELECT a, 'qwe', 5.5, 4 from first;"));
  EXPECT_THROW(sql->getDoubleFromNColumn(0), NoDataException);
  EXPECT_TRUE(sql->getNextRecord());
  EXPECT_THROW(sql->getDoubleFromNColumn(-1), NoDataException);
  EXPECT_THROW(sql->getDoubleFromNColumn(3), WrongDataException);
  EXPECT_THROW(sql->getDoubleFromNColumn(4), NoDataException);
  EXPECT_EQ(0.2, sql->getDoubleFromNColumn(0));
  EXPECT_THROW(sql->getDoubleFromNColumn(1), WrongDataException);
  EXPECT_EQ(5.5, sql->getDoubleFromNColumn(2));
  EXPECT_TRUE(sql->getNextRecord());
  EXPECT_THROW(sql->getDoubleFromNColumn(-1), NoDataException);
  EXPECT_THROW(sql->getDoubleFromNColumn(3), WrongDataException);
  EXPECT_THROW(sql->getDoubleFromNColumn(4), NoDataException);
  EXPECT_EQ(0.05, sql->getDoubleFromNColumn(0));
  EXPECT_THROW(sql->getDoubleFromNColumn(1), WrongDataException);
  EXPECT_EQ(5.5, sql->getDoubleFromNColumn(2));
  EXPECT_FALSE(sql->getNextRecord());
  EXPECT_NO_THROW(sql->executeQuery("DROP TABLE first;"));
  delete sql;
}

/**
 * Helper
 */
TEST(intToString, one)
{
  EXPECT_STREQ("1", Helper::intToString(1).c_str());
  EXPECT_STREQ("-1", Helper::intToString(-1).c_str());
  EXPECT_STREQ("234", Helper::intToString(234).c_str());
  EXPECT_STREQ("-234", Helper::intToString(-234).c_str());
  EXPECT_STREQ("5", Helper::intToString(5.6).c_str());
  EXPECT_STREQ("3", Helper::intToString(3.4).c_str());
  EXPECT_STREQ("0", Helper::intToString(-0).c_str());
  EXPECT_STREQ("-1", Helper::intToString(-1.1).c_str());
  EXPECT_STREQ("-2", Helper::intToString(-2.6).c_str());
}

int main(int argc, char **argv)
{

  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();

}

