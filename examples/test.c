#define TESTS \
  ADD(should_fail) \
  ADD(should_pass)
#define CTEST_IMPLEMENTATION
#include "../ctest.h"

TEST(should_fail,
  int i = 10;
  ASSERT(i == 11);
)

TEST(should_pass,
  ASSERT(2 + 3 == 5);
)

RUN_TESTS();
