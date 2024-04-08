#define TESTS \
  ADD(should_fail) \
  ADD(should_pass) \
  ADD(string_check_fail)
#define CTEST_IMPLEMENTATION
#include "../ctest.h"

TEST(should_fail,
  ASSERT_EQ_MSG(3 + 7, 1 + 2, "Ten does not equal three!");
)

TEST(should_pass,
  ASSERT_EQ(2 + 3, 5);
)

TEST(string_check_fail,
  ASSER_EQ_STR_MSG("John", "Jane", "John and Jane are not the same name!");
)

RUN_TESTS();
