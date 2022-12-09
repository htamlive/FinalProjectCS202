#include "SceneNode.h"
#include "TextureHolder.h"
#include <SFML/Graphics.hpp>

class SpriteNode : public SceneNode {
    sf::Sprite sprite;
public:
    SpriteNode(Texture::ID id, sf::Vector2f size);
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    void updateCurrent(sf::Time dt) override;
};
