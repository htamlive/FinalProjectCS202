#pragma once

#include "PlayerCollidable.h"
#include "Entity.h"

class HealthPickup : public virtual PlayerCollidable, public virtual Entity {
private:
    void updateCurrent(sf::Time dt) override;

    void onStartPlayerCollision() override;

    bool shouldSave() const override;

public:
    HealthPickup(sf::Vector2f pos, sf::Vector2f size);

    Category::Type getCategory() const override;

    std::string getClassName() const override;
};

class SpeedPickup : public virtual PlayerCollidable, public virtual Entity {
private:
    void updateCurrent(sf::Time dt) override;

    void onStartPlayerCollision() override;

    bool shouldSave() const override;

public:
    SpeedPickup(sf::Vector2f pos, sf::Vector2f size);

    Category::Type getCategory() const override;

    std::string getClassName() const override;
};

class SmallSizePickup : public virtual PlayerCollidable, public virtual Entity {
private:
    void updateCurrent(sf::Time dt) override;

    void onStartPlayerCollision() override;

    bool shouldSave() const override;

public:
    SmallSizePickup(sf::Vector2f pos, sf::Vector2f size);

    Category::Type getCategory() const override;

    std::string getClassName() const override;
};

class InvinciblePickup : public virtual PlayerCollidable, public virtual Entity {
private:
    void updateCurrent(sf::Time dt) override;

    void onStartPlayerCollision() override;

    bool shouldSave() const override;

public:
    InvinciblePickup(sf::Vector2f pos, sf::Vector2f size);

    Category::Type getCategory() const override;

    std::string getClassName() const override;
};
