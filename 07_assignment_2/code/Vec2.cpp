#include "Vec2.h"
#include <cmath> // TODO cmath vs math.h? course uses math.h

bool Vec2::operator==(const Vec2& rhs) const
{
    return x == rhs.x && x == rhs.y; // TODO float comparasion
}

bool Vec2::operator!=(const Vec2& rhs) const
{
    return !(*this == rhs);
}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
}

Vec2 Vec2::operator/(const Vec2& rhs) const
{
}

Vec2 Vec2::operator*(const Vec2& rhs) const
{
}

void Vec2::operator+=(const Vec2& rhs)
{
}

void Vec2::operator-=(const Vec2& rhs)
{
}

void Vec2::operator/=(const Vec2& rhs)
{
}

void Vec2::operator*=(const Vec2& rhs)
{
}

void Vec2::normalize()
{
}

float Vec2::magnitude() const
{
    return 0;
}
