#include "SceneNode.h"
#include "TextureHolder.h"
#include <SFML/Graphics.hpp>

class SpriteNode : public SceneNode {
protected:
    Texture::ID id;
    sf::Vector2f size;
    sf::Sprite sprite;
public:
    void saveCurrentNode(std::ostream &out = std::cout) const override;
    void loadCurrentNode(std::istream &in = std::cin) override;
    bool shouldSave() const override;
    SpriteNode(Texture::ID id);
    SpriteNode(Texture::ID id, sf::Vector2f size);
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    void updateCurrent(sf::Time dt) override;
    std::string getClassName() const override {
        return "SpriteNode";
    }
};
