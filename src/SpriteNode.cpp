#include "SpriteNode.h"

SpriteNode::SpriteNode(Texture::ID id, sf::Vector2f size) {
    sprite.setTexture(TextureHolder::instance().getTexture(id));
    sprite.setScale(size.x / sprite.getLocalBounds().width, size.y / sprite.getLocalBounds().height);
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void SpriteNode::updateCurrent(sf::Time dt) {
    // Do nothing
}
