# ctest.h - a simple single header testing library for C

## 📝 Description:
ctest.h is a simple, single-header C library designed to streamline unit testing for C
projects. The library offers developers an efficient way to define and execute tests within the same environment
(no need for overyly complicated build systems). Its header-only nature makes ctest.h exceptionally easy to
integrate into any existing project, providing a straightforward and effective tool for ensuring code reliability
and correctness.

## 🛠️ Usage:
1. Copy [ctest.h](https://github.com/AineeJames/ctest.h/blob/main/ctest.h) into your project.
2. Create a file called `test.c` and include the following contents at the top:
    ```c
    #define TESTS \
        ADD(multiply_2_and_4) \
        ADD(divide_30_by_10)  \
        ADD(check_names_equal)
    #define CTEST_IMPLEMENTATION
    #include "../ctest.h"
    ```
3. Define some functions to test (these have mistakes for demonstration purposes):
    ```c
    int multiply(int a, int b) { return a + b; }
    int divide(int a, int b) { return b / a; }
    ```
4. Define `multiply_2_and_4`,`divide_30_by_10`, and `check_names_equal`:
    ```c
    TEST(multiply_2_and_4, /* This test will FAIL */
        int result = multiply(2, 4);
        ASSERT_EQ_MSG(8, result, "multiply(2, 4) returned %d!", result);
    )

    TEST(divide_30_by_10, /* This test will also FAIL */
        int result = divide(30, 10);
        ASSERT_EQ_MSG(3, result, "divide(30, 10) is not working!");
    )

    TEST(check_names_equal, /* This test will PASS */
         const char* name = "John";
         ASSERT_EQ_STR(name, "John");
    )
    ```
5. Add entry point for tests at the bottome of the file:
    ```c
    RUN_TESTS();
    ```
6. Build and execute tests:
    ```shell
    gcc -o test test.c
    ./test
    ```

## 💻 Example Output:
```shell
~/dev/c/ctest/examples (main) » ./test
INFO: Running a total of 3 tests.

test.c:test_multiply_2_and_4():18: Assertion of '(8) == (result)' failed: multiply(2, 4) returned 6!
❌ Test multiply_2_and_4 failed 1 assertions!
test.c:test_divide_30_by_10():23: Assertion of '(3) == (result)' failed: divide(30, 10) is not working!
❌ Test divide_30_by_10 failed 1 assertions!
✅ Test check_names_equal passed.

    Tests  2 failed | 1 passed (3)
 Start at  15:32:47
 Duration  0s
```

## 📜 Available Macros:
- `ASSERT(condition)`:   Fails when `condition == false`.
- `ASSERT_EQ(a, b)`:     Fails when `a != b`.
- `ASSERT_EQ_STR(a, b)`: Fails when `strcmp(a, b) != 0`.

> [!NOTE]  
> Adding `_MSG` to the end of any of the macros allows you to provide a message when the assertion occours.
> ```c
> ASSERT_EQ_STR_MSG("John", "Jane", "Names do not match!");
> /* or */
> int num = 3;
> ASSERT_EQ_MSG(2, num, "2 != %d", num);
> ```
