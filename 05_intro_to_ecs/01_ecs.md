# ECS Game Programming

-   `ECS` uses composition based design
-   `Entity`: Any object in the game
    -   Platform, Player, Tile, Bullet, Enemy, Gravity
-   `Component`: properties that can attach to Entities
    -   Position, texture, animation, health, gravity
    -   Components are `PURE DATA`
-   `Systems` Code/logic that drives behavior
    -   Movement, rendering, sound, physics
-   Entities can `never` have more than one type of components, i.e speed, bbox

## Examples

-   Player
    -   pos, speed, bbox, sprite, health, gravity, input
-   Enemy
    -   pos, speed, bbox, sprite, health, ai
-   Bullet
    -   pos, speed, bbox, angle, sprite, damage, lifespan
-   Tile
    -   pos, bbox, sprite

## Important Notes

-   Large AAA games can and have been made with `Object Oriented Design` for years
-   The teaches decided to teach ECS because in `his opinion` it is `better for this course`, and will allow us to do many things quite easily
-   Some agree with using ECS and some prefer OOD, `neither is 100% provably best`
-   This is `not the only` way to implement ECS
-   The architecture in this course is a `balance` between `efficiency`, ease of `use`, and ease of `learning` for an `undergraduate` class.
-   We will make `improvements` as we go and at the end of the course discuss how we would `optimize` things if making a `real game`

```cpp
Movement System:
    for(e: entities) { e.pos += e.velocity }

Collision System:
    for(b: bullets)
        for(e: enemies)
            if (Physics::IsCollision(b, e))
                    e.health -= b.damage
                    b.destroy();

Rendering System:
    for (e: entities) { window.draw(e.sprite, e.pos); }
```

## Game Engine Structure:

```
GameEngine
    > Scene
        > Systems
        > EntityManager
            > Entity
                > Component
```

## What is a Component?

-   An ECS Component is just `DATA`!
    -   (Maybe `some` logic in the constructor)
    -   No helper functionality within components
-   A Component class has some `intuitive meaning` to an Entity which contains it
    -   Ex: Position, Gravity, Health etc.
-   How to `implement` them in C++?

## What is an Entity?

-   Entity = any `object` in the game
    -   Usually, any object with a position
-   No unique `functionality`, typically just `stores` a number of Components
-   Stores `at most 1` of each component type
-   How Components are stored and used within an Entity can be a complex topic

## Component Storage Options

1.  Since there will be a `at most one` of every component, sotre `a variable for each` component type.
2.  Store a single `container` of Components. We can then use addComponent/getComponent functions for more `generally` than individual variables.

Component variables:

This approach have a downside because giving public access to raw pointers invite trouble with memory leaks, dangling pointers etc...

```cpp
class Entity
{
public:
    CTransform* cTransform = nullptr;
    CName*      cName      = nullptr;
    CShape*     cShape     = nullptr;
    CBBox*      cBBox      = nullptr;
    Entity() {}
    ~Entity() { // free memory properly (RAII) }
};
```

Component variables (safer):

While this one is safer it is slower. This will be improved in future lessons. Memory polling, cache coherence.

```cpp
class Entity
{
public:
    std::shared_ptr<CTransform> cTransform = nullptr;
    std::shared_ptr<CName>      cName      = nullptr;
    std::shared_ptr<CShape>     cShape     = nullptr;
    std::shared_ptr<CBBox>      cBBox      = nullptr;
    Entity() {}
}; // assignment 2
```

Component Collection:

```cpp
class Entity
{
private:
    std::vector<Component> m_components;
    // std::tuple<C1, C2, C3, C4> m_components;

public:
    Entity() {}
    void addComponent<T>(args);
    void getComponent<T>(args);
}; // assignment 3
```
