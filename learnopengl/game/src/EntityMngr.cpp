#include <esc/Entity.h>

Entity EntityMngr::Create(std::span<const TypeID> types)
{
    
}

bool EntityMngr::Exist(Entity) const noexcept
{
    
}

void EntityMngr::Destroy(Entity)
{
    
}

void EntityMngr::Clear() 
{
    entityTableFreeEntry.clear();
	entityTable.clear();
}