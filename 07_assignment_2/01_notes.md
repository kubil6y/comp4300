# Engine Architecture Progression

-   Assignment 1
    -   Getting used to C++/API
    -   One file main.cpp
-   Assignment 2
    -   Seperation of functionality into Classes
    -   Wrote our own Vec2 class for 2D game math
    -   Appearance of ECS classes
    -   EntityManager handles all Entity data
    -   ECS Systems functionality in Game.h functions

## Note

-   Game engine will be improved in future lessons.
-   Engine capabilities will be introduced below

## Game Class

-   Top-Level Game Object
-   Holds all game data
-   All game system functions
-   All gameplay code

## What can this engine do?

-   Create game objects as Entity instances
-   Add Component data to Entities
-   Implement game play via Systems
    -   Also, handle user input
-   Pause/exit game
-   Can init/load configuration file

## What are the limitations?

-   Can only display one `scene`
-   Can NOT load texture/sound assets
-   Can NOT display textured animations
-   Does not have any menu/interface

## Game Scene

-   A game can contain many different `scenes` that have very different logic/controls
-   Example: RPG Games
    -   Menu/Text/Dialogue Scene
    -   World-Map Scene
    -   Combat/Battle Scene
