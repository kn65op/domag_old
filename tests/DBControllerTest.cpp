/* 
 * File:   SQLite3ControllerTest.cpp
 * Author: tomko
 *
 * Created on 2011-11-17, 21:38:32
 */

#include <stdlib.h>
#include <iostream>
#include <tomko/Helper.h>
#include "../../gtest/gtest_src/include/gtest/gtest.h"
#include "../headers/DBController.h"


/**
 * DBController
 */

TEST(DBController, Konstruktor)
{
  DBController *sql = NULL;
  EXPECT_NO_THROW(sql = new DBController(""));
  delete sql;  
  EXPECT_NO_THROW(sql = new DBController("test.sqlite3"));
  delete sql;  
}

TEST(DBController, dropTables)
{
  DBController *sql = NULL;
  ASSERT_NO_THROW(sql = new DBController("test.sqlite3"));
  ASSERT_TRUE(sql->isValid());
  EXPECT_TRUE(sql->dropTables());
  EXPECT_TRUE(sql->createTables());
  EXPECT_TRUE(sql->dropTables());
  EXPECT_FALSE(sql->checkTables());
  delete sql;
}

TEST(DBController, createTables)
{
  DBController *sql = NULL;
  ASSERT_NO_THROW(sql = new DBController("test.sqlite3"));
  ASSERT_TRUE(sql->isValid());
  ASSERT_TRUE(sql->dropTables());
  EXPECT_TRUE(sql->createTables());
  EXPECT_FALSE(sql->createTables());
  EXPECT_TRUE(sql->dropTables());
  EXPECT_TRUE(sql->createTables());
  EXPECT_TRUE(sql->dropTables());
  delete sql;
}
TEST(DBController, checkTables)
{
  DBController *sql = NULL;
  ASSERT_NO_THROW(sql = new DBController("test.sqlite3"));
  ASSERT_TRUE(sql->dropTables());
  EXPECT_FALSE(sql->checkTables());
  ASSERT_TRUE(sql->createTables());
  EXPECT_TRUE(sql->checkTables());
  ASSERT_TRUE(sql->dropTables());
  EXPECT_FALSE(sql->checkTables());
  delete sql;
}
TEST(DBController, isValid)
{
  DBController *sql = NULL;
  ASSERT_NO_THROW(sql = new DBController("test.sqlite3"));
  EXPECT_TRUE(sql->isValid());
  delete sql;
  ASSERT_NO_THROW(sql = new DBController(""));
  EXPECT_FALSE(sql->isValid());
  delete sql;
}

int main(int argc, char **argv)
{

  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();

}

