# Collisions in Games

-   Collision programming involves 2 stages
-   Collision `Detection`
    -   Given two moving entities with some given shape/bounds, determine if they intersect
    -   Detection is a geometric problem
-   Collision `Resolution`
    -   Given that two entities have `collided`, determine what to do to `resolve` the physics of the simulation

Assumptions in this lecture:

-   We will use the course definition of `Entity`
-   Assume that Entities have the following
    -   Position(x,y)
    -   Bounding Shape (circle, rectangle, lines)
    -   Velocity (dx, dy)
-   Our goal is to learn the mathematics that allows entities to interact in our game.

## Collision Detection Problems

-   Given two entitites which have a speed, position, bounding shape, determine if, when, where they will collide (intersect)

## Entity Bounding Shapes

-   In the real world, objects can have arbitrary shapes/interaction `surfaces`
-   These are `difficult` to store, compute, and simulate accurately/continuously
-   All shapes in computer simulations must be made of `primitive` types
    -   2D: Line, Triangle, Circle, Rectangle
    -   3D: Sphere, Plane, Cylinder, Prism, Curves

## 2D Bounding Shapes

-   The `simplest` 2D bounding shape to store and compute is a `circle` with given radius
-   Other 2D bounding ahspes can be constructed with a number of `line segments`
-   The simplest of these is a `rectangle`
    -   Bounding Rectangle / Bounding Box

## Axis Aligned Bounding Boxes

-   Rectangles in a 2D plane can take `any orientation` as long as all 4 corners form 90 degree angles (def of rectangle)
-   By aligning our rectangles with the x/y axios, we can trade arbitrary alignments very fast intersection/collision checks

## AABB Horizontal Overlap

-   Horizontal overlap occurs if the top of each box is higher than the bottom of the other

## AABB Vertical Overlap

-   Vertical overlap occurs if the left of each box is less than right of the other

## AABB Intersection

-   Two AABB intersect if they overlap both horizontally and vertically

```
// horizontal
y1 < y2 + h2
y2 < y1 + h1

// vertical
x1 < x2 + w2
x2 < x1 + w1
```

-   This tells us IF two AABB intersect, but does not tell us by how much

## Centered AABB Intersection

-   Our game engine uses the CENTER of the entity as the position for AABB

```cpp
class CTransform : public Component
{
public:
    vec2  pos      = {0.0, 0.0}; // center
    vec2  prevPos  = {0.0, 0.0};
    vec2  scale    = {1.0, 1.0};
    vec2  velocity = {0.0, 0.0};
    float angle    = 0;
};

class CBoundingBox : public Component
{
public:
    vec2 size;
    vec2 halfSize;
    CBoundingBox(const vec2& s) : size(s), halfSize(s.x / 2, s.y / 2) {}
};
```

```
dx = abs(x2-x1)
Overlap in x-direction
(w2/2) + (w1/2) - dx
Positive if overlap

dy = abs(y2-y1)
Overlap in x-direction
(h2/2) + (h1/2) - dy
Positive if overlap

Combining both
--------------
delta = [abs(x1-x2),abs(y1-y2)]
ox = (w1/2) + (w2/2) - delta.x
oy = (h1/2) + (h2/2) - delta.y
overlap = [ox,oy] // both needs to be positive!
```

## Resolving Collisions

-   Now that we have `detected` an AABB collision, what do we do?
-   `Resolution` of collisions depends entirely on what the physics of your world should do
-   For example: if the player colllides with a tile, it should be `pushed out` to no overlap

## Detecting Collisions Direction

-   When detecting collisions inour game, they will first happen on a specific `frame`
-   The frame `before` the collision is detected, there will be no collision
-   Could try to use overlap to detech which direciton the movement came from? (No)
-   **Use previous overlap to detect direction**

## Using Previous Overlap

-   If the previous frame overlap.y > 0, then movement came from the side
-   Resolving collision by pushing x direction

-   If the previous frame overlap.x > 0, then movement came from the top or the bottom
-   Resolving collision by pushing y direction

## Top/Bottom Detection

-   A collision came from the top if it had a previous overlap.x > 0 and its y is higher

## Tricky Resolution Case

-   What if the previous frame had no overlap in either x or y direction? (diagonal)

    -   Must decide how to resolve collision based on previous position and/or overlap size

-   What if an entity overlaps with multiple entities? Ex: plyaer moving near stack
    -   Order of collision checks may decide which resolution occurs, can be tricky
    -   The `previous overlap` method discussed here usually resolves this case, using previous position only does not.

## Important Note

-   All collision resolution discussed here is for the simple case of avoiding overlap
-   Useful for: walking on tiles, not being able to pass through tiles, bullet hits entity
-   Many other kinds of collision resolutions occur in games:
    -   Kinematic object elastic/inelastic collision
    -   Physics simulators with mass/forces
