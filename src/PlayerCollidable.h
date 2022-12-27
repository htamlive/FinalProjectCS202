#pragma once

#include "Player.h"

class PlayerCollidable : public virtual SceneNode {
private:
    virtual void onStartPlayerCollision();

    virtual void onRepeatPlayerCollision();

    virtual void onEndPlayerCollision();

protected:
    bool isCollidingWithPlayer = false;
    Player *player = nullptr;

public:
    using SceneNode::SceneNode;

    void onPlayerCollision(Player &player);

    void updateCurrent(sf::Time dt) override;
};
