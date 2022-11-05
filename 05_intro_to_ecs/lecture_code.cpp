#include <cmath>
#include <iostream>

class Vec2
{
public:
    float x = 0;
    float y = 0;
    Vec2()  = default;
    Vec2(float x, float y) : x(x), y(y) {}

    Vec2  operator+(const Vec2& v) const;
    void  operator+=(const Vec2& v);
    Vec2& add(const Vec2& v);
    Vec2& scale(float s);
    Vec2& rotate(float radians);
    float dist(const Vec2& v) const;

    friend std::ostream& operator<<(std::ostream& os, const Vec2& v);
};

Vec2 Vec2::operator+(const Vec2& v) const { return Vec2(x + v.x, y + v.y); }

void Vec2::operator+=(const Vec2& v)
{
    x += v.x;
    y += v.y;
}

std::ostream& operator<<(std::ostream& os, const Vec2& v)
{
    std::cout << '(' << v.x << ',' << v.y << ')';
    return os;
}

Vec2& Vec2::add(const Vec2& v)
{
    x += v.x;
    y += v.y;
    return *this;
}

Vec2& Vec2::scale(float scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vec2& Vec2::rotate(float radians)
{
    // will be implemented later
    return *this;
}

float Vec2::dist(const Vec2& v) const
{
    return sqrtf((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y));
}

int main()
{
    Vec2 v1(100, 200);
    Vec2 v2(50, 75);
    Vec2 v3(3, 4);
    Vec2 zero(0, 0);

    float dist = v3.dist(zero);

    // Vec2 v3 = v1 + v2;
    // v3 += (v1 + v2);
    // v1 += v2;

    // v3.add(v1).add(v2).scale(.01f).rotate(3.14f / 2);

    std::cout << dist << std::endl; // 5
    std::cout << v3 << std::endl;
    return 0;
}
