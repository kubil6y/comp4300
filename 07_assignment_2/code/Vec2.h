#ifndef VEC2_H
#define VEC2_H

class Vec2
{
public:
    float x = 0;
    float y = 0;

    Vec2() = default;
    Vec2(float x, float y);

    bool operator==(const Vec2& rhs) const;
    bool operator!=(const Vec2& rhs) const;

    Vec2 operator+(const Vec2& rhs) const;
    Vec2 operator-(const Vec2& rhs) const;
    Vec2 operator/(const Vec2& rhs) const;
    Vec2 operator*(const Vec2& rhs) const;

    void operator+=(const Vec2& rhs);
    void operator-=(const Vec2& rhs);
    void operator/=(const Vec2& rhs);
    void operator*=(const Vec2& rhs);

    float dist(const Vec2& rhs) const;
    float magnitude() const;
    void  normalize();
};

#endif // !VEC2_H
