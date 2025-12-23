#pragma once

#include <iostream>
#include "EntityManager.h"
#include "Renderer.h"
#include "System.h"
#include "VertexArray.h"
#include <cmath>

class RenderSystem : public System
{
private:
	EntityManager& m_entityManager;
	Window& m_window;
	VertexArray m_bulletVA;
	VertexArray m_enemyVA;
	VertexArray m_enemyRectVA;
public:
	RenderSystem(EntityManager& entityManager, Window& window);
	~RenderSystem() = default;

	void render() override;
};

