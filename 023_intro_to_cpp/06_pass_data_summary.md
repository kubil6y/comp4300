# How to allocate / pass data?

1. If possible, use the stack
    - Small, local variables
    - Pass variables by const reference if size > 8 bytes
2. If you need heap memory, use smart ptr
    - std::shared_ptr<T> myBigData;
    - std::shared_ptr<Base> = std::make_shared<Derived>();
3. Only when **absolutely necessary** use raw pointers and new
    - Hopefully this should not happen in this course
