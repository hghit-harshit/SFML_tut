#pragma once
#include <SFML/Graphics.hpp>

class StateManager;

class BaseState
{
    friend class StateManager;

public:
    BaseState(StateManager *l_stateManager)
        : m_stateManager(l_stateManager), m_transcendent(false), m_transparent(false) {}

    virtual ~BaseState() {};

    virtual void OnCreate() = 0;
    virtual void OnDestroy() = 0;

    virtual void Activate() = 0;
    virtual void Deactivate() = 0;

    virtual void Update(const sf::Time &l_time) = 0;
    virtual void Draw() = 0;

    void SetTransparent(const bool l_transparent) { m_transparent = l_transparent; }
    bool IsTransparent() const { return m_transparent; }
    void SetTranscendent(const bool l_transcendent) { m_transcendent = l_transcendent; }
    bool IsTranscendent() const { return m_transcendent; }

    StateManager *GetStateManager() { return m_stateManager; }
    sf::View &GetView() { return m_view; }

protected:
    StateManager *m_stateManager;
    bool m_transparent;
    bool m_transcendent; // basically this indicates whether the state allow other states to update
    sf::View m_view;
};