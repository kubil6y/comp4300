# Replays

-   Many games have functionality to be able to `record gameplay` in the form of `replays`
-   The replay files are just actions recorded.
-   The replay files are small in size.
-   The draw back of replay files is that they only work with the game engine. You can not put them on YouTube for example which is not a drawback in my book
-   Now that our Scenes don't care about `where an Action came from`, we can see how easy it would be to implement Replay files
-   For example, just store our Action strings in a file along with the specific `game frame` that they were performed on. Then load this file in the GameEngine class and feed Actions to the Scene
    -   FRAME 100 SHOOT START
-   This is how ghosts are implemented (mostly in racing games)
