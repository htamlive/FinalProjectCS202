#pragma once

#include "Entity.h"

// TODO: player currently only has 1 animation (walk).
// TODO: player currently only walks, not jumps.
class Player : public Entity {
public:
    Player();

    Player(float speed, float x, float y, float w, float h);

    void onKeyPressed(sf::Event::KeyEvent);

    void onKeyReleased(sf::Event::KeyEvent);

private:
    void drawCurrent(sf::RenderTarget &target, sf::RenderStates state) const override;

    void updateCurrent(sf::Time dt) override;

    float speed;
};