#include "VertexArray.h"

void VertexArray::clear()
{
    m_vertices.clear();
    m_indices.clear();
}

void VertexArray::pushQuad(
    float x, float y,
    float w, float h,
    float r,              
    SDL_Color color)
{
    int baseIndex = (int)m_vertices.size();

    float cx = x + w * 0.5f;
    float cy = y + h * 0.5f;

    SDL_FPoint local[4] = {
        { -w * 0.5f, -h * 0.5f },
        {  w * 0.5f, -h * 0.5f },
        {  w * 0.5f,  h * 0.5f },
        { -w * 0.5f,  h * 0.5f }
    };

    float c = std::cos(r);
    float s = std::sin(r);

    SDL_Vertex v[4];

    for (int i = 0; i < 4; i++)
    {
        float rx = local[i].x * c - local[i].y * s;
        float ry = local[i].x * s + local[i].y * c;

        v[i].position = { cx + rx, cy + ry };
        v[i].color = color;
    }

    v[0].tex_coord = { 0.f, 0.f };
    v[1].tex_coord = { 1.f, 0.f };
    v[2].tex_coord = { 1.f, 1.f };
    v[3].tex_coord = { 0.f, 1.f };

    for (int i = 0; i < 4; i++)
        m_vertices.push_back(v[i]);

    m_indices.push_back(baseIndex + 0);
    m_indices.push_back(baseIndex + 1);
    m_indices.push_back(baseIndex + 2);

    m_indices.push_back(baseIndex + 2);
    m_indices.push_back(baseIndex + 3);
    m_indices.push_back(baseIndex + 0);
}


void VertexArray::draw(SDL_Renderer* renderer, SDL_Texture* texture)
{
    if (m_vertices.empty())
        return;

    SDL_RenderGeometry(
        renderer,
        texture,
        m_vertices.data(),
        (int)m_vertices.size(),
        m_indices.data(),
        (int)m_indices.size()
    );
}
