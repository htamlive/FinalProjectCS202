#include "Vehicle.h"
#include "TextureHolder.h"
#include "Consts.h"

void Vehicle::drawCurrent(sf::RenderTarget &target, sf::RenderStates state) const {
    // Downcast Vehicle back to sf::Transformable then upcast to sf::Sprite to preserve properties i.e., position, scale, origin, rotation.
    sf::Transformable trans = *this;
    auto sprite = dynamic_cast<sf::Sprite &>(trans);

    sprite.setTexture(TextureHolder::instance().get(spriteStage), true);
    target.draw(sprite, state);
}

void Vehicle::updateCurrent(sf::Time dt) {
    // TODO: time between sprites is currently a constant. does it need to be custom?
    spriteStage.next((int) (dt / TIME_BETWEEN_SPRITE));

    if (!stop) {
        auto pos = getPosition();
        pos.x += getVelocity().x * (float) dt.asSeconds();
        pos.y += getVelocity().y * (float) dt.asSeconds();
        setPosition(pos);
    }
}

void Vehicle::onLightChanged() {
    stop = !stop;
}

Vehicle::Vehicle() : stop(false) {}

Vehicle::Vehicle(sf::Vector2f velocity, float x, float y, float w, float h) : stop(false),
                                                                              Entity(Texture::ID::VehicleSprites,
                                                                                     velocity, x, y, w, h) {}
