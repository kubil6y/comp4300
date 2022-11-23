# Pathfinding and Steering

[Pathfinding Demo](https://www.cs.mun.ca/~dchurchill/search/)

Main video game movement problems:

|     |                |                        |
| --- | -------------- | ---------------------- |
| 1   | Path-finding   | How to get from A to B |
| 2   | Path-following | How to move along path |
| 3   | Physics        | How environment reacts |
| 4   | Animation      | How entities look      |

[COMP 3200 - Intro Artificial Intelligence](https://www.youtube.com/playlist?list=PL_xRyXins84-dTmpL68AKv7UFAEvIeIr1)

## Pathfinding

-   Video game maps are often filled with `obstacles` with which NPC will `collide`
-   Pathfinding is the method we use to determine which path an NPC should take from its `current` location to a `goal` location
-   Pathfinding attemps to `minimize a cost` of the path. It could be total length, fuel, damage taken, or an arbitrary function

## Pathfinding Considerations

-   Single Agent / Multi Agent
-   Single Goal / Multi Goal
-   Static (precomputed) / Dynamic (online)
-   Space representation (data structure)
    -   Open / Grid / Graph / Polygons
-   Movement Directions
    -   Fixed movement (up, down left, right)
    -   Arbitrary angles / movement
    -   Move between nodes on a graph

## Space / Action Representation

-   Space and action representations are important decisions, ideas are linked
-   Which representation to choose is based on many factors from the game's `design`
-   The choice of space representation in the pathfinding engine will determine which movement actions can be performed
