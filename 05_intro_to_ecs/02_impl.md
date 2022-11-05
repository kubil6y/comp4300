# ECS

## Component Implementation

-   In this class, we will have a different Component class for each Component we want to implement
-   Naming: class CName
-   Very easy to implement Entity Component Storage option #1 with this

```cpp
class CTransform
{
public:
    Vec2 pos      = {0, 0};
    Vec2 velocity = {0, 0};
    CTransform() {}
    CTransform(const Vec2& p, const Vec2& v) : pos(p), velocity(v) {}
};

class CShape
{
public:
    sf::CircleShape shape;
    CShape() {}
};
```

## Declaring an Entity

```cpp
void doStuff(std::vector<Entity>& entities)
{
    for (auto& e : entities)
    {
        // update positions and draw to the screen
        e.cTransform->pos += e.cTransform->velocity;
        e.cShape->shape.setPosition(e.cTransform->pos);
        window.draw(e.cShape->shape);
    }
};


int main()
{
    std::vector<Entity> entities;
    Vec2                p(100, 200), v(10, 10);
    Entity              e;
    e.cTransform = std::make_shared<CTransform>(p, v);
    e.cName      = std::make_shared<CName>("Red Box");
    e.cShape     = std::make_shared<CShape>(args);
    entities.push_back(e);
    doStuff(entities);
    return 0;
};
```

## ECS: Systems

```cpp
void sMovement(std::vector<Entity>& entities)
{
    for (auto& e : entities)
    {
        e.CTransform->pos += e.CTransform->velocity;
    }
};
```

-   Some systems only operator on entities which `contain certain Components`
    -   Movement: CTransform
    -   Render: CTransform + CShape
    -   Physics: CBoundingBox
-   We can `filter` entities before passing them into system, or just `check` entities for required components before using them.

Checking for a component:

```cpp
int main()
{
    Entity e;
    e.cName      = std::make_shared<CName>("Red Box");
    // Component stored as shared_ptr, false if not present
    if(e.cTransform) {} // will be false
    if(e.cName) {} // will be true
    if(e.cTransform && e.cShape) {} // needed to render
};

void sRender(std::vector<Entity>& entities)
{
    for(auto& e : entities)
    {
        if(e.cShape && e.cTransformo)
        {
            e.cShape->shape.setPosition(e.cTransform->pos);
            window.draw(e.cShape->shape);
        }
    }
};
```
