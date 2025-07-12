#pragma once
#include "SFML/Graphics/Texture.hpp"
#include "resource_manager.hpp"
#include <iostream>
/**
 * @brief It manages texture(wow shocker)
 * 
 */
class TextureManager : public ResourceManager<TextureManager,sf::Texture>
{
    public :
        TextureManager():ResourceManager("resources/textures.cfg"){}

        sf::Texture* Load(const std::string& l_path)
        {
            sf::Texture* texture = new sf::Texture();
            if(!texture->loadFromFile(l_path))//Utils::GetWorkingDirectory() + l_path
            {
                delete texture;
                texture = nullptr;
                std::cerr << "Cannot load texture from " << l_path << '\n';
            }
            return texture;
        }
};