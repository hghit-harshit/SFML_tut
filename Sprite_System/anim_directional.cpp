#include "anim_directional.hpp"
#include "sprite_sheet.hpp"

void Anim_Directional::CropSprite()
{
    // First, we construct a rectangle. Its top-left corner position is the sprite size multiplied 
    // by the current frame on the x axis and the sprite size multiplied by the sum of the 
    // current animation row and the sprite sheet direction on the y axis. Because the 
    // direction enumeration maps the directions to numerical values of either 0 or 1, it 
    // makes obtaining the row for the correct direction really easy
    sf::IntRect rect(
        m_spriteSheet->GetSpriteSize().x*m_frameCurrent,
        m_spriteSheet->GetSpriteSize().y*
        (m_frameRow + (short)m_spriteSheet->GetDirection()),
        m_spriteSheet->GetSpriteSize().x,
        m_spriteSheet->GetSpriteSize().y
    );
    m_spriteSheet->CropSprite(rect);
}

void Anim_Directional::FrameStep()
{
    if(m_frameStart < m_frameEnd){m_frameCurrent++;}
    else {--m_frameCurrent;}

    if ((m_frameStart < m_frameEnd && m_frameCurrent > m_frameEnd)||
    (m_frameStart > m_frameEnd && m_frameCurrent < m_frameEnd))
    {
        if (m_loop){ m_frameCurrent = m_frameStart; return; }
        m_frameCurrent = m_frameEnd;
        Pause();
    }
}

void Anim_Directional::ReadIn(std::stringstream& l_stream)
{
    l_stream >> m_frameStart >> m_frameEnd >> m_frameRow >>
    m_frameTime >> m_frameActionStart >> m_frameActionEnd;
}