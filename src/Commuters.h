#pragma once

#include "Entity.h"
#include "Light.h"
#include "Obstacle.h"
#include "PlayerState.h"

class Enemy : public virtual PlayerCollidable {
protected:
    void onStartPlayerCollision() override;

public:
    using PlayerCollidable::PlayerCollidable;

    Category::Type getCategory() const override;

    std::string getClassName() const override;
};

class Animal : public virtual Enemy, public virtual Entity {
private:
    void updateCurrent(sf::Time dt) override;

public:
    using Entity::Entity;
    std::string getClassName() const override;
    Category::Type getCategory() const override;
};

class Vehicle : public virtual Enemy, public virtual Obstacle, public virtual Entity, public LightObserver {
private:
    void onStartPlayerCollision() override;

    void updateCurrent(sf::Time dt) override;

public:
    using Entity::Entity;

    void onLightChanged() override;

    Category::Type getCategory() const override;

    std::string getClassName() const override;

private:
    sf::Vector2f tmpVelocity = {0, 0};
};

class Water : public virtual PlayerCollidable, public virtual Entity {
private:
    bool isPlayerInWater = false;
    StopOnCommandEffect *damageEffect = nullptr;
    Texture::ID startTexture, midTexture, endTexture;
    unsigned int squareCount;

    void onStartPlayerCollision() override;

    void onRepeatPlayerCollision() override;

    void updateCurrent(sf::Time dt) override;

    void drawCurrent(sf::RenderTarget &target, sf::RenderStates state) const override;

public:
    Water();

    Water(Texture::ID startTexture, Texture::ID midTexture, Texture::ID endTexture, sf::Vector2f position,
          sf::Vector2f sizePerSquare, unsigned int squareCount, sf::Vector2f velocity);

    Category::Type getCategory() const override;

    std::string getClassName() const override;
};
