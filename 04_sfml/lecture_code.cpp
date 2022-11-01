#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <memory>

int main()
{
    const int        wWidth  = 640;
    const int        wHeight = 480;
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "Tutorial");
    window.setFramerateLimit(60);

    /*
    sf::CircleShape circle(50);
    uint r = 0;
    uint g = 255;
    uint b = 255;
    circle.setFillColor(sf::Color(r, g, b));
    circle.setPosition(300.0f, 300.0f);
    circle.setOutlineThickness(10);
    circle.setOutlineColor(sf::Color::Magenta);
    float circleMoveSpeed = .5f;

    float              rx = 50.0f;
    float              ry = 50.0f;
    sf::Vector2f       rSize(rx, ry);
    sf::RectangleShape rect(rSize);
    rect.setOrigin(rx / 2, ry / 2);
    float rectMoveSpeed = -0.8f;

    rect.setPosition(200, 200);
    rect.setFillColor(sf::Color(255, 0, 0));
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(20.0f);
    */

    std::vector<std::shared_ptr<sf::Shape>> shapes;
    std::shared_ptr<sf::Shape> shape1 = std::make_shared<sf::CircleShape>(20);
    std::shared_ptr<sf::Shape> shape2 = std::make_shared<sf::CircleShape>(30);
    shapes.push_back(shape1);
    shapes.push_back(shape2);

    shape1->setFillColor(sf::Color::Yellow);
    shape1->setPosition(200, 200);
    shape2->setFillColor(sf::Color::Blue);
    shape2->setPosition(300, 300);

    sf::Font myFont;
    if (!myFont.loadFromFile("assets/tech.ttf"))
    {
        std::cerr << "Could not load font!\n";
        exit(-1);
    }

    sf::Text text("Sample Text", myFont, 20);
    // Position the top-left corner of the text so that the text aligns on the
    // bottom. Text character size is in pixels, so move the text up from the
    // bottom by its height
    text.setPosition(0, wHeight - (float)text.getCharacterSize());

    sf::Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                std::cout << "Key pressed with code = " << event.key.code
                          << '\n';
                if (event.key.code == sf::Keyboard::X)
                {
                    // reverse the direction of the circle on the screen
                    //circleMoveSpeed *= -1.0f;
                    //rectMoveSpeed *= -1.0f;
                }
            }
        }

        // circle.setPosition(circle.getPosition().x + circleMoveSpeed,
        // circle.getPosition().y + circleMoveSpeed);
        // rect.rotate(.2f);

        window.clear();

        for (auto& shape : shapes)
        {
            window.draw(*shape);
        }
        window.draw(text);
        window.display(); // handles OpenGL buffer swapping
    }
    return 0;
}
