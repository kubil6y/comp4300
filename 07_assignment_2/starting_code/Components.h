#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "Vec2.h"

#include <SFML/Graphics.hpp>

// Components are essentially structs, they do not have any functionality.
// They are just data containers.

class CTransform
{
public:
    Vec2  pos      = {0.0f, 0.0f};
    Vec2  velocity = {0.0f, 0.0f};
    float angle    = 0.0f;

    CTransform(const Vec2& pos, const Vec2& velocity, float angle)
        : pos(pos), velocity(velocity), angle(angle)
    {
    }
};

class CShape
{
public:
    sf::CircleShape circle;
    CShape(float radius, int points, const sf::Color& fill,
           const sf::Color& outline, float thickness)
        : circle(radius, points)
    {
        circle.setFillColor(fill);
        circle.setOutlineColor(outline);
        circle.setOutlineThickness(thickness);
        circle.setOrigin(radius, radius);
    }
};

class CCollision
{
public:
    float radius = 0;
    CCollision(float radius) : radius(radius)
    {
    }
};

class CScore
{
public:
    int score = 0;
    CScore(int score) : score(score)
    {
    }
};

class CLifespan
{
public:
    int remaining = 0; // amount of lifespan remaining on the entity
    int total     = 0; // the total initial amount of lifespan
    CLifespan(int total) : remaining(total), total(total)
    {
    }
};

class CInput
{
public:
    bool up    = false;
    bool left  = false;
    bool right = false;
    bool down  = false;
    bool shoot = false;

    CInput()
    {
    }
};

#endif // !COMPONENTS_H
