#pragma once

#include "Entity.h"
#include "Enums.h"
#include "SceneNode.h"
#include <SFML/Graphics/Rect.hpp>
#include "Effect.h"

// [ ] Boost tăng tốc
// [ ] Boost small size
// [ ] Mud
// [ ] Rocket
// [ ] Bomb
// [ ] Cave // Chuột chũi -> Subway -> cá sấu dưới cống, Thang máy
// [ ] Cổng điện
// [ ] Cây cầu
// [ ] Trộm chó (trúng là chết luôn)
// [ ] Akshan
// [ ] Dải caro kết thúc màn
// [ ] Bãy caitlyn + R caitlyn
// [ ] Bay lên vũ trụ + điều khiển ufo

/**
 * @brief The Player class
 *
 * Note: character jumps only once each press. That allows user to control the speed (by pressing faster or slower).
 */

class PlayerState;
class Player : public Entity {
    friend class PlayerState;
    friend class JumpingState;
    friend class IdleState;
    friend class SmallSizeBoostingState;
    friend class SpeedBoostingState;
    friend class CollidingState;
public:
    Player();
    Player(sf::Vector2f position, sf::Vector2f size);

    void onKeyPressed(sf::Event::KeyEvent);
    void onCollision(SceneNode *other);
    Category::Type getCategory() const override;
    void setState(PlayerState *newState);
    void takeDamage(int damage);

private:
    void updateCurrent(sf::Time dt) override;

    bool isJumping() const;

    void updateJump(sf::Time dt);

    void onJumpAnimationFinished();

    PlayerState *state;
    Texture::ID jumpTexture, idleTexture;
    sf::Vector2f staticPos;
    sf::Vector2f preJumpPos;
    int health = 3;
    bool onSizeBoost = false;
    bool onSpeedBoost = false;
};
