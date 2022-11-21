#ifndef VEC2_H
#define VEC2_H

#include <ostream>

class vec2
{
public:
    float x = 0;
    float y = 0;

    vec2() = default;
    vec2(float x, float y);

    bool operator==(const vec2& rhs) const;
    bool operator!=(const vec2& rhs) const;

    vec2 operator+(const vec2& rhs) const;
    vec2 operator-(const vec2& rhs) const;
    vec2 operator*(const vec2& rhs) const;
    vec2 operator/(const vec2& rhs) const;

    void operator+=(const vec2& rhs);
    void operator-=(const vec2& rhs);
    void operator*=(const vec2& rhs);
    void operator/=(const vec2& rhs);

    vec2 operator*(float s) const;
    vec2 operator/(float s) const;
    void operator*=(float s);
    void operator/=(float s);

    friend std::ostream& operator<<(std::ostream& os, const vec2& v);

    float dist(const vec2& rhs) const;
    float magnitude() const;
    vec2  normalized() const;
    void  normalizeInPlace();
};

float dot(const vec2& lhs, const vec2& rhs);
vec2 reflection(const vec2& source, const vec2& normal);
#endif // !VEC2_H
