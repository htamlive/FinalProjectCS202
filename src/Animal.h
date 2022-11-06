#pragma once

#include "Entity.h"

class Animal : public Entity {
public:
    Animal() = default;

    Animal(sf::Vector2f velocity, float x, float y, float w, float h);

private:
    void drawCurrent(sf::RenderTarget &target, sf::RenderStates state) const override;
};