#pragma once

#include "Consts.h"
#include "Enums.h"
#include "SceneNode.h"
#include "Entity.h"
#include "TextureHolder.h"
#include "PlayerState.h"
#include "PlayerCollidable.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Obstacle : public virtual PlayerCollidable {
protected:
    void onStartPlayerCollision() override;
public:
    using PlayerCollidable::PlayerCollidable;

    Category::Type getCategory() const override;

    std::string getClassName() const override;
};

class Rock : public virtual Obstacle, public virtual Entity {
private:
    void updateCurrent(sf::Time dt) override;

public:
    Rock(sf::Vector2f pos, sf::Vector2f size);

    Category::Type getCategory() const override;

    std::string getClassName() const override;

    bool shouldSave() const override;
};