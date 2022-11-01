# C++ Programming Language - Smart Pointers

-   Can be cumbersome to create our own RAII classes for `every data type` we want to store a pointer to
-   C++ contains different `smart pointers`
-   In this class std::shared_ptr<T> will be used.
-   Handles RAII for a given pointer/type

NOTE: shared_ptr is not the most optimal solution. At the end of the course professor will go over optimization techniques.

## Shared Pointer

-   Also known as `Reference Counted Pointer`
-   `Internal counter` is set to 1 in constructor
-   Every time the shared_ptr is copied, the counter `increases` by 1
-   Every time the shared_ptr destructs, the counter `decreases` by 1
-   When the count reaches 0, resource `deallocated`

```cpp
#include <memory>

void func(std::shared_ptr<MyClass> p) // counter++, counter=2
{
    p->doSomething();
} // counter-- (counter=1)

int main()
{
    // Old Syntax for shared_ptr
    std::shared_ptr<MyClass> p(new MyClass(args)); // counter=1
    // New syntax (this will be used in this class)
    auto p = std::make_shared<MyClass>(args); // counter=1

    someOtherThings();

    return 0;
} // counter=0, deallocate
```
