#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <sys/types.h>

#include "Consts.h"
#include "Enums.h"
#include "TextureHolder.h"


/**
 * This Class is mainly to keep track of the animation of a sprite. The Class
 * is short-lived and lightweight so that it can be switched out quickly and
 * replace with other animation.
 */
class AnimationMachine {
    Texture::ID id;
    sf::Time elapsedTime;
    sf::Time duration;
    bool loop;

    /**
     * @param i is a 0-based index
     */
    sf::Sprite getSprite(unsigned i) const;
    SpriteSheet const &getSheet() const;

public:
    /**
     * @param textureID ID of the texture
     * @param duration the duration of the animation
     * @param loop true to loop animation, otherwise false
     */
    AnimationMachine(Texture::ID textureID, sf::Time duration, bool loop);

    /**
     * Update the stage of the animation over time
     *
     * @param dt delta time
     */
    void update(sf::Time dt);

    /**
     * Apply texture of current stage onto sprite
     *
     * @param sprite reference to the sprite
     */
    sf::Sprite toSprite() const;

    /**
     * Check if a non-looped animation is finished.
     * @return true if animation is finished, otherwise false
     */
    bool isFinished() const;

    Texture::ID getID() const;
};
