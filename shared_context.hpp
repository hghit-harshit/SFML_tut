#pragma once
class Window;
class EventManager;
class TextureManager;
class Map;
class EntityManager;
struct SharedContext
{
    SharedContext():m_wind(nullptr),
    m_eventManager(nullptr),
    m_textureManager(nullptr),
    m_entityManager(nullptr){}
    Window* m_wind;
    EventManager* m_eventManager;
    TextureManager* m_textureManager;
    Map* m_gameMap;
    EntityManager* m_entityManager;
};