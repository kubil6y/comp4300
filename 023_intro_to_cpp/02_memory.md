# C++ Programming Language - Memory

-   Two different types of memory in C++
    -   Stack Memory
    -   Heap Memory
-   When program is launched, OS gives it `access` to a number of areas of memory
-   The main two that we can manipulate are the `stack` and `heap` memory
-   Both stack and heap stored in RAM, difference is determined by the OS when program runs

## Stack/Heap Memory

-   At a basic level, both just `store data`
-   We `request` an amount of memory from either stack or heap, it gives it to us
-   The main differences are:
    -   The size of available memory (Heap has a lot more memory)
    -   The way memory is found/allocated
    -   The speed of memory allocation (Stack is way faster in general)
    -   The way we request memory in our code
    -   Stack memory deallocated when leaves scope

```cpp
int main()
{
    int val   = 5;       // stack
    int* hval = new int; // heap
    *hval     = 5;

    int arr[5];             // stack
    int* harr = new int[5]; // heap
    harr[3]   = 10;

    MyClass c(args);                 // stack
    MyClass* hc = new MyClass(args); // heap

    delete hval;
    delete[] harr;
    delete hc;
    hval = nullptr;
    harr = nullptr;
    hc = nullptr;

    return 0;
}
```

## Stack Memory

-   Has `predefined` size (few megabytes)
-   Very easy to `run out` of stack memory
-   Local variables without `new` are allocated on the stack by `default`
-   Program function calls/return `addresses` are also allocated on the stack
-   Stack known as `static memory`
    -   Predefined memory
    -   Can not to dynamic memory allocation
-   All stack memory allocation sizes need to be known at `COMPILE TIME`
-   Memory allocation which depends on `runtime` variables (dynamic memory size) must be `heap` allocated.

## Heap Memory

-   Much `more` space available than stack
-   Allocation via the `new` keyword
    ```cpp
    Type* varName = new Type;
    ```
-   Calls C function `malloc` under the hood
-   Operating system finds a contiguous chunk of memory and returns a pointer to it
    -   **This is very complicated and expensive**
-   You then access the memory via pointer

## Just Remember

-   Stack : `Fast` and `Limited`
-   Heap  : `Slow` and `Larger`
