# Ray Casting

-   Ray Casting is the name for a technique which has many applications in games
-   Ray Tracing = Iterative Ray Casting
-   Intuitively in 3D: "Cast rays outward from my eye to the world, what do they hit?"
-   Very heavy on vector math, but has many useful applications

-   [Sight and Light](https://ncase.me/sight-and-light)
-   [Visibility](https://www.redblobgames.com/articles/visibility/)

## 2D Ray Casting

-   Draw a line(segment) between two points
-   Detect if and where a collision occurs
-   Ray Tracing = Where did it `bounce` to?
-   If no collision occurs on a line between two points, then they can `see` each other (line of sight in military terminology)
-   2D Ray Casting primarily solves problems that deal with light/visibility

## Ray Casting Basics

-   Ray Casting asks `is anything blocking the path between these two 2D points`
-   The `path` between two points is `blocked` if the line segment between them intersects with another existing line segment
-   Depending on the application, we may also want to know the `first` such intersection, and where it occured
-   So far in the course, we have been using the Vec2 class to represent points in 2D space as 2D vector with (x,y)
-   A line segment can be defined by the start and end point of a line using Vec2

## 2D Game Visibility

-   Now thatwe know how to do line segment intersection, how do we use it for visibility?
-   If line segment ab does not collide with any vision-blocking entities, b is visible to a
-   Non-line game objects (like cubes) are made of line segments. We take the closest intersection. Entity can see up to the closest intersection. Anything beyond that is outside vision

## 2D Game Lighting Effects

-   Light travels outward in all directions
-   How do we calculate everywhere it lands? (There are better ways to do things)
