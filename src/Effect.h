#include "SceneNode.h"
#include "AnimationMachine.h"

class Entity;
class Effect : public SceneNode {
    sf::Time duration;
    Entity *entity;
    AnimationMachine animation;
public:
    Effect(Entity *entity, Texture::ID textureID, sf::Vector2f position, sf::Vector2f size, sf::Time duration);
    void updateCurrent(sf::Time dt) override;
    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
    void destroy();
};
