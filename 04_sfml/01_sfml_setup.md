# Linux SFML Setup

[SFML Linux](https://www.sfml-dev.org/tutorials/2.5/start-linux.php)

```sh
g++ src/*.cpp -Isrc -std=c++17 -o bin/sfmlgame -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

Config file will be in `bin` folder. That's why we need to cd into bin to read it.
