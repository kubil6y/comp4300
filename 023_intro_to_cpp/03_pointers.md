# C++ Programming Language - Pointers

-   Same as pointers in C
-   A pointer stores a `memory address`
-   Modifying the `pointer variable` modifies the `address` it points to
-   To modify the value of the data in memory that it points to, we `dereference`
-   `Raw pointers` can be `very unsafe`.
    -   _Row pointers allow you to modify anything at any time_

```cpp
int main()
{
    int i = 6; // local int var
    // Here the value of p in stack is undefined.
    // *p gets the value of whatever in the memory
    // This is why raw pointers are very dangerous
    // Always initialize pointers with a value.
    int* p;  // pointer to int
    p  = &i; // & = `address of`
    *p = 88; // * = `dereference`
    return 0;
}
```

## Arrays / Pointers

Dynamic arrays are just pointers.

```cpp
int staticArray[COMPILETIME_VALUE];         // stack
int* dynamicArray = new int[RUNTIME_VALUE]; // heap
```

```cpp
int* arr   = new int[3];
arr[0]     = 10;
arr[1]     = 20;
*(arr + 2) = 30; // pointer math

// These statements are identical
// arr[n]    = *(arr + n)
// n[arr]    = *(n + arr)
// (arr + n) = &(arr[n])
```

### Why use pointers?

-   Must use pointer for `inheritance`
    ```cpp
    Base* ptr = new Derived();
    ```
-   Pass by `value` vs. by `reference`
    -   Modifying variable passed into function
-   Pointing to `large` data
    -   Large data can't live on the stack

Be careful **Pointers may be null**

## C++ References

-   References are essentially `safe pointers`
-   Instead of \*, use &
-   A reference `MUST` point to `existing` data, and can `never` point to nothing/nullptr
    -   This makes them _almost_ always safe
-   References can not be rebound to another addresses
-   `Prefer` using reference to pointers wherever possible in our code

### Pass By Value / Reference

-   By default, C++ pass variables by `value`
-   PBVal has a `cost for copying` large data
-   Also, may want to `modify` the value passed
-   We can use pointers to accomplish PBRef, but ideally we want to use `references`

### Pass by const reference

-   Whenever we pass a variable to a function that we don't want to be modified, use a `const reference`
-   const declares that the variable `cannot be modified` inside the called function
-   We only have to pass the 8-byte reference, which may be `far less data` then the data we are passing into the function

### Pass by const reference exceptions

-   Pass `primitive` data types by `value`
    -   ~~int add(const int& a, const int& b);~~
    -   int add(int a, int b);
-   Referencing has an extra `dereference` step which is slower when using primitives
-   Pass `std::shared_ptr<T>` by value
    -   Copy constructor does counter inc/dec
