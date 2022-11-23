# Visualizing Games

-   Video game worlds are often much bigger than we can display on-screen all at once
-   Like the real world, we can only display a sub-section of the world at a given time
-   The part of the game world that we can currently see is called a `View`

## View/Camera

-   To mathematically describe our desired view of the game world, we often use the concept of an in-game `Camera`
-   Intuitively, we define the location of a camera in the world, and where it points
-   Similar to real photography, this will determine the final view that we see

-   [The Challenge of Cameras](https://www.youtube.com/watch?v=bHdi5Ar8GXw)
-   [2D Camera Types](https://www.youtube.com/watch?v=l9G6MNhfV7M)
-   [Scroll Back: The Theory and Practice of Cameras in Side-Scrollers](https://www.gamedeveloper.com/design/scroll-back-the-theory-and-practice-of-cameras-in-side-scrollers)
-   [The Beauty of Parallax](https://www.youtube.com/watch?v=z9tBce8eFqE)

## SFML Views

-   A `View` is a window into another `world`
-   An sf::View is a rectangle representing a 2D `camera` that you can use to specify which pixesl of a game will be drawn to the window
-   Changing a window's view does not alter the underlying entity/sprite, it simply changes where in the window they are drawn
-   By changing the view, we can change what part of our game world is shown to the player

https://www.gamesutra.com/blogs
