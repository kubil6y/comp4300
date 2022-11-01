# C++ Programming Language - RAII

-   Resource Acquisition is Initialization
-   Binds the life cycle of a `resource` that must be acquired before use to the `lifetime of an object`
-   Makes life easier by implementing things in a way that `automatically manages memory` and resources within an object

## RAII Implementation

-   `Encapsulate` each resource into a class
-   The class constructor `acquires` the resource and initializes it accordingly
-   The destructor `releases` the resource
-   The class itself should be instantiated such that it has either automatic storage duration, or in another RAII object. RAII objects can be chained

```cpp
class IntArray
{
private:
  int* array;

public:
  IntArray(size_t size) { array = new int[size]; }
  ~IntArray() { delete[] array; }
  int& operator[](size_t i) { return array[i]; }
};


// We do not see any pointers
// Memory is managed by the InArray class
// When array goes out of scope, its destructor is called
int main()
{
    IntArray array(10); // mem allocated
    array[5] = 21;
    return 0;
} // arr destructs, mem deallocated 
```

NOTE: This is faster than java btw lel
