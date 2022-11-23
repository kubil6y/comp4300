# Advanced Main Loop

-   Graphically, more FPS = smoother gameplay
-   FPS is typically determined by two things:
    -   How much work done on each loop
    -   How fast is the underlying hardware
-   The flexibility you have with your game loop can depend on many factors
    -   OS: How often can you poll events?
    -   OS: Are hardware input events blocking?
    -   Monitor: Can't render more often than monitor refresh rate (Vsync)
    -   Networking: Type of net traffic can determine timeouts, loss, etc (not covered here)

## Setting Fixed FPS Count

-   Let's say we want to fix game to 60FPS
-   To do it manually, we must limit out game loop to run at most every 1000/60 ~ 16ms
-   We will add a delay to the end of each loop

```cpp
float MS_PER_FRAME = 1000.0 / 60.0;
while (true)
{
    float start = getCurrentTimeMS();
    processInput();
    update();
    render();
    float elapsed = getCurrentTimeMS() - start;
    sleep(max(0, MS_PER_FRAME - elapsed));
}
```

-   Adding the sleep() at the end of the loop ensures we don't update too quickly
-   Unfortunately, there's no way to ensure that slow code doesn't make your game run too slowly
-   In this case, must cut computation time to ensure the FPS target can be reached

## Game Simulation Scaling

```cpp
float lastTime = getCurrentTimeMS();
while (true)
{
    float current = getCurrentTimeMS();
    float elapsed = current - lastTime;
    processInput();
    update(elapsed); // could be floating point error
    render();
    lastTime = current;
}
```

### Variable Time Step

-   Each frame we calculate how much real time has passed since the last game update
-   When we update the game state, we use the real elapsed time as a scale variable
-   Example: Bullet flying through the air

    -   Each time step update it with velocity
    -   Variable time: scale velocity with elapsed time

**Advantages**

-   Game plays at consistent rate on different hardware
-   Players with faster machines get smoother FPS

**Disadvantages**

-   Non-deterministic effects based on variable FPS
-   Floating point errors produce different results
-   Network desynchronization
-   Physics simulations yield different results (collision)

---

### Variable Number of Fixed Updates

```cpp
float previous = getCurrentTimeMS();
float lag = 0.0f;
while(true)
{
    float current = getCurrentTimeMS();
    float elapsed = current - previous;
    previous = current;
    lag += elapsed;
    processInput();
    while(lag >= MS_PER_UPDATE)
    {
        update();
        lag -= MS_PER_UPDATE;
    }
    render();
}
```

-   Lag measures `how far behind` the game's clock is behind the real world clock (example: if one update or render took too long)
-   Inner loop updates the game to `catch up` until all of the lag is gone, with fixed step updates (which are accurate)
-   Once we catch up, we render the scene
-   Game simulates at a constant rate using fix time steps in a `safe` way + `catch up` for lagged frames
-   Rendering may appear `choppy` while the game catches up, but at least the simulation speed is fixed on different hardware
-   NOTE: We can only `catch up` if `lag frames` are infrequent

Rendering Decoupling:

-   Imporatant: We have now removed the rendering synchronization from update()
-   No longer call one render per update
-   This means we could put rendering into another thread (for example)
-   But some issues can arise from this, namely: rendering between updates

NOT COMPLETE ENOUGH
