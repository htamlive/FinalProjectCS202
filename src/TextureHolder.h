#pragma once

#include <memory>
#include <map>

#include <SFML/Graphics/Texture.hpp>

#include "Enums.h"
#include "Consts.h"

/**
 * @brief A class that store texture's related information.
 */
struct SpriteSheet {
    sf::Texture texture;
    unsigned int spriteCount = 0;
    sf::Vector2u spriteSize = {0, 0};
    unsigned int textureRow = 0;
};

/**
 * @brief A singleton that handles textures.
 */
class TextureHolder {
private:
    std::map<Texture::ID, std::unique_ptr<SpriteSheet>> textures;

    TextureHolder() = default;

public:
    TextureHolder(const TextureHolder &) = delete;

    void operator=(const TextureHolder &) = delete;

    static TextureHolder &instance();

    /**
     * Loads a texture containing multiple sprites (spritesheet) from file as an animation sequence of Texture::ID.
     * @param spriteSize is {0, 0} by default (takes the whole texture's size as spriteSize)
     * @param spriteCount is 1 by default, in case texture contains a single sprite (not an animation)
     * @param textureRow is number of rows in the texture, 1 by default
     */
    void load(Texture::ID, const std::string &filename, sf::Vector2u spriteSize = {0, 0},
              unsigned int spriteCount = 1, unsigned int textureRow = 1);

    /**
     * Gets the texture of a Texture::ID.
     * Abort if not found.
     *
     * @return <tt>const sf::Texture &</tt> a reference to the texture.
     */
    sf::Texture const &getTexture(Texture::ID) const;

    /**
     * Gets spritesheet information of a Texture::ID.
     * Abort if not found.
     *
     * @return <tt>const SpriteSheet &</tt>
     */
    SpriteSheet const &get(Texture::ID) const;
};
