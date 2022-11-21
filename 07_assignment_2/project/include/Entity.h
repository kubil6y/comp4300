#ifndef ENTITY_H
#define ENTITY_H

#include "Components.h"

#include <memory>
#include <string>

enum class EntityType
{
    zero,
    bullet,
    player,
    enemy,
};

class Entity
{
private:
    bool       m_active = true;
    size_t     m_id     = 0;
    EntityType m_tag    = EntityType::zero;

    // constructor and destructor
    Entity(size_t id, EntityType tag);

public:
    // component pointers
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CShape>     cShape;
    std::shared_ptr<CCollision> cCollision;
    std::shared_ptr<CInput>     cInput;
    std::shared_ptr<CScore>     cScore;
    std::shared_ptr<CLifespan>  cLifespan;

    // private member access functions
    bool       isActive() const;
    EntityType tag() const;
    size_t     id() const;
    void       destroy();

    friend class EntityManager;
};

#endif // !ENTITY_H
