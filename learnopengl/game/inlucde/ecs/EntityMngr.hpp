#pragma once 
#include <ecs/Entity.h>

class EntityMngr 
{
public:
    Entity Create(std::span<const TypeID> types = {});

    bool Exist(Entity) const noexcept;

    void Destroy(Entity);

    void Clear()

private:
    std::vector<EntityInfo> entityTable;
	std::vector<std::size_t> entityTableFreeEntry;
};

