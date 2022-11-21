#include "Game.h"
#include "vec2.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cstdlib>
#include <fstream>
#include <iostream>

// helpers
float incRand(int min, int max);
vec2  getRandomEnemyCoords(const EntityVec& enemies, float minX, float maxX,
                           float minY, float maxY, float radius);

// constructor, takes in game config
Game::Game(const std::string& config)
{
    init(config);
}

void Game::init(const std::string& path)
{
    std::srand(time(nullptr)); // seed random

    // TODO: read in config file here
    //       use the premade PlayerConfig, EnemyConfig, BulletConfig variables
    //       remember to add fullscreen mode 0,1

    std::ifstream fin(path);
    std::string   name;
    while (fin >> name)
    {
        if (name == "Window")
        {
            // clang-format off
            fin >> m_config.window.W >>
                   m_config.window.H >>
                   m_config.window.FL >>
                   m_config.window.FS;
            // clang-format on
        }
        else if (name == "Font")
        {
            // clang-format off
            fin >> m_config.font.F
                >> m_config.font.S
                >> m_config.font.R
                >> m_config.font.G
                >> m_config.font.B;
            // clang-format on
        }
        else if (name == "Player")
        {
            // clang-format off
            fin >> m_config.player.SR
                >> m_config.player.CR
                >> m_config.player.S
                >> m_config.player.FR
                >> m_config.player.FG
                >> m_config.player.FB
                >> m_config.player.OR
                >> m_config.player.OG
                >> m_config.player.OB
                >> m_config.player.OT
                >> m_config.player.V;
            // clang-format on
        }
        else if (name == "Enemy")
        {
            // clang-format off
            fin >> m_config.enemy.SR
                >> m_config.enemy.CR
                >> m_config.enemy.SMIN
                >> m_config.enemy.SMAX
                >> m_config.enemy.OR
                >> m_config.enemy.OG
                >> m_config.enemy.OB
                >> m_config.enemy.OT
                >> m_config.enemy.VMIN
                >> m_config.enemy.VMAX
                >> m_config.enemy.L
                >> m_config.enemy.SI;
            // clang-format on
        }
        else if (name == "Bullet")
        {
            // clang-format off
            fin >> m_config.bullet.SR
                >> m_config.bullet.CR
                >> m_config.bullet.S
                >> m_config.bullet.FR
                >> m_config.bullet.FG
                >> m_config.bullet.FB
                >> m_config.bullet.OR
                >> m_config.bullet.OG
                >> m_config.bullet.OB
                >> m_config.bullet.OT
                >> m_config.bullet.V
                >> m_config.bullet.L;
            // clang-format on
        }
        else
        {
            std::cout << "Something went wrong while reading '" + path + "'\n";
        }
    }

    // set up default window parameters
    m_window.create(
        sf::VideoMode(m_config.window.W, m_config.window.H), "Assignment 2",
        m_config.window.FS ? sf::Style::Fullscreen : sf::Style::Default);
    m_window.setFramerateLimit(m_config.window.FL);

    spawnPlayer();
}

void Game::run()
{
    // TODO: add pause functionality in here
    //       some systems should function while paused (rendering)
    //       some system should not (movement, input)
    sf::Clock clock;
    while (m_running)
    {
        // std::cout << "fps: " << 1 / clock.restart().asSeconds() << std::endl;

        m_entityManager.update();

        // TODO
        if (!m_paused)
        {
            sLifespan();
            sEnemySpawner();
            sEnemyVelUpdate();
            sMovement();
            sCollision();
        }

        sUserInput();
        sRender(); // always render!

        // increment the current frame
        // may need to be moved when paused implemented
        m_currentFrame++;
    };
}

// pause the game
void Game::setPaused(bool paused)
{
    m_paused = paused;
}

void Game::sMovement()
{
    // TODO implement all entity movement in this function
    // you should read the m_player->cInput component to determine if the player
    // is moving

    vec2  zero(0.0f, 0.0f);
    float vel = 5; // TODO

    // Player Movement BEGIN ----------
    m_player->cTransform->velocity = zero;
    if (m_player->cInput->up)
        m_player->cTransform->velocity.y = -vel;
    if (m_player->cInput->down)
        m_player->cTransform->velocity.y = vel;
    if (m_player->cInput->left)
        m_player->cTransform->velocity.x = -vel;
    if (m_player->cInput->right)
        m_player->cTransform->velocity.x = vel;

    // sample movement speed update
    m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
    m_player->cTransform->pos.y += m_player->cTransform->velocity.y;
    // Player Movement END ----------

    // Enemy Movement BEGIN ----------
    for (auto e : m_entityManager.getEntities(EntityType::enemy))
    {
        e->cTransform->pos.x += e->cTransform->velocity.x;
        e->cTransform->pos.y += e->cTransform->velocity.y;
    }
    // Enemy Movement END ----------

    // Bullet Movement BEGIN ----------
    for (auto b : m_entityManager.getEntities(EntityType::bullet))
    {
        b->cTransform->pos.x += b->cTransform->velocity.x * 8;
        b->cTransform->pos.y += b->cTransform->velocity.y * 8;
    }
    // Bullet Movement END ----------
}

// System: User Input
void Game::sUserInput()
{
    // TODO handler user input here
    // note that you should only be setting the player's input component
    // variables here.
    // you should not implement the player's movement logic here
    // the movement system will read the variables you set in this function

    sf::Event event;
    while (m_window.pollEvent(event))
    {
        // this event triggers when the window is closed
        if (event.type == sf::Event::Closed)
        {
            m_running = false;
        }

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::E:
                m_player->cInput->up = true;
                break;
            case sf::Keyboard::D:
                m_player->cInput->down = true;
                break;
            case sf::Keyboard::F:
                m_player->cInput->right = true;
                break;
            case sf::Keyboard::S:
                m_player->cInput->left = true;
                break;
            case sf::Keyboard::P:
                if (m_paused)
                {
                    std::cout << "game is UNPAUSED" << std::endl;
                    m_paused = false;
                }
                else
                {
                    std::cout << "game is PAUSED" << std::endl;
                    m_paused = true;
                }
                break;
            case sf::Keyboard::Escape: // TODO
                m_window.close();
                m_running = false;
                break;
            default:
                break;
            }
        }

        if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::E:
                m_player->cInput->up = false;
                break;
            case sf::Keyboard::D:
                m_player->cInput->down = false;
                break;
            case sf::Keyboard::F:
                m_player->cInput->right = false;
                break;
            case sf::Keyboard::S:
                m_player->cInput->left = false;
                break;
            default:
                break;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                // std::cout << "Left mouse button clicked @ ("
                //<< event.mouseButton.x << ',' << event.mouseButton.y
                //<< ')' << '\n';

                spawnBullet(m_player,
                            vec2(event.mouseButton.x, event.mouseButton.y));
            }

            if (event.mouseButton.button == sf::Mouse::Right)
            {
                // std::cout << "Right mouse button clicked @ ("
                //<< event.mouseButton.x << ',' << event.mouseButton.y
                //<< ')' << '\n';

                // TODO call spawnSpecialWeapon here
            }
        }
    }
}

void Game::sLifespan()
{
    for (auto& entity : m_entityManager.getEntities())
    {
        if (!entity->cLifespan)
            continue;

        int  ls    = entity->cLifespan->remaining;
        bool alive = entity->isActive();
        if (ls > 0 && alive)
        {
            entity->cLifespan->remaining--;

            // fade out bullets
            if (entity->tag() == EntityType::bullet)
            {
                float     fadeRate = 1.5f;
                sf::Color fColor   = entity->cShape->circle.getFillColor();
                entity->cShape->circle.setFillColor(sf::Color(
                    fColor.r, fColor.g, fColor.b, fColor.a - fadeRate));

                sf::Color oColor = entity->cShape->circle.getOutlineColor();
                entity->cShape->circle.setOutlineColor(sf::Color(
                    oColor.r, oColor.g, oColor.b, oColor.a - fadeRate));
            }
        }
        else if (ls <= 0)
        {
            entity->destroy();
        }
    }
}

// System: Render/Drawing
void Game::sRender()
{
    m_window.clear();

    // set the position of the shape based the entity's transform->pos
    m_player->cShape->circle.setPosition(m_player->cTransform->pos.x,
                                         m_player->cTransform->pos.y);

    // set the rotation of the shape based on the entity's transform->angle
    m_player->cShape->circle.setRotation(++m_player->cTransform->angle);

    // draw the entity's sf::CircleShape
    m_window.draw(m_player->cShape->circle);

    for (auto e : m_entityManager.getEntities(EntityType::enemy))
    {
        // set the position of the shape based the entity's transform->pos
        e->cShape->circle.setPosition(e->cTransform->pos.x,
                                      e->cTransform->pos.y);

        // set the rotation of the shape based on the entity's transform->angle
        e->cTransform->angle += 2.0f;
        e->cShape->circle.setRotation(e->cTransform->angle);

        // draw the entity's sf::CircleShape
        m_window.draw(e->cShape->circle);
    }

    for (auto b : m_entityManager.getEntities(EntityType::bullet))
    {
        b->cShape->circle.setPosition(b->cTransform->pos.x,
                                      b->cTransform->pos.y);
        m_window.draw(b->cShape->circle);
    }

    m_window.display();
}

void Game::sEnemyVelUpdate()
{
    for (auto& e : m_entityManager.getEntities(EntityType::enemy))
    {
        vec2 enemyVel = m_player->cTransform->pos - e->cTransform->pos;
        e->cTransform->velocity = enemyVel.normalized();
    }
}

void Game::sEnemySpawner()
{
    if (m_currentFrame - m_lastEnemySpawnTime > m_config.enemy.SI)
    {
        spawnEnemy();
    }
}

void Game::sCollision()
{
    // TODO implement all proper collisions between entities
    // be sure to use the collision radius, NOT the shape radius
    for (auto b : m_entityManager.getEntities(EntityType::bullet))
    {
        for (auto e : m_entityManager.getEntities(EntityType::enemy))
        {
            bool collides =
                b->cTransform->pos.dist(e->cTransform->pos) <
                (b->cCollision->radius + e->cCollision->radius);
            if (collides)
            {
                b->destroy();
                e->destroy();
            }
        }
    }

    for (auto e : m_entityManager.getEntities(EntityType::enemy))
    {
        bool collides = m_player->cTransform->pos.dist(e->cTransform->pos) <
                        (m_player->cShape->circle.getRadius() +
                         e->cShape->circle.getRadius());
        if (collides)
        {
            float mx = m_window.getSize().x / 2.0f;
            float my = m_window.getSize().y / 2.0f;
            m_player->cTransform->pos = vec2(mx, my);
        }
        // b->cTransform->pos.dist(e->cTransform->pos) <
        //(b->cShape->circle.getRadius() + e->cShape->circle.getRadius());
    }
}

// respawn the player in the middle of the screen
void Game::spawnPlayer()
{
    // TODO: finish adding all properties of the player with the correct values
    // from the config

    auto  entity = m_entityManager.addEntity(EntityType::player);
    float mx     = m_window.getSize().x / 2.0f;
    float my     = m_window.getSize().y / 2.0f;

    entity->cTransform =
        std::make_shared<CTransform>(vec2(mx, my), vec2(1.0f, 1.0f), 0.0f);
    entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color::White,
                                              sf::Color::Red, 4.0f);
    entity->cInput = std::make_shared<CInput>();
    m_player       = entity;
}

// spawn an enemy at a random position
void Game::spawnEnemy()
{
    auto enemy = m_entityManager.addEntity(EntityType::enemy);

    float vertices = incRand(m_config.enemy.VMIN, m_config.enemy.VMAX);
    float FR       = incRand(0, 255);
    float FG       = incRand(0, 255);
    float FB       = incRand(0, 255);
    float S        = incRand(m_config.enemy.SMIN, m_config.enemy.SMAX);

    // generate random enemy position and check for collision with other
    // enemies.
    vec2 enemyPos = getRandomEnemyCoords(
        m_entityManager.getEntities(EntityType::enemy), m_config.enemy.SR,
        m_window.getSize().x, m_config.enemy.SR,
        m_window.getSize().y - m_config.enemy.SR, m_config.enemy.SR);

    vec2 enemyVel = m_player->cTransform->pos - enemyPos;
    enemyVel.normalizeInPlace();

    enemy->cTransform = std::make_shared<CTransform>(enemyPos, enemyVel, 0.0f);

    enemy->cShape = std::make_shared<CShape>(
        m_config.enemy.SR, vertices, sf::Color(FR, FG, FB),
        sf::Color(m_config.enemy.OR, m_config.enemy.OG, m_config.enemy.OB),
        m_config.enemy.OT);

    enemy->cCollision = std::make_shared<CCollision>(m_config.enemy.CR);

    m_lastEnemySpawnTime = m_currentFrame;
}

// spawn the small enemies when a big one (input entity e) explodes
void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{
    // TODO spawn small enemies at the location of the input enemy e

    // when we craete the smaller enemy, we have to read the values of the
    // original enemy
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const vec2& mousePos)
{
    auto bullet    = m_entityManager.addEntity(EntityType::bullet);
    vec2 bulletDir = mousePos - entity->cTransform->pos;
    bulletDir.normalizeInPlace();

    bullet->cTransform =
        std::make_shared<CTransform>(entity->cTransform->pos, bulletDir, 0);
    bullet->cShape = std::make_shared<CShape>(
        m_config.bullet.SR, m_config.bullet.V,
        sf::Color(m_config.bullet.FR, m_config.bullet.FG, m_config.bullet.FB,
                  255),
        sf::Color(m_config.bullet.OR, m_config.bullet.OG, m_config.bullet.OB,
                  255),
        m_config.bullet.OT);
    bullet->cCollision = std::make_shared<CCollision>(m_config.bullet.CR);
    bullet->cLifespan = std::make_shared<CLifespan>(m_config.bullet.L);
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
    // TODO implement your own special weapon
}

vec2 getRandomEnemyCoords(const EntityVec& enemies, float minX, float maxX,
                          float minY, float maxY, float radius)
{
    float ex = incRand(minX, maxX);
    float ey = incRand(minY, maxY);
    for (auto& e : enemies)
    {
        bool collides = e->cTransform->pos.dist(vec2(ex, ex)) <
                        e->cShape->circle.getRadius() + radius;
        if (collides)
            getRandomEnemyCoords(enemies, minX, maxX, minY, maxY, radius);
    }
    return vec2(ex, ey);
}

float incRand(int min, int max)
{
    return rand() % (max - min + 1) + min;
}
