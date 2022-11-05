# Entity Manager

Recall: Entity

```cpp
class Entity
{
public:
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CName>      cName;
    std::shared_ptr<CShape>     cShape;
    std::shared_ptr<CBBox>      cBBox;
    Entity() {}
};
```

## Data Management

-   One of the most important concepts in all of programming: `seperate logic & data`
-   Create data structures which `manage` data so your logic code doesn't worry about it
-   Complex algorithm shouldn't have to know whether set, vector, map implementation
-   Let's make an `Entity Manager`!

## Entity Manager

-   Uses the `Factory` design pattern
-   Entity Manager will handle the creation, storage, and lifetime of `ALL` Entity objects
-   Entity Manager functions:
    -   addEntity, removeEntity, storage, bookkeeping
-   Factory should someshow ensure that user `cannot create` its own Entities

## Entity Tags

-   We may want to `group` Entities by functionality
-   Entity is `tagged` by string
    -   Tile, Player, Bullet, Enemy
    -   Instead of string, enum or int would be more optimized
-   EntityManager should have functionality for quickly getting Entities `of a given tag`
    -   Example: loop over all bullets

## Entity Implementation

```cpp
class Entity
{
private:
    const size_t      m_id    = 0;         // Unique
    const std::string m_tag   = "Default"; // {Player,Bullet,Tile}
    bool              m_alive = true;

public:
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CName>      cName;
    std::shared_ptr<CShape>     cShape;
    std::shared_ptr<CBBox>      cBBox;
    Entity(const std::string& tag, size_t id);
    void destroy() { m_alive = false; }
    const std::string& tag() { return m_tag; }
};
```

## Entity Manager Implementation

-   Will `trade` some memory for functionality
-   Will store all Entity objects in a `vector`
    ```cpp
    typedef std::vector<std::shared_ptr<Entity>> EntityVector;
    // According to learncpp prefer `using` over `typedef`
    using EntityVector = std::vector<std::shared_ptr<Entity>>;
    ```
-   Will also store `seperate vectors` of Entity objects `by their tag` for quick retrieval
    -   std::map<std::string, EntityVector>
-   We store `double` the number of pointers to save on computation in our engine
    -   We trade memory over speed and ease of use.

```cpp
using EntityVector = std::vector<std::shared_ptr<Entity>>;
using EntityMap    = std::map<std::string, EntityVector>;

class EntityManager
{
private:
    EntityVector m_entities;
    EntityVector m_toAdd; // waiting room (iterator validation)
    EntityMap    m_entityMap;
    // Represents number of entities ever created, not alive entities count
    size_t m_totalEntities = 0;

public:
    EntityManager() = default;
    void update();
    std::shared_ptr<Entity> addEntity(const std::string& tag);
    EntityVector&           getEntities();
    EntityVector&           getEntities(const std::string& tag);
};

// NOTE: addEntity doesn't handle some map related edge cases
std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag)
{
    // create a new Entity object
    auto e = std::make_shared<Entity>(tag, m_totalEntities++);

    // store it in the vector of all entities
    m_entities.push_back(e);

    // store it in the map of tag->EntityVector
    m_entityMap[tag].push_back(e); // if tag does not exist c++ will create it

    // return the shared pointer pointing to that entity
    return e;
}
```

## Iterator Invalidation

[cppreference/container](https://en.cppreference.com/w/cpp/container)

-   Iterator invalidation is `very important`
-   Caused by `adding/removing` elements of a collection as we are `iterating` through it
-   This happens `all the time` in games
    -   `Adding`: While iterating through all entities to check for collisions, an explosion happens and we spawn an explosion entity. While we iterate through our entities we add more entities. This could cause undefined behavior
    -   `Removing`: Iterate through entities to check collisions, one dies, so we remove it

## C++ Iterator Invalidation

-   Vector functions may cause reallocation (resizing)
    -   `Adding` to vector: push_back, insert, etc
    -   Vector may `resize`, recreating internal array
    -   Invalidates all pointers and iterators
-   Erasing elements may invalidate too
    -   `Remove` from vector: erase, pop_back
    -   Invalidates `iterators` and `references` at or after the point of erasing in the internal array

Example:

```cpp
void sCollision()
{
    // These will come from EntityManager
    EntityVector bullets;
    EntityVector tiles;
    for (auto& b : bullets)
        for (auto& t : tiles)
            if (Physics::IsCollision(b, t))
                bullets.erase(b); // after b might be undefined behavior
}

// We can modify the contents of the array (change its properties)
// but when we add/remove elements, we can face problems
```

## Delayed Effects

-   One way to avoid iterator invalidation is to `delay the effects` of actions that modify collections util it is safe to do so
    -   When you want to remove a bullet, mark it deleted and delete when it is safe to do it
-   With the EntityManager handling Entity creation and destruction, this becomes easy
-   Remember EntityManager also allows us to change underlying data structure. Without EntityManager it would be a nightmare to handle this manually through all over our codebase
-   Idea: Only add or remove entities at the beginning of a frame `when it is safe`

## Adding Entities

```cpp
std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
    // give each entity an increasing integer id
    auto e = std::make_shared<Entity>(tag, m_totalEntities++);
    // add e to waiting room vector, e will be added the next frame
    m_toAdd.push_back(e);
    return e;
}

// called at the beginning of each frame by game engine
// entities wil now be available to use this frame
void EntityManager::update()
{
    for (auto e : m_toAdd)
    {
        m_entities.push_back(e);
        m_entityMap[e->tag()].push_back(e);
    }
    m_toAdd.clear(); // clear waiting room
}
```

## Entity Death/Removal

-   With this system, we can easily implement entity death/removal
-   Entity has m_alive bool variable
-   Set this to false when we want it do die
-   EntityManager update() will read this variable and remove entities if false in next frame
-   Prevents removal iterator invalidation

```cpp
void EntityManager::update()
{
    for (auto e : m_toAdd)
    {
        m_entities.push_back(e);
        m_entityMap[e->tag()].push_back(e);
    }

    // this will also cause iterator invalidation but there
    // are ways to deal with this (remove if)
    for(auto e : m_entities)
    {
        // if e is dead, remove it from m_entities
        // if e is dead, remove it from m_entityMap[e->tag()]
        // this will be the assignment 2
    }

    m_toAdd.clear(); // clear waiting room
}
```

## EntityManager Usage

```cpp
EntityManager m_entities;
void spawnEnemy()
{
    auto e        = m_entities.addEntity("enemy");
    e->cTransform = std::make_shared<CTransform>(args);
    e->cShape     = std::make_shared<CShape>(args);
}

void collisions()
{
    for (auto b : m_entities.getEntities("bullet"))
        for (auto e : m_entities.getEntities("enemy"))
            if (Physics::CheckCollision(b, e))
            {
                // sets m_alive to false, and gets removed next frame
                b->destroy();
                e->destroy();
            }
}
```

## Game Main Loop

```cpp
void GameEngine::mainLoop()
{
    // before anything happens we update EntityManager
    m_entityManager.update();
    sUserInput();
    sMovement();
    sCollision();
    sRender();
    m_currentFrame++;
}
```

## Entity Private Constructor

-   We can ensure the safe creation of Entity objects by `only allowing them to be created` by the EntityManager class
-   We can make Entity constructor `private` and add EntityManager as friend class
-   This way, we `cannot` create Entity objects `outside` of the EntityManager
-   Unfortunately, having a private constructor means that we can no longer use `std::make_shared<Entity>(args)`
-   For private constructor classes, can use
    ```cpp
    // This is a hacky code, but we will not these hacky codes often.
    // This still works just fine, it is owned by shared_ptr but
    // it is just not the idiomatic way of doing things.
    auto e = std::shared_ptr<Entity>(new Entity(args));
    ```
-   This is not the preferred way of the creating shared pointer objects, but make just this one exception for our design
