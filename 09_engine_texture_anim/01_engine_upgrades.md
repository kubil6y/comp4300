# GameEngine / Scenes

-   Let's seperate the previous Game class into two classes which handle this new functionality
-   GameEngine Class
    -   Functionality present in all scenes
    -   Construction/Management of Scene(s)
    -   Running/Quitting Game
-   Scene Class
    -   Functionality specific to each scene
    -   Entities relevant to that scene

## GameEngine Class

```
GameEngine
-scenes       : map<string,Scene>
-window       : sf::RenderWindow
-assets       : Assets
-currentScene : string
-running      : bool

+init               : void
+currentScene()     : Scene*
+run()              : void
+update()           : void
+quit()             : void
+changeScene(scene) : void
+getAssets()        : void
+window()           : Window&
+sUserInput()       : void
```

-   Stores `top level` game data
-   Performs top level functionality
    -   Changing Scenes, Handling Input
-   Run() contains game `main loop`
-   GameEngine pointer will be passed to Scenes in constructor
    -   Access to : assets, window, scenes

## Scene Base Class

-   Stores `common Scene data`
    -   Entities, frame count, actions
-   Scene-specific functionality is carried out in Derived classes
-   Base Scene class is `Abstract`, cannot be instantiated
-   simulate() calls derived scene's update() a given number of times (will be useful later)

```
Scene(Abstract)
- game         : GameEngine*
- entities     : EntityManager
- currentFrame : int
- actionMap    : map<int, string>
- paused       : bool
- hasEnded     : bool

+ update()          : void = 0
+ sDoAction(action) : void = 0
+ sRender()         : void = 0

+ simulate(int)          : void
+ doAction(action)       : void
+ registerActino(action) : void
```

## Scene Derived Class

-   Stores `Scene-specific` data
    -   level, player pointer, config
-   Scene-specific systems are defiend within the derived class
-   Some scene derived classes may require quite different systems based on functionality
-   **update(), sRender(), sDoAction() must be implemented for each Scene**

```
Scene_Play : Scene
- levelPath    : string
- player       : Entity*
- playerConfig : PlayerConfig

- init()   : void
+ update() : void

// Systems
- sAnimation()      : void
- sMovement()       : void
- sEnemySpawner()   : void
- sCollision()      : void
- sRender()         : void
- sDoAction(action) : void
- sDebug(action)    : void
```

## Scene Switching

-   GameEngine stores a map from strings to shared_ptr<Scene>
-   Also stores a currentScene string
-   currentScene() looks up the currently active scene by `map[currentScene]`
-   changeScene(string, scene) changes the scene to a new, or previously stored Scene
-   Mimics a `finite state machine` for Scene switching

## Scene Switching Example

1.  Game engine constructed:
    -   changeScene("menu", sp<Scene_Menu>())
        -   currentScene = "menu"
        -   scenes["menu"] = sp<Scene_Menu>
2.  Player presented with menu scene
3.  Player selectes a level on the menu
    -   LevelPath = currently selected menu item
    -   Menu tells game negine to change scenes
    -   game->changeScene("play", sp<Scene_Play>(LevelPath))

## Asset Management

-   Assets are external files that are loaded into memory to be used in the game.
-   For our games, assets will be:
    -   Textures (.png, .jpg)
    -   Animations (textures + bookkeeping)
    -   Sounds (.wav, .ogg)
    -   Fonts (.ttf)
-   **Load once, use often**

## Assets Class

-   Want to load assets that are defined in an external configuration file
    -   Texture MegaMan textures/MMS.png
    -   Sound MegaDeath sounds/death.wav
-   We can then reference that asset via its name:
    -   m_assets->getTexture("MegaMan");
    -   m_assets->getSound("MegaDeath");
-   To implement this, the Asset class will use a map<string, AssetType>
