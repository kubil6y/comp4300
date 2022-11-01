# ECS Game Programming

-   ECS uses composition based design
-   Entity: Any object in the game
    -   Player, platform, tile, bullet
-   Component: Properties attached to entities
    -   Components are **PURE DATA**
    -   Position, texture, animation, health, gravity
-   Systems: Code/logic that drives behavior
    -   Movement, rendering, sound, physics

## ECS Entity Examples:

```
Player:
    - pos, speed, bbox, sprite, health, gravity, input
Enemy:
    - pos, speed, bbox, sprite, health, ai
Bullet:
    - pos, speed, angle, bbox, sprite, damage, lifespan
Tile:
    pos, bbox, sprite
```

## ECS Entity Examples:

```
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
