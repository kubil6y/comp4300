#include "Game.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <fstream>
#include <iostream>

// constructor, takes in game config
Game::Game(const std::string& config)
{
    init(config);
}

void Game::init(const std::string& path)
{
    // TODO: read in config file here
    //       use the premade PlayerConfig, EnemyConfig, BulletConfig variables
    //       remember to add fullscreen mode 0,1
    std::ifstream fin(path);
    // fin >> m_playerConfig.SR >> m_playerConfig.CR;

    // set up default window parameters
    m_window.create(sf::VideoMode(1280, 720), "Assignment 2");
    m_window.setFramerateLimit(60);

    spawnPlayer();
}

void Game::run()
{
    // TODO: add pause functionality in here
    //       some systems should function while paused (rendering)
    //       some system should not (movement, input)
    while (m_running)
    {
        m_entities.update();

        // TODO
        if (!m_paused)
        {
        }

        sEnemySpawner();
        sMovement();
        sCollision();
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
    // TODO
}

void Game::sMovement()
{
    // TODO implement all entity movement in this function
    // you should read the m_player->cInput component to determine if the player
    // is moving

    // TODO implement player movement
    // NOTE at the start of each frame set the velocity of the objects to zero
    m_player->cTransform->velocity = {0.0f, 0.0f};

    if (m_player->cInput->up)
    {
        m_player->cTransform->velocity.y = -5;
    };

    // sample movement speed update
    m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
    m_player->cTransform->pos.y += m_player->cTransform->velocity.y;
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
    while (m_window.isOpen())
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
            case sf::Keyboard::W:
                std::cout << "W key is pressed" << '\n';
                m_player->cInput->up = true;
                break;
            default:
                break;
            }
        }

        if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::W:
                std::cout << "W key is released" << '\n';
                m_player->cInput->up = false;
                break;
            default:
                break;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Left mouse button clicked @ ("
                          << event.mouseButton.x << ',' << event.mouseButton.y
                          << ')' << '\n';

                // TODO call spawnBullet here
                spawnBullet(m_player,
                            Vec2(event.mouseButton.x, event.mouseButton.y));
            }

            if (event.mouseButton.button == sf::Mouse::Right)
            {
                std::cout << "Right mouse button clicked @ ("
                          << event.mouseButton.x << ',' << event.mouseButton.y
                          << ')' << '\n';

                // TODO call spawnSpecialWeapon here
            }
        }
    }
}

void Game::sLifespan()
{
    // TODO implement all lifespan functionality
    // for all entities
    //      if entity has no lifespan component, skip it
    //      if entity has > 0 remaining lifespan, subtract 1
    //      if it has lifespan and is alive
    //          scale its alpha channel properly
    //      if it has lifespan and is time is up
    //          destroy the entity
}

// System: Render/Drawing
void Game::sRender()
{
    // TODO change the code below to draw all of the entities
    //      same drawing of the player Entity that we have created
    m_window.clear();

    // set the position of the shape based the entity's transform->pos
    m_player->cShape->circle.setPosition(m_player->cTransform->pos.x,
                                         m_player->cTransform->pos.y);

    // set the rotation of the shape based on the entity's transform->angle
    m_player->cTransform->angle += 1.0f;
    m_player->cShape->circle.setRotation(m_player->cTransform->angle);

    // draw the entity's sf::CircleShape
    m_window.draw(m_player->cShape->circle);

    // ---
    for (auto e : m_entities.getEntities())
    {
        // set the position of the shape based the entity's transform->pos
        e->cShape->circle.setPosition(e->cTransform->pos.x,
                                      e->cTransform->pos.y);

        // set the rotation of the shape based on the entity's transform->angle
        e->cTransform->angle += 1.0f;
        e->cShape->circle.setRotation(e->cTransform->angle);

        // draw the entity's sf::CircleShape
        m_window.draw(e->cShape->circle);
    }
    // ---

    m_window.display();
}

void Game::sEnemySpawner()
{
    // TODO code which implements enemy spawning should go here
    //
    // use m_currentFrame - m_lastEnemySpawnTime to determine
    // how long it hsa been since the last enemy spawned

    if (m_currentFrame - m_lastEnemySpawnTime > 100) // fix it
    {
        spawnEnemy();
    }
}

void Game::sCollision()
{
    // TODO implement all proper collisions between entities
    // be sure to use the collision radius, NOT the shape radius
    for(auto b : m_entities.getEntities("bullet"))
    {
        for(auto e : m_entities.getEntities("enemy"))
        {
            // TODO check collision
        }
    }
}

// respawn the player in the middle of the screen
void Game::spawnPlayer()
{
    // TODO: finish adding all properties of the player with the correct values
    // from the config

    // we create every entity by calling EntityManager.addEntity(tag)
    // this returns a std::shared_ptr<Entity>, so we use 'auto' to save typing
    auto entity = m_entities.addEntity("player");

    // give this entity a Transform so it spawns at (200, 200)
    // with velocity (1,1) and angle 0
    float mx = m_window.getSize().x / 2.0f;
    float my = m_window.getSize().y / 2.0f;
    entity->cTransform =
        std::make_shared<CTransform>(Vec2(mx, my), Vec2(1.0f, 1.0f), 0.0f);

    // the Entity's shape will have radius 32, 8 sides, dark grey fill, and red
    // outline of thickness 4
    // instead of 32.0f -> m_playerConfig.SR  (SR:Shape Radius)
    entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10),
                                              sf::Color(255, 0, 0), 4.0f);

    // add an input component to the player so that we can use inputs
    entity->cInput = std::make_shared<CInput>();

    // since we want this Entity to be our player, set our Game's player
    // variable to be this Entity, This goes slightly against EntityManager
    // paradigm, but we use the player so much it's worth it
    m_player = entity;
}

// spawn an enemy at a random position
void Game::spawnEnemy()
{
    // TODO make sure the enemy is spawned properly with the m_enemyConfig
    // variables. The enemy must be spawned completely within the bounds of the
    // window

    // ---
    auto entity = m_entities.addEntity("enemy");

    float ex = rand() % m_window.getSize().x; // make it random
    float ey = rand() % m_window.getSize().y; // make it random

    entity->cTransform =
        std::make_shared<CTransform>(Vec2(ex, ey), Vec2(1.0f, 1.0f), 0.0f);

    entity->cShape = std::make_shared<CShape>(16.0f, 3, sf::Color(0, 0, 255),
                                              sf::Color(255, 255, 255), 4.0f);
    // ---

    // record when the most recent enemy was spawned
    m_lastEnemySpawnTime = m_currentFrame;
}

// spawn the small enemies when a big one (input entity e) explodes
void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{
    // TODO spawn small enemies at the location of the input enemy e

    // when we craete the smaller enemy, we have to read the values of the
    // original enemy
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos)
{
    // TODO implement the spawning of a bullet which travels toward target
    //      - bullet speed is given by a scalar speed
    //      - you must set the velocity by using formula in notes

    // TODO FIX
    auto bullet        = m_entities.addEntity("bullet");
    bullet->cTransform = std::make_shared<CTransform>(mousePos, Vec2(0, 0), 0);
    bullet->cShape = std::make_shared<CShape>(10, 8, sf::Color(255, 255, 255),
                                              sf::Color(255, 0, 0), 2);
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
    // TODO implement your own special weapon
}
