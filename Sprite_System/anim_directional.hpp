#pragma once
#include "anim_base.hpp"
class Anim_Directional : public Anim_Base
{
    protected:
        void FrameStep();
        void CropSprite();
        void ReadIn(std::stringstream& l_stream);
};