#pragma once
#include "../Core/s_base.hpp"
#include "../../Window_System/window.hpp"
#include "../../direction.hpp"

class S_Renderer : public S_Base
{
    public : 
        S_Renderer(SystemManager* l_systemManager);
        ~S_Renderer();

        void Update(float l_dt);
        void HandleEvent(const EntityId& l_entity, const EntityEvent& l_event);
        void Notify(const Message& l_message);
        void Render(Window* l_wind, unsigned int l_layer);

    private:
        void SetSheetDirection(const EntityId& l_entity, const Direction& l_dir);
        void SortDrawables();
};