#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <cmath>

class VertexArray
{
private:
    std::vector<SDL_Vertex> m_vertices;
    std::vector<int>        m_indices;
public:
    void clear();
    void pushQuad(float x, float y, float w, float h,float r,SDL_Color color);
    void draw(SDL_Renderer* renderer, SDL_Texture* texture = nullptr);
};
