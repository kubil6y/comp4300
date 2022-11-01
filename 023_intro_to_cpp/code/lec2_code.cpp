#include <iostream>

template <typename T>
class DynamicArray
{
private:
    size_t m_size;
    T*     m_array;

public:
    DynamicArray(size_t size) : m_size(size), m_array(new T[size])
    {
        std::cout << "DynamicArray Constructor" << std::endl;
    }

    ~DynamicArray()
    {
        std::cout << "DynamicArray Destructor" << std::endl;
        delete[] m_array;
    }

    const T& operator[](size_t index) const
    {
        return m_array[index];
    }

    T& operator[](size_t index)
    {
        return m_array[index];
    }
};

int main()
{
    DynamicArray<int> arr(5);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    arr[3] = 40;
    arr[4] = 50;

    std::cout << arr[3] << std::endl;
    return 0;
}
