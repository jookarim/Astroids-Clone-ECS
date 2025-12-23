#pragma once

#include <iostream>
#include "Entity.h"
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <string_view>

using EntityVec = std::vector<std::shared_ptr<Entity>>;
using EntityMap = std::map<std::string, EntityVec>;

class EntityManager
{
private:
	EntityVec m_entities;
	EntityMap m_entityTags;
	uint32_t m_entityID = 0;
	EntityVec m_toAdd;
public:
	void update();
	std::shared_ptr<Entity> addEntity(std::string_view tag);
	void removeEntity(std::shared_ptr<Entity> entity);
	const EntityVec& getEntities() const;
	const EntityVec& getEntities(std::string_view tag) const;
};

