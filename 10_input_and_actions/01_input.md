# Game Inputs & Actions

-   The `result` of an input is typically an `action` that the player wants to happen in the game
    -   example: jump, walk right, shoot
-   Actions can also be called `Commands`
-   It doesn't really matter to the player which Input `causes` an Action, as long as it's `easy to perform`
-   Similarly, the game negine shouldn't care which `input device` caused an action to be triggered
-   The game engine should only care about the `action logic` itself and how to carry it out
-   So ideally, we would like to `decouple` the action logic from the inputs that triggered them

## Game Action Implementation

-   So far, we have been performing actions `directly` inside the sfml eventl loop
-   When a specific key is pressed, specific game logic gets called
-   In our current engine, we can't separate the two, or re-map keys, etc

## New Action Implementation

-   Let's try and implement a system where the Scene `only knows` the type of `action` the player wants to perform, and `doesn't care` about the input method
-   In this way, actions could come from `anywhere:` keyboard, mouse, replay file, network system, VR controller, etc

## Action Class

-   We will construct an `Action` class, which will store the type of action that the player wants the Scene to perform
-   All user `input` will be handled within the GameEngine class, where Actions will be `created` and `sent` to the Scenes to have their logic carried out
-   The Scene will then have a `doAction()` method which performs logic based on a specific Action object
-   Actions will be given a `name` (jump, left, etc)
-   Actions input via keyboard or controller will have two phases: `press` and `release`, which typically denote the start and end of action
-   Actions will then have two main variables
    -   Name: Name of the action (jump, shoot, etc)
    -   Type: START or END

```cpp
// string is for ease of use, an enum would be better
class Action
{
    std::string m_name = "NONE";
    std::string m_type = "NONE";

public:
    Action();
    Action(const std::string& name, const std::string& type);

    const std::string& name() const;
    const std::string& type() const;
    std::string toString() const;
};
```

Example: {"Right", "Start"}:

-   Player will run Right as if you held down the move right input button continuously
-   Will only stop moving on {"Right", "End"}

## Mapping Keys to Action

-   We want to be able to `specify` which user input (exp: keyboard key) `maps` to a specific Action object
-   The scene base class will store this map
    -   std::map<int, string> m_actionMap; (int is SFML keycode)
-   To `register` (map) a key to an Action, which will insert the action name into the map
    -   `m_actionMap[inputKey] = actionName;`
-   Each scene will now have `its own map` so we can have different actions available in each Scene

```cpp
void Scene_Menu::init()
{
    registerAction(sf::Keyboard::W, "UP");
    registerAction(sf::Keyboard::S, "DOWN");
    registerAction(sf::Keyboard::D, "PLAY");
    registerAction(sf::Keyboard::Escape, "QUIT");
}
```

## Creating Action Objects

-   The `GameEngine` class will handle the actual user input key presses and `construct` the Action to send to the current Scene
-   When a key is pressed, the GameEngine will `ask the Scene` if it has an action name `associated` with the key's value
-   If the Scene has an associated Action, we create an Action object with the correct NAME and TYPE
    -   KeyPress = START, KeyRelease = END

```cpp
// @GameEngine Class
if (event.type == sf::Event::KeyPressed ||
    event.type == sf::Event::KeyReleased)
{
    // if the current scene does not have an action associated with this
    // key, skip the event
    if (currentScene()->getActionMap().find(event.key.code) ==
        currentScene()->getActionMap().end())
    {
        continue;
    }

    // determine start or end action by whether it was key press or release
    const std::string actionType =
        (event.type == sf::Event::KeyPressed) ? "START" : "END";

    // look up the action and send the action to the scene
    currentScene()->doAction(Action(
        currentScene()->getActionMap().at(event.key.code), actionType));
}
```

## Doing Scene Actions

-   Now that we have constructed the Action object in the GameEngine, we `send it to the Scene` to have its logic performed
-   This is done by the derived Scene class's sDoAction(const Action& action) method
-   We read the name and the type of the action and perform its logic `without knowing` the user input that created it

```cpp
void Scene_Menu::sDoAction(const Action& action)
{
    if (action.type() == "START")
    {
        if (action.name() == "UP")
        {
            if (m_selectedMenuIndex > 0)
                m_selectedMenuIndex--;
            else
                m_selectedMenuIndex = m_menuStrings.size() - 1;
        }
        else if (action.name() == "DOWN")
        {
            m_selectedMenuIndex =
                (m_selectedMenuIndex + 1) % m_menuStrings.size();
        }
        else if (action.name() == "PLAY")
        {
            m_game->changeScene("PLAY",
                                std::make_shared<Scene_Play>(
                                    m_game, m_levelPaths[m_selectedMenuIndex]));
        }
        else if (action.name() == "QUIT")
        {
            onEnd();
        }
    }
}
```

NOTE: In some systems Actions have a reference to the scene and modify the scene. The action encapsulates the logic. In this course the teacher chose this way because it was more fitting with the architecture. Both are valid. I think encapulating the logic is better.
