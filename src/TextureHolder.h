#pragma once

#include <memory>
#include <map>

#include <SFML/Graphics/Texture.hpp>

#include "Enums.h"
#include "Consts.h"

struct SpriteSheet {
    std::unique_ptr<sf::Texture> texture = nullptr;
    unsigned int spriteCount = 0;
    unsigned int spriteSize = 0;
    unsigned int textureRow = 0;
};

/**
 * A singleton that handles textures.
 */
class TextureHolder {
private:
    std::map<Texture::ID, SpriteSheet> textures;

    TextureHolder() = default;

public:
    TextureHolder(const TextureHolder &) = delete;

    void operator=(const TextureHolder &) = delete;

    static TextureHolder &instance();

    /**
     * Loads a texture containing multiple sprites (spritesheet) from file as an animation sequence of Texture::ID.
     *
     * @param spriteCount is 1 by default, in case texture contains a single sprite (not an animation).
     */
    void load(Texture::ID, const std::string &filename, unsigned int spriteCount = 1,
              unsigned int spriteSize = DEF_SPRITE_SIZE, unsigned int textureRow = 1);

    /**
     * Gets the texture of a Texture::ID.
     *
     * @return <tt>const sf::Texture &</tt> a reference to the texture.
     */
    sf::Texture const &getTexture(Texture::ID) const;

    /**
     * Gets spritesheet information of a Texture::ID.
     *
     * @return <tt>const SpriteSheet &</tt>
     */
    SpriteSheet const &get(Texture::ID) const;
};