#include "SpriteNode.h"
#include <SFML/Graphics/Sprite.hpp>

SpriteNode::SpriteNode(Texture::ID id, sf::Vector2f size) : id(id), size(size) {
    sprite.setTexture(TextureHolder::instance().getTexture(id));
    sprite.setScale(size.x / sprite.getLocalBounds().width, size.y / sprite.getLocalBounds().height);
}

SpriteNode::SpriteNode(Texture::ID id) : id(id) {
    sprite.setTexture(TextureHolder::instance().getTexture(id));
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void SpriteNode::updateCurrent(sf::Time dt) {
    // Do nothing
}

void SpriteNode::saveCurrentNode(std::ostream &out) const {
    SceneNode::saveCurrentNode(out);
    std::cout << "Save spriteNode" << std::endl;
    out << id << std::endl;
    out << size.x << " " << size.y << std::endl;
}

void SpriteNode::loadCurrentNode(std::istream &in) {
    SceneNode::loadCurrentNode(in);
    int i;
    in >> i;
    in >> size.x >> size.y;
    std::cout << "Size: " << size.x << " " << size.y << std::endl;
    id = (Texture::ID)(i);
    sf::Sprite newSprite(TextureHolder::instance().getTexture(id));
    std::cout << "Scale: " << size.x / newSprite.getLocalBounds().width << " " << size.y / newSprite.getLocalBounds().height << std::endl;
    newSprite.setScale(size.x / newSprite.getLocalBounds().width, size.y / newSprite.getLocalBounds().height);
    sprite = newSprite;

}

bool SpriteNode::shouldSave() const {
    return true;
}
