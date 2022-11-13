#include "Animal.h"
#include "TextureHolder.h"
#include "Consts.h"

void Animal::drawCurrent(sf::RenderTarget &target, sf::RenderStates state) const {
    // Downcast Vehicle back to sf::Transformable then upcast to sf::Sprite to preserve properties i.e., position, scale, origin, rotation.
    sf::Transformable trans = *this;
    auto sprite = dynamic_cast<sf::Sprite &>(trans);

    animation.toSprite(sprite);
    target.draw(sprite, state);
}

Animal::Animal(sf::Vector2f velocity, float x, float y, float w, float h) : Entity(velocity, x, y, w, h,
                                                                                   Texture::ID::AnimalSprites) {}
