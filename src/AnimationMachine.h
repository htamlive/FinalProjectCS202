#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <sys/types.h>

#include "Consts.h"
#include "Enums.h"
#include "TextureHolder.h"


/**
 * This class is used to automatically update the animated sprite according to
 * various configurations. Can be view as a wrapper for sprite to provide
 * animated functionality.
 */
class AnimationMachine {
    Texture::ID id;
    sf::Time elapsedTime;
    sf::Time duration;
    bool loop;

    /**
     * Use std::reference_wrapper to enable operator= on AnimationMachine.
     */
    std::reference_wrapper<SpriteSheet const> sheet;

    /**
     * @param i is a 0-based index
     */
    void getSprite(u_int i, sf::Sprite &sprite) const;

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
    void toSprite(sf::Sprite &sprite) const;

    /**
     * Check if a non-looped animation is finished.
     * @return true if animation is finished, otherwise false
     */
    bool isFinished() const;

    Texture::ID getID() const;
};
