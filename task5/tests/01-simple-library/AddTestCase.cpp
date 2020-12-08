//
// Created by akhtyamovpavel on 5/1/20.
//

#include "AddTestCase.h"
#include "Functions.h"

TEST(AddTestCase, TwoPlusTwo) {
  ASSERT_EQ(4, Add(2, 2));
}

TEST(AddTestCase, ZeroPlusOne) {
  ASSERT_EQ(1, Add(0, 1));
}

TEST(AddTestCase, FivePlusMinusFive) {
  ASSERT_EQ(0, Add(5, -5));
}
