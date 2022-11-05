#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <sys/types.h>


/**
 * This class is used to automatically update the animated sprite acording to
 * various configurations. Can be view as a wrapper for sprite to provide
 * animated functionality.
 */
class AnimationMachine {
    sf::Time elaspedTime;
    sf::Time duration;
    u_int spriteCount;
    u_int spriteSize;
    u_int textureRow;

    sf::Texture &texture;
    sf::Sprite &sprite;

    sf::Sprite getSprite(u_int i);

public:
    /**
     * @param sprite: the sprite to be animated
     * @param texture: the texture used to update the sprite
     * @param spriteCount: number of sprites in the spritesheet
     * @param duration: the duration of the animation
     * @param spriteSize: size of a sprite in the spritesheet
     * @param textureRow: number of row in the texture
     */
    AnimationMachine(sf::Sprite &sprite, sf::Texture &texture,
                     u_int spriteCount, sf::Time duration = sf::seconds(1.f),
                     u_int spriteSize = 128, u_int textureRow = 1);
    /**
     * Update the sprite over time
     */
    void updateAnimation(sf::Time dt);
};
