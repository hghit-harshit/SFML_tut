#pragma  once
#include "../shared_context.hpp"
#include "../State_System/base_state.hpp"
#include "../State_System/state_manager.hpp"
#include "../Entity_Component_System/entity_manager.hpp"
#include "tile.hpp"
#include <unordered_map>

//enum Sheet{ Tile_Size = 32, Sheet_Width = 256, Sheet_Height = 256 };

using TileMap = std::unordered_map<unsigned int,Tile*>;
using TileSet = std::unordered_map<TileId,TileInfo*>;

class Map
{
    public: 
        Map(SharedContext* l_context, BaseState* l_currentState);
        ~Map();
        
        Tile* GetTile(unsigned int l_x,unsigned int l_y);
        unsigned int GetTileSize();
        TileInfo* GetDefaultTile();
        float GetGravity()const;
        const sf::Vector2u& GetMapSize()const;
        const sf::Vector2f& GetPlayerStart()const;
        void LoadMap(const std::string& l_path);
        void LoadNext();
        void Update(float l_dt);
        void Draw();

    private:
        // for converting 2d coords into 1d units
        unsigned int ConvertCoords(unsigned int l_x,unsigned int l_y);
        void LoadTiles(const std::string& l_path);
        void PurgeMap();
        void PurgeTileSet();

        TileSet m_tileSet;
        TileMap m_tileMap;
        sf::Sprite m_background;
        TileInfo m_defaultTile;
        sf::Vector2u m_maxMapsize;
        sf::Vector2f m_playerStart;
        unsigned int m_tileCount;
        unsigned int m_tileSetCount;
        float m_mapGravity;
        std::string m_nextMap;
        bool m_loadNextMap;
        std::string m_backgroundTexture;
        BaseState* m_currentState;
        SharedContext* m_context;
    
};