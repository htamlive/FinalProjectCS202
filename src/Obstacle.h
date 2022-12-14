#include "Consts.h"
#include "Enums.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include "TextureHolder.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Obstacle : public SpriteNode {
public:
    Obstacle(sf::Vector2f pos) : SpriteNode(Texture::Obstacle) {
        sprite.setScale(GRID_SIZE.x / sprite.getLocalBounds().width,
                GRID_SIZE.x / sprite.getLocalBounds().width);
        move(pos);
        // Offset the sprite to the center of the grid
        move(0, 10);
    }
    sf::FloatRect getLocalBounds() const override {
        return sprite.getGlobalBounds();
    }
    Category::Type getCategory() const override {
        return Category::Obstacle;
    }
};

class Reward : public SceneNode {
    sf::Sprite sprite;
public:
    Reward(sf::Vector2f pos) {
        sprite.setTexture(TextureHolder::instance().getTexture(Texture::Object));
        sprite.setTextureRect(sf::IntRect(1*16, 2*16, 16, 16));
        sprite.setScale(GRID_SIZE.x / sprite.getLocalBounds().width,
                GRID_SIZE.x / sprite.getLocalBounds().width);
        move(pos);
    }
    sf::FloatRect getLocalBounds() const override {
        return sprite.getGlobalBounds();
    }
    Category::Type getCategory() const override {
        return Category::Reward;
    }
    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override {
        target.draw(sprite, states);
    }
};
