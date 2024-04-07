# ctest.h - a simple single header testing library for C

## Usuage:
1. Copy the file from [](https://github.com/AineeJames/ctest.h/blob/main/ctest.h) into your project.
2. Create a file called `test.c` and include the following contents at the top:
    ```c
    #define TESTS \
        ADD(test_name_1) \
        ADD(test_name_2)
    #define CTEST_IMPLEMENTATION
    #include "ctest.h"
    ```

