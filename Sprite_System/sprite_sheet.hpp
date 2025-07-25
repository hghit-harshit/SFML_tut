#pragma once
#include <SFML/Graphics.hpp>
#include "../Resource_System/texture_manager.hpp"
#include "anim_base.hpp"
#include "../direction.hpp"
#include "anim_directional.hpp"

using Animations = std::unordered_map<std::string,Anim_Base*>;

class SpriteSheet
{
    public:

        SpriteSheet(TextureManager* l_textMgr);
        ~SpriteSheet();

        void CropSprite(const sf::IntRect& l_rect);
        // Baic getters setter
        sf::Vector2u GetSpriteSize() const;
        sf::Vector2f GetSpritePosition() const;

        void SetSpriteSize(const sf::Vector2u& l_size);
        void SetSpritePosition(const sf::Vector2f& l_pos);

        void SetDirection(const Direction& l_dir);
        Direction GetDirection() const;
        void SetSheetPadding(const sf::Vector2f& l_padding);
        void SetSpriteSpacing(const sf::Vector2f& l_spacing);
        sf::Vector2f GetSheetPadding()const;
        sf::Vector2f GetSpriteSpacing()const;
        sf::FloatRect GetSpriteBounds()const;
        
        bool LoadSheet(const std::string& l_file);
        void ReleaseSheet();

        Anim_Base* GetCurrentAnim();
        bool SetAnimation(const std::string& l_name,
        const bool& l_play = false,
        const bool& l_loop = false);
        
        void Update(const float& l_dt);
        void Draw(sf::RenderWindow* l_wind);
    private:
        std::string m_texture;
        sf::Sprite m_sprite;
        sf::Vector2u m_spriteSize;
        sf::Vector2f m_spriteScale;
        Direction m_direction;

        std::string m_animType;
        Animations m_animations;
        Anim_Base* m_animationCurrent;
        TextureManager* m_textureManager;
};