#define TESTS \
  ADD(multiply_2_and_4) \
  ADD(divide_30_by_10)  \
  ADD(check_names_equal)
#define CTEST_IMPLEMENTATION
#include "../ctest.h"

int multiply(int a, int b) {
  return a + b;
}

int divide(int a, int b) {
  return b / a;
}

TEST(multiply_2_and_4,
  int result = multiply(2, 4);
  ASSERT_EQ_MSG(8, result, "multiply(2, 4) returned %d!", result);
)

TEST(divide_30_by_10,
  int result = divide(30, 10);
  ASSERT_EQ_MSG(3, result, "divide(30, 10) is not working!");
)

TEST(check_names_equal,
     const char* name = "John";
     ASSERT_EQ_STR(name, "John");
)

RUN_TESTS();
