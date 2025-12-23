#pragma once

#include <iostream>

class Scene
{
public:
    virtual ~Scene() = default;

    virtual void init() = 0;
    virtual void handleEvents() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
};
