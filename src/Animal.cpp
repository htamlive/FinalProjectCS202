#include "Animal.h"
#include "TextureHolder.h"
#include "Consts.h"

void Animal::drawCurrent(sf::RenderTarget &target, sf::RenderStates state) const {
    // Downcast Vehicle back to sf::Transformable then upcast to sf::Sprite to preserve properties i.e., position, scale, origin, rotation.
    sf::Transformable trans = *this;
    auto sprite = dynamic_cast<sf::Sprite &>(trans);

    sprite.setTexture(TextureHolder::instance().get(spriteStage), true);
    target.draw(sprite, state);
}

void Animal::updateCurrent(sf::Time dt) {
    // TODO: time between sprites is currently a constant. does it need to be custom?
    spriteStage.next((int) (dt / TIME_BETWEEN_SPRITE));
    Entity::updateCurrent(dt);
}

Animal::Animal(sf::Vector2f velocity, float x, float y, float w, float h) : Entity(Texture::ID::AnimalSprites,
                                                                                   velocity, x, y, w, h) {}
