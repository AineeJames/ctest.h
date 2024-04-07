# ctest.h - a simple single header testing library for C

## Usuage:
1. Copy [ctest.h](https://github.com/AineeJames/ctest.h/blob/main/ctest.h) into your project.
2. Create a file called `test.c` and include the following contents at the top:
    ```c
    #define TESTS \
        ADD(test_example_1) \
        ADD(test_example_2)
    #define CTEST_IMPLEMENTATION
    #include "ctest.h"
    ```
3. Define `test_example_1` and `test_example_2`:
    ```c
    // This test will fail
    TEST(test_example_1,
        int i = 1;
        ASSERT(i == 10);
    )

    // This test will pass
    TEST(test_example_1,
        ASSERT(2 + 3 == 5);
    )
    ```
4. Add entry point for tests:
    ```c
    RUN_TESTS();
    ```
5. Build and execute tests:
    ```shell
    gcc -o test test.c
    ./test
    ```

## Example Output:
```shell
~/dev/c/ctest/examples (main*) » ./test
INFO: Running a total of 2 tests.

test.c:test_should_fail():9 Assertion of 'i == 11' failed!
❌ Test should_fail failed 1 assertions!
✅ Test should_pass passed.

    Tests  1 failed | 1 passed (2)
 Start at  16:56:26
 Duration  0s
```

