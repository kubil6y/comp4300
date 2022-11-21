#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"

#include <map>
#include <vector>

using EntityVec = std::vector<std::shared_ptr<Entity>>;
using EntityMap = std::map<EntityType, EntityVec>;

class EntityManager
{
private:
    EntityVec m_entities;
    EntityVec m_entitiesToAdd;
    EntityMap m_entityMap;
    size_t    m_totalEntities = 0;

    void removeDeadEntities(EntityVec& vec);

public:
    EntityManager();

    void update();

    std::shared_ptr<Entity> addEntity(EntityType tag);
    const EntityVec&        getEntities();
    const EntityVec&        getEntities(EntityType tag);
};

#endif // !ENTITY_MANAGER_H
