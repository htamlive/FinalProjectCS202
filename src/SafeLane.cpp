#include "SafeLane.h"
#include "Consts.h"
#include "TextureHolder.h"

SafeLane::SafeLane() : height(0), texture(Texture::ID::SafeLane) {
    setPosition(0, 0);
}

SafeLane::SafeLane(float y, Texture::ID texture) : height(DEF_LANE_HEIGHT), texture(texture) {
    setPosition(0, y);
}

SafeLane::SafeLane(float y, float height, Texture::ID texture) : height(height), texture(texture) {
    setPosition(0, y);
}

void SafeLane::setLaneHeight(float newHeight) {
    height = newHeight;
}

void SafeLane::setPosY(float y) {
    setPosition(0, y);
}

float SafeLane::getTopY() const {
    return getPosition().y;
}

float SafeLane::getBottomY() const {
    return getPosition().y + height;
}

void SafeLane::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    auto sprite = TextureHolder::instance().getSheet(texture).getSprite(0);
    // Set scale to match the height of the road
    auto scaleFactor = height / (float) sprite.getGlobalBounds().height;
    sprite.setScale(sprite.getScale().x * scaleFactor, sprite.getScale().y * scaleFactor);

    for (float i = 0; i < (float) WINDOW_VIDEO_MODE.width; i += sprite.getLocalBounds().width) {
        sprite.setPosition(i, 0);
        target.draw(sprite, states);
    }
}
