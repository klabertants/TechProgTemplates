//
// Created by akhtyamovpavel on 5/1/20.
//


#include "TreeTestCase.h"
#include "Tree.h"

#include <boost/filesystem.hpp>
#include "boost/filesystem/fstream.hpp"

const std::string MAIN_TEST_PATH = "TreeTestCaseTestDirectory";

FileNode createTestDirectory(const std::string& MAIN_PATH, const bool dirs_only)
{
  boost::filesystem::create_directory(MAIN_PATH);

  FileNode answer;
  answer.name = boost::filesystem::path(MAIN_PATH).filename().string();
  answer.is_dir = true;

  const std::string FILE_PATH = MAIN_PATH + "/" + "file.txt";
  boost::filesystem::ofstream file(FILE_PATH);
  file << "Just for test :)";
  file.close();

  if (!dirs_only) {
    answer.children.push_back(
      { boost::filesystem::path(FILE_PATH).filename().string(), false, {} }
    );
  }

  const std::string SUBDIR_PATH = MAIN_PATH + "/" + "test";

  boost::filesystem::create_directory(SUBDIR_PATH);
  FileNode subdir;
  subdir.name = boost::filesystem::path(SUBDIR_PATH).filename().string();
  subdir.is_dir = true;

  answer.children.push_back(subdir);

  return answer;
}

TEST(TreeTestCase, PathNotExist) {
  ASSERT_THROW(GetTree("5top100", true), std::invalid_argument);
}

TEST(TreeTestCase, PathIsNotADirectory) {
  ASSERT_THROW(GetTree("Makefile", true), std::invalid_argument);
}

TEST(TreeTestCase, TestDirsOnly) {
  const auto answer = createTestDirectory(MAIN_TEST_PATH, true);

  ASSERT_EQ(GetTree(MAIN_TEST_PATH, true), answer);

  boost::filesystem::remove_all(MAIN_TEST_PATH);
}

TEST(TreeTestCase, TestNotDirsOnly) {
  const auto answer = createTestDirectory(MAIN_TEST_PATH, false);

  ASSERT_EQ(GetTree(MAIN_TEST_PATH, false), answer);

  boost::filesystem::remove_all(MAIN_TEST_PATH);
}
