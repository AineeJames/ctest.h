#ifndef CTEST_H
#define CTEST_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CTEST_GRY "\e[0;37m"
#define CTEST_GRYB "\e[1;37m"
#define CTEST_RED "\e[1;31m"
#define CTEST_GRN "\e[1;32m"
#define CTEST_RST "\e[0m"

// ASSERTIONS
#define ASSERT(condition)                                                      \
  failed_assertions += !ctest__assert((condition), #condition, __FILE__,       \
                                      __FUNCTION__, __LINE__, "")              \
                           ? 1                                                 \
                           : 0
#define ASSERT_MSG(condition, msg, ...)                                        \
  failed_assertions +=                                                         \
      !ctest__assert((condition), #condition, __FILE__, __FUNCTION__,          \
                     __LINE__, msg, ##__VA_ARGS__)                             \
          ? 1                                                                  \
          : 0
#define ASSERT_EQ(a, b) ASSERT((a) == (b))
#define ASSERT_EQ_MSG(a, b, msg, ...) ASSERT_MSG((a) == (b), msg, ##__VA_ARGS__)
#define ASSERT_EQ_STR(a, b) ASSERT(strcmp((a), (b)) == 0)
#define ASSERT_EQ_STR_MSG(a, b, msg, ...)                                      \
  ASSERT_MSG(strcmp((a), (b)) == 0, msg, ##__VA_ARGS__)

// TESTS
#define TEST(name, ...)                                                        \
  static int test_##name(void) {                                               \
    int failed_assertions = 0;                                                 \
    __VA_ARGS__ return failed_assertions;                                      \
  }
#define RUN_TESTS()                                                            \
  int main(void) { return ctest__run_tests() ? 0 : 1; }

static bool ctest__assert(bool result, const char *expression, const char *file,
                          const char *test_name, const int line,
                          const char *msg, ...);
static bool ctest__run_tests();
static char *ctest__get_timestamp(void);
#define ADD(name) static int test_##name(void);
#ifdef TESTS
TESTS
#endif // !TESTS
#undef ADD

// #define CTEST_IMPLEMENTATION
#ifdef CTEST_IMPLEMENTATION

static bool ctest__assert(bool result, const char *expression, const char *file,
                          const char *test_name, const int line,
                          const char *msg, ...) {
  if (result) {
    return true;
  } else {
    fprintf(stderr, "%s:%s:%d: Assertion of '%s' failed: ", file, test_name,
            line, expression);
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    fprintf(stderr, "\n");
    return false;
  }
}

static bool ctest__run_tests() {
#ifndef TESTS
#define TESTS // Defined to omit useless warnings when compiling
  fprintf(stderr, "ERROR: No tests are defined!\n");
  exit(1);
#endif // !TESTS

  int test_count = 0;
#define ADD(name) test_count++;
  TESTS
#undef ADD
  printf(CTEST_GRY "INFO: Running a total of %d tests.\n\n", test_count);

  int fail_test_count = 0;
  int failed_assertions = 0;
  time_t start_time = time(NULL);
  // #define ADD(name) fail_test_count += test_##name() ? 1 : 0;
#define ADD(name)                                                              \
  failed_assertions = test_##name();                                           \
  if (failed_assertions > 0) {                                                 \
    fprintf(stderr,                                                            \
            "❌ Test " CTEST_GRYB "%s" CTEST_GRY " failed %d assertions!\n",   \
            #name, failed_assertions);                                         \
    fail_test_count++;                                                         \
  } else {                                                                     \
    fprintf(stderr, "✅ Test " CTEST_GRYB "%s" CTEST_GRY " passed.\n", #name); \
  }
  TESTS
#undef ADD
  time_t end_time = time(NULL);

  printf("\n");
  int pass_test_count = test_count - fail_test_count;
  printf(CTEST_GRY "    Tests  " CTEST_RED "%d failed" CTEST_GRY " | " CTEST_GRN
                   "%d passed" CTEST_GRY " (%d)\n" CTEST_RST,
         fail_test_count, pass_test_count, test_count);
  printf(CTEST_GRY " Start at  " CTEST_RST "%s\n", ctest__get_timestamp());
  printf(CTEST_GRY " Duration  " CTEST_RST "%lds\n", end_time - start_time);
  if (fail_test_count > 0)
    return false;
  return true;
}

static char *ctest__get_timestamp() {
  time_t rawtime;
  struct tm *timeinfo;

  char *buffer = (char *)malloc(9 * sizeof(char)); // HH:MM:SS + null terminator
  if (buffer == NULL) {
    fprintf(stderr, "ERROR: Could not allocate memory for timestamp!\n");
    exit(1);
  }

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  strftime(buffer, 9, "%H:%M:%S", timeinfo);

  return buffer;
}

#endif // !CTEST_IMPLEMENTATION

#endif // !CTEST_H
