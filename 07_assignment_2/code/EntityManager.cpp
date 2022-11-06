#include "EntityManager.h"

EntityManager::EntityManager()
{
}

void EntityManager::update()
{
    // TODO Add entities from m_entitiesToAdd to the proper location(s)
    //      - Add them to the vector of all entities
    //      - Add them to the vector inside the map, with the tag as a key
    for (auto e : m_entitiesToAdd)
    {
        m_entities.push_back(e);
        m_entityMap[e->tag()].push_back(e);
    }
    m_entitiesToAdd.clear();

    // Remove dead entities from the vector of all entities
    removeDeadEntities(m_entities);

    // Remove dead entities from each vector in the entity map
    // C++17 way of iterating through [key,value] pairs in a map
    for (auto& [tag, entityVec] : m_entityMap)
    {
        removeDeadEntities(entityVec);
    }
}

void EntityManager::removeDeadEntities(EntityVec& vec)
{
    // TODO remove all dead entities from the input vector
    // this is called by the update() function
    for (auto e : vec)
    {
        if (!e->isActive())
        {
            // remove from vec consider std::remove_it 
        }
    }
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
    auto entity = std::make_shared<Entity>(m_totalEntities++, tag);
    m_entitiesToAdd.push_back(entity);
    return entity;
}

const EntityVec& EntityManager::getEntities()
{
    return m_entities;
}

const EntityVec& EntityManager::getEntities(const std::string& tag)
{
    return m_entityMap[tag];
}
