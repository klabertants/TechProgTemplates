//
// Created by akhtyamovpavel on 5/1/20.
//

#include "LeapTestCase.h"

#include <Functions.h>

TEST(LeapTestCase, TwoThousandIsLeap) {
  EXPECT_TRUE(IsLeap(2000));
}

TEST(LeapTestCase, SeventeenHundredIsNotLeap) {
  EXPECT_FALSE(IsLeap(1700));
}

TEST(LeapTestCase, TwoThousandFourIsLeap) {
  EXPECT_TRUE(IsLeap(2004));
}

TEST(LeapTestCase, MyBirthYearIsNotLeap) {
  EXPECT_FALSE(IsLeap(1997));
}

TEST(LeapTestCase, ExceptionOnInvalidYear) {
  ASSERT_THROW(IsLeap(-1000), std::invalid_argument);
}
