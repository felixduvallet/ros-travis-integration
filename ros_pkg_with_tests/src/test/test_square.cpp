#include "square.h"
#include <gtest/gtest.h>

TEST(TestSuite, squareTwo)
{
  const double ret = square(2);
  ASSERT_EQ(4, ret);
}

TEST(TestSuite, squareFour)
{
  const double ret = square(4.1);
  ASSERT_EQ(16.81, ret);
}

// Run all the tests that were declared with TEST()
int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
