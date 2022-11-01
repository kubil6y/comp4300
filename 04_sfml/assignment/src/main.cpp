#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

class MyShape
{
private:
    std::shared_ptr<sf::Shape> shape;
    sf::Color color;
    float posX;
    float posY;
    float velX;
    float velY;

public:
    MyShape(std::shared_ptr<sf::Shape> shape, sf::Color color, float posX,
            float posY, float velX, float velY)
        : shape(shape), color(color), posX(posX), posY(posY), velX(velX),
          velY(velY)
    {
        shape->setPosition(posX, posY);
        shape->setFillColor(color);
    }

    std::shared_ptr<sf::Shape> getShape()
    {
        return shape;
    }

    void update(int windowWidth, int windowHeight)
    {
        sf::Vector2f pos = shape->getPosition();
        sf::FloatRect bounds = shape->getLocalBounds();

        if (pos.x + bounds.left + bounds.width > windowWidth || pos.x < 0)
        {
            velX *= -1;
        }

        if (pos.y + bounds.top + bounds.height > windowHeight || pos.y < 0)
        {
            velY *= -1;
        }

        shape->setPosition(pos.x + velX * .5f, pos.y + velY * .5f);
    }
};

void loadConfigFile(const std::string& filename,
                    std::vector<std::shared_ptr<MyShape>>& shapes,
                    int& windowWidth, int& windowHeight);
int main()
{
    int windowWidth = 640;
    int windowHeight = 480;
    std::vector<std::shared_ptr<MyShape>> shapes;
    loadConfigFile("config", shapes, windowWidth, windowHeight);

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
                            "Assignment 1");
    // window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                std::cout << "Closing Application" << std::endl;
                window.close();
            }
        }

        window.clear();

        for (auto& s : shapes)
        {
            window.draw(*s->getShape());
            s->update(windowWidth, windowHeight);
        }

        window.display();
    }
    return 0;
}

void loadConfigFile(const std::string& filename,
                    std::vector<std::shared_ptr<MyShape>>& shapes,
                    int& windowWidth, int& windowHeight)
{
    std::ifstream fin(filename);
    std::string name;

    while (fin >> name)
    {
        if (name == "Window")
        {
            int W, H;
            fin >> W >> H;
            windowWidth = W;
            windowHeight = H;
            std::cout << name << ' ' << W << ' ' << H << '\n';
        }
        else if (name == "Font")
        {
            std::string F;
            int S, R, G, B;
            fin >> F >> S >> R >> G >> B;
            std::cout << name << ' ' << F << ' ' << S << ' ' << R << ' ' << G
                      << ' ' << B << '\n';
        }
        else if (name == "Circle")
        {
            std::string color;
            float X, Y, SX, SY, Rad;
            int R, G, B;
            fin >> color >> X >> Y >> SX >> SY >> R >> G >> B >> Rad;

            auto sfShape = std::make_shared<sf::CircleShape>(Rad);
            auto sPtr = std::make_shared<MyShape>(sfShape, sf::Color(R, G, B),
                                                  X, Y, SX, SY);
            shapes.push_back(sPtr);

            std::cout << name << ' ' << color << ' ' << X << ' ' << Y << ' '
                      << SX << ' ' << SY << ' ' << R << ' ' << G << ' ' << B
                      << ' ' << Rad << '\n';
        }
        else if (name == "Rectangle")
        {
            std::string color;
            float X, Y, SX, SY, W, H;
            int R, G, B;
            fin >> color >> X >> Y >> SX >> SY >> R >> G >> B >> W >> H;

            auto sfShape =
                std::make_shared<sf::RectangleShape>(sf::Vector2f(W, H));
            auto sPtr = std::make_shared<MyShape>(sfShape, sf::Color(R, G, B),
                                                  X, Y, SX, SY);
            shapes.push_back(sPtr);

            std::cout << name << ' ' << color << ' ' << X << ' ' << Y << ' '
                      << SX << ' ' << SY << ' ' << R << ' ' << G << ' ' << B
                      << ' ' << W << ' ' << H << '\n';
        }
        else
        {
            std::cout << "Unknown type while reading :" << filename << '\n';
            break;
        }
    }
}
