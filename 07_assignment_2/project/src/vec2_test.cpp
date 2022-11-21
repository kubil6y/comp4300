#include "vec2_test.h"
#include "vec2.h"

#include <iostream>

#define IS_TRUE(x)                                                             \
    {                                                                          \
        if (!(x))                                                              \
            std::cout << "\t " << __FUNCTION__ << "\tfailed on line "          \
                      << __LINE__ << std::endl;                                \
        else                                                                   \
            std::cout << "\t " << __FUNCTION__ << "\tpassed" << std::endl;     \
    }

// TEST: bool operator==(const vec2& rhs) const;
void vec2_test1()
{
    vec2 v1 = vec2(1, 1);
    vec2 v2 = vec2(1, 1);
    IS_TRUE(v1 == v2);
};

// TEST: bool operator!=(const vec2& rhs) const;
void vec2_test2()
{
    vec2 v1 = vec2(1, 1);
    vec2 v2 = vec2(1, 1);
    IS_TRUE(!(v1 != v2));
};

// TEST: vec2 operator+(const vec2& rhs) const;
void vec2_test3()
{
    vec2 v1       = vec2(1, 1);
    vec2 v2       = vec2(1, 2);
    vec2 result   = v1 + v2;
    vec2 expected = vec2(2, 3);
    IS_TRUE(result == expected);
};

// TEST: vec2 operator-(const vec2& rhs) const;
void vec2_test4()
{
    vec2 v1       = vec2(1, 1);
    vec2 v2       = vec2(1, 2);
    vec2 result   = v1 - v2;
    vec2 expected = vec2(0, -1);
    IS_TRUE(result == expected);
};

// TEST: vec2 operator/(const vec2& rhs) const;
void vec2_test5()
{
    vec2 v1       = vec2(4, 6);
    vec2 v2       = vec2(2, 2);
    vec2 result   = v1 / v2;
    vec2 expected = vec2(2, 3);
    IS_TRUE(result == expected);
};

// TEST: vec2 operator*(const vec2& rhs) const;
void vec2_test6()
{
    vec2 v1       = vec2(1, 5);
    vec2 v2       = vec2(2, 2);
    vec2 result   = v1 * v2;
    vec2 expected = vec2(2, 10);
    IS_TRUE(result == expected);
};

// TEST: void operator+=(const vec2& rhs);
void vec2_test7()
{
    vec2 v1 = vec2(1, 5);
    vec2 v2 = vec2(2, 2);
    v1 += v2;
    vec2 expected = vec2(3, 7);
    IS_TRUE(v1 == expected);
};

// TEST: void operator-=(const vec2& rhs);
void vec2_test8()
{
    vec2 v1 = vec2(1, 5);
    vec2 v2 = vec2(2, 2);
    v1 -= v2;
    vec2 expected = vec2(-1, 3);
    IS_TRUE(v1 == expected);
};

// TEST: void operator/=(const vec2& rhs);
void vec2_test9()
{
    vec2 v1 = vec2(4, 10);
    vec2 v2 = vec2(2, 2);
    v1 /= v2;
    vec2 expected = vec2(2, 5);
    IS_TRUE(v1 == expected);
};

// TEST: void operator*=(const vec2& rhs);
void vec2_test10()
{
    vec2 v1 = vec2(1, 5);
    vec2 v2 = vec2(2, 3);
    v1 *= v2;
    vec2 expected = vec2(2, 15);
    IS_TRUE(v1 == expected);
};

// TEST: vec2  normalized() const;
void vec2_test11()
{
    vec2 v          = vec2(3, 4);
    vec2 normalized = v.normalized();
    vec2 expected   = vec2(0.6f, 0.8f);
    IS_TRUE(normalized == expected);
};

// TEST: void  normalizeInPlace();
void vec2_test12()
{
    vec2 v = vec2(3, 4);
    v.normalizeInPlace();
    vec2 expected = vec2(0.6f, 0.8f);
    IS_TRUE(v == expected);
};

// TEST: vec2 vec2::operator*(float s) const
void vec2_test13()
{
    vec2 v      = vec2(2, 3);
    vec2 result = v * 2;
    IS_TRUE(result == vec2(4, 6));
}

// TEST: vec2 vec2::operator/(float s) const
void vec2_test14()
{
    vec2 v      = vec2(2, 3);
    vec2 result = v / 2;
    IS_TRUE(result == vec2(1, 1.5f));
}

// TEST: void vec2::operator*=(float s)
void vec2_test15()
{
    vec2 v = vec2(2, 3);
    v *= 2;
    IS_TRUE(v == vec2(4, 6));
}

// TEST: void vec2::operator/=(float s)
void vec2_test16()
{
    vec2 v = vec2(2, 3);
    v /= 2;
    IS_TRUE(v == vec2(1, 1.5f));
}

// TEST: float dot(const vec2& lhs, const vec2& rhs)
void vec2_test17()
{
    vec2 right = vec2(1, 0);
    vec2 up    = vec2(0, 1);
    IS_TRUE(dot(right, up) == 0);
}

// TEST: float dist(const vec2& rhs) const;
void vec2_test18()
{
    vec2 v = vec2(0, 0);
    float distance = v.dist(vec2(3, 4));
    IS_TRUE(distance == 5);
}

void vec2_test_run()
{
    std::cout << "vec2_h tests:" << std::endl;
    vec2_test1();
    vec2_test2();
    vec2_test3();
    vec2_test4();
    vec2_test5();
    vec2_test6();
    vec2_test7();
    vec2_test8();
    vec2_test9();
    vec2_test10();
    vec2_test11();
    vec2_test12();
    vec2_test13();
    vec2_test14();
    vec2_test15();
    vec2_test16();
    vec2_test17();
    vec2_test18();
}
