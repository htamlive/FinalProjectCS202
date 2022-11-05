#pragma once

#include <memory>
#include <map>

#include <SFML/Graphics/Texture.hpp>

#include "Enums.h"
#include "SpriteStage.h"

/**
 * A singleton that handles textures.
 */
class TextureHolder {
private:
    std::map<Texture::ID, std::vector<std::unique_ptr<sf::Texture>>> textures;

    TextureHolder() = default;

public:
    TextureHolder(const TextureHolder&) = delete;

    void operator=(const TextureHolder&) = delete;

    static TextureHolder &instance();

    /**
     * Loads a texture from file as a stage of an animation sequence. Stage is default to 0 in case Texture::ID is not an animation.
     */
    void load(Texture::ID, const std::string &filename, std::size_t stage);
    /**
     * Loads a series of textures from files as an animation sequence of Texture::ID. If the sequence already exists, it is concatenated.
     *
     * @return <tt>std::size_t</tt> size of the current sequence.
     */
    std::size_t load(Texture::ID, const std::vector<std::string> &filenames);
    /**
     * Gets the texture of a stage of an animation sequence.
     *
     * @return <tt>sf::Texture &</tt> a reference to the texture.
     */
    sf::Texture &get(const SpriteStage &);
    /**
     * Gets the texture of a stage of an animation sequence.
     *
     * @return <tt>const sf::Texture &</tt> a reference to the texture.
     */
    sf::Texture const &get(const SpriteStage &) const;
    /**
     * Gets the size of an animation sequence.
     *
     * @return <tt>std::size_t</tt>
     */
    std::size_t getSpritesSize(Texture::ID) const;
};