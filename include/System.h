#pragma once

#include <iostream>

class System
{
public:
	virtual ~System() = default;
	virtual void update(float deltaTime) {}
	virtual void render() {}
};