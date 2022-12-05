#pragma once

#include <memory>
#include <map>

#include <SFML/Graphics/Texture.hpp>

#include "Enums.h"
#include "Consts.h"

class Sheet {
public:
    virtual unsigned int getCount() const = 0;

    virtual sf::Texture const &getTexture() const = 0;

    /**
     * @param i is a 0-based index
     */
    virtual sf::Sprite getSprite(unsigned i) const = 0;

    virtual ~Sheet() = default;
};

/**
 * @brief A class that stores texture's related information.
 */
class TextureSheet : public Sheet {
private:
    sf::Texture texture;
    unsigned int spriteCount = 0;
    sf::Vector2u spriteSize = {0, 0};
    unsigned int textureRow = 0;

public:
    TextureSheet(const sf::Texture& texture, unsigned int spriteCount,
                 sf::Vector2u spriteSize, unsigned int textureRow);

    unsigned int getCount() const override;

    sf::Texture const &getTexture() const override;

    /**
     * @param i is a 0-based index
     */
    sf::Sprite getSprite(unsigned i) const override;
};

/**
 * @brief A class that stores information of a part of a texture, with effects on it.
 */
struct SpriteSheet : public Sheet {
    Texture::ID texture{};
    unsigned int startIdx = 0;
    unsigned int endIdx = 0;
    bool mirrorVertical = false;
    bool mirrorHorizontal = false;

    SpriteSheet() = default;

    SpriteSheet(Texture::ID);

    SpriteSheet(Texture::ID, bool mirrorVertical, bool mirrorHorizontal);

    SpriteSheet(Texture::ID, unsigned int index, bool mirrorVertical, bool mirrorHorizontal);

    SpriteSheet(Texture::ID, unsigned int startIdx, unsigned int endIdx, bool mirrorVertical, bool mirrorHorizontal);

    unsigned int getCount() const override;

    sf::Texture const &getTexture() const override;

    /**
     * @param i is a 0-based index
     */
    sf::Sprite getSprite(unsigned i = 0) const override;
};

/**
 * @brief A singleton that handles textures.<br>
 * TextureSheet stores sf::Texture. SpriteSheet represents the sprite cut from a texture.<br>
 * Every Texture::ID can be returned as SpriteSheet. Not all Texture::ID can be returned as TextureSheet.<br>
 */
class TextureHolder {
private:
    std::map<Texture::ID, std::unique_ptr<Sheet>> sheets;

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
     * Adds a SpriteSheet.
     */
    void addSpriteSheet(Texture::ID, const SpriteSheet &);

    /**
     * Gets the texture of a Texture::ID.
     * Abort if not found.
     *
     * @return <tt>const sf::Texture &</tt> a reference to the texture.
     */
    sf::Texture const &getTexture(Texture::ID) const;

    /**
     * Gets a Sheet information of a Texture::ID.
     * Abort if not found.
     *
     * @return <tt>const SpriteSheet &</tt>
     */
    Sheet const &getSheet(Texture::ID) const;
};
