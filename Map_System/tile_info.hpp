#pragma once
#include "../shared_context.hpp"
#include "../Resource_System/texture_manager.hpp"
#include <SFML/Graphics.hpp>
#include <string>

enum Sheet{Tile_Size = 32, Sheet_Width = 256, Sheet_Height = 256};
using TileId = unsigned int;

struct TileInfo
{
    
    TileInfo(SharedContext* l_context,
    const std::string& l_texture = "", TileId l_id = 0)
    :m_context(l_context),m_id(0),m_deadly(false)
    {
        TextureManager* tmgr = l_context->m_textureManager;

        if(l_texture == "") {m_id = l_id; return;}

        if(!tmgr->RequireResource(l_texture)){return;}

        m_texture = l_texture;
        m_id = l_id;

        m_sprite.setTexture(*tmgr->GetResource(m_texture));
        sf::IntRect tileBoundaries(m_id%(Sheet::Sheet_Width/Sheet::Tile_Size)* Sheet::Tile_Size,
        m_id/(Sheet::Sheet_Height/Sheet::Tile_Size)*Sheet::Tile_Size,
        Sheet::Tile_Size,Sheet::Tile_Size);

        m_sprite.setTextureRect(tileBoundaries);
    }

    ~TileInfo()
    {
        if(m_texture == "") return;
        m_context->m_textureManager->ReleaseResource(m_texture);
    }
    sf::Sprite m_sprite;
    
    TileId m_id;
    std::string m_name;
    sf::Vector2f m_friction;
    bool m_deadly;

    SharedContext* m_context;
    std::string m_texture;

};