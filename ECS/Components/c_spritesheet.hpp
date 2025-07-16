#pragma once
#include "c_drawable.hpp"
#include "../../Sprite_System/sprite_sheet.hpp"

class C_SpriteSheet : public C_Drawable
{
    public:
        C_SpriteSheet() : C_Drawable(Component::SpriteSheet),m_spriteSheet(nullptr){};
        ~C_SpriteSheet()
        { if(m_spriteSheet) delete m_spriteSheet;}

        void ReadIn(std::stringstream& l_stream)
        {
            l_stream >> m_sheetName;
        }

        void Create(TextureManager* l_textureManager, const std::string& l_name = "")
        {
            if(m_spriteSheet) return;

            m_spriteSheet = new SpriteSheet(l_textureManager);
            m_spriteSheet->LoadSheet("path + l_name");
        }

        SpriteSheet* GetSpriteSheet(){ return m_spriteSheet;}

        void UpdatePosition(const sf::Vector2f& l_vec)
        {
            m_spriteSheet->SetSpritePosition(l_vec);
        }

        const sf::Vector2u& GetSize()
        {
            return m_spriteSheet->GetSpriteSize();
        }

        void Draw(sf::RenderWindow* l_wind)
        {
            if(!m_spriteSheet)return;
            m_spriteSheet->Draw(l_wind);
        }
    private:
        SpriteSheet* m_spriteSheet;
        std::string m_sheetName;
};