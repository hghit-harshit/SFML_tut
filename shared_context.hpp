#pragma once
class Window;
class EventManager;
class TextureManager;
class Map;

struct SharedContext
{
    SharedContext():m_wind(nullptr),
    m_eventManager(nullptr),
    m_textureManager(nullptr){}
    Window* m_wind;
    EventManager* m_eventManager;
    TextureManager* m_textureManager;
    Map* m_gameMap;
};