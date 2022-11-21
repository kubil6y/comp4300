#include "vec2.h"
#include <cfloat>
#include <cmath>
#include <iostream>

#define CMP(x, y)                                                              \
    (fabsf(x - y) <= FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))))

vec2::vec2(float x, float y) : x(x), y(y)
{
}

bool vec2::operator==(const vec2& rhs) const
{
    return CMP(x, rhs.x) && CMP(y, rhs.y);
}

bool vec2::operator!=(const vec2& rhs) const
{
    return !(*this == rhs);
}

vec2 vec2::operator+(const vec2& rhs) const
{
    return vec2(x + rhs.x, y + rhs.y);
}

vec2 vec2::operator-(const vec2& rhs) const
{
    return vec2(x - rhs.x, y - rhs.y);
}

vec2 vec2::operator/(const vec2& rhs) const
{
    return vec2(x / rhs.x, y / rhs.y);
}

vec2 vec2::operator*(const vec2& rhs) const
{
    return vec2(x * rhs.x, y * rhs.y);
}

void vec2::operator+=(const vec2& rhs)
{
    x += rhs.x;
    y += rhs.y;
}

void vec2::operator-=(const vec2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
}

void vec2::operator*=(const vec2& rhs)
{
    x *= rhs.x;
    y *= rhs.y;
}

void vec2::operator/=(const vec2& rhs)
{
    x /= rhs.x;
    y /= rhs.y;
}

float vec2::dist(const vec2& rhs) const
{
    return sqrtf((x-rhs.x) * (x-rhs.x)  + (y-rhs.y) * (y-rhs.y));
}

float vec2::magnitude() const
{
    return sqrtf(x * x + y * y);
}

vec2 vec2::normalized() const
{
    float m = magnitude();
    return vec2(x / m, y / m);
}

void vec2::normalizeInPlace()
{
    float m = magnitude();
    x /= m;
    y /= m;
}

vec2 vec2::operator*(float s) const
{
    return vec2(x * s, y * s);
}

vec2 vec2::operator/(float s) const
{
    return vec2(x / s, y / s);
}

void vec2::operator*=(float s)
{
    x *= s;
    y *= s;
}

void vec2::operator/=(float s)
{
    x /= s;
    y /= s;
}

float dot(const vec2& lhs, const vec2& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

vec2 reflection(const vec2& source, const vec2& normal)
{
    return source - normal * (dot(source, normal) * 2.0f);
}

std::ostream& operator<<(std::ostream& os, const vec2& v)
{
    os << '(' << v.x << ',' << v.y << ')';
    return os;
}
