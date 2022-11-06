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
    sf::Time elapsedTime;
    sf::Time duration;

    SpriteSheet const &sheet;

    void getSprite(u_int i, sf::Sprite &sprite) const;

public:
    /**
     * @param textureID: ID of the texture
     * @param duration: the duration of the animation
     */
    explicit AnimationMachine(Texture::ID textureID, sf::Time duration = DEF_ANIMATION_DURATION);

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
};
