# Vectors in Games

-   For 2D games, many quantities/properties of game objects have box an `X and Y` position, these form a `2D Vector`
    -   Mathematical Vector, not collection vector
-   Example: Coordinate(x,y), Velocity(x,y), Gravity(x,y)
-   Annoying to store/refer to xy seperately
-   We will make a 2D Vector class: Vec2

## Notes on Vec2

-   We will go more in depth on vector math for games later in the course
-   We first `introduce` the programming `architecture`, then later use it to implement game math/physics concepts
-   Note: `sf::Vector2f` already exists, we will basically be reinventing it in this course

## Vec2 Class

-   What do we want to `store` in Vec2?
    -   Member variables x, y
-   What do we want to `do with` those values?
    -   Functions/Operators on the Vec2 class
-   Possible `operations` on Vec2
    -   +, -, \*, /
    -   length, normalize, rotate etc

```cpp
class Vec2
{
public:
    float x = 0, y = 0;
    Vec2();
    Vec2(float xin, float yin);
    bool operator==(const Vec2& rhs) const;
    Vec2 operator+(const Vec2& rhs) const;
    Vec2 operator*(const Vec2& val) const;
    Vec2 operator+=(const Vec2& rhs);
};

Vec2 pos(100, 200);
Vec2 speed(-5, 10);
Vec2 accel(0, -9.8);
while(true)
{
    pos += speed;
    speed += accel;
}

// Speed is the time rate at which an object is moving along a path,
// while velocity is the rate and direction of an object's movement.
float dist = velocity.length();
```
