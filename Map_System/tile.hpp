#pragma once
#include "tile_info.hpp"

struct Tile
{
    TileInfo* m_properties;
    bool m_warp; // is this a wrap tile or not
};