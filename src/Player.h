#pragma once

#include "Effect.h"
#include "Entity.h"
#include "Enums.h"
#include "SceneNode.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

// [x] Boost tăng tốc
// [x] Boost small size
// [ ] Vỏ chuối
// [ ] Mud
// [ ] Hiệu ứng mù (bãi nước đen)
// [ ] Rocket
// [ ] Bomb
// [ ] Cave // Chuột chũi -> Subway -> cá sấu dưới cống, Thang máy (Che tầm nhìn)
// [ ] Cổng điện
// [ ] Cây cầu
// [ ] Zombie giữa mộ trên đường
// [ ] Trộm chó (trúng là chết luôn)
// [ ] Akshan
// [ ] Dải caro kết thúc màn
// [ ] Bãy caitlyn + R caitlyn
// [ ] Bay lên vũ trụ + điều khiển ufo

/**
 * @brief The Player class
 *
 * Note: character jumps only once each press. That allows user to control the
 * speed (by pressing faster or slower).
 */

class PlayerState;
class Player : public Entity {
    friend class PlayerState;
    friend class JumpingState;
    friend class IdleState;
    friend class StunnedState;
    friend class SpeedBoostingState;
    friend class ObstacleCollidingState;
    friend class InvincibleState;
    friend class CollidingState;
    friend class DyingState;
    friend class DeadState;
    friend class PlayerEffect;

public:
    Player();
    Player(sf::Vector2f position, sf::Vector2f size);

    void           onKeyPressed(sf::Event::KeyEvent);
    void           onCollision(SceneNode *other);
    Category::Type getCategory() const override;
    void           setState(PlayerState *newState);
    void           takeDamage(float damage);
    void           takeFood();
    void           takeSmallSizeBoost();
    void           takeSpeedBoost();
    void           onCollideWithWood(sf::Vector2f velocity);
    bool           isDead();

protected:
    void updateCurrent(sf::Time dt) override;
    void drawCurrent(sf::RenderTarget &target,
                     sf::RenderStates  states) const override;

private:
    bool isJumping() const;

    void updateJump(sf::Time dt);

    void onJumpAnimationFinished();

    void drawHealthBar(sf::RenderTarget &target, sf::RenderStates states) const;

    sf::FloatRect getLocalBounds() const override;

    sf::Vector2f getNearestGridPosition(sf::Vector2f pos) const;

private:
    PlayerState *state;

    sf::FloatRect       localBounds;
    const sf::FloatRect defaultBounds =
        sf::FloatRect(20, 20, GRID_SIZE.x - 40, GRID_SIZE.y - 40);
    Texture::ID jumpTexture, idleTexture, ripTexture;

    float health              = MAX_HEALTH;
    float healthReductionRate = 2;

    const sf::Time sizeBoostDuration = sf::seconds(5);
    sf::Time       sizeBoostTime     = sf::Time::Zero;
    bool           onSizeSmallerBoost       = true;
    sf::FloatRect  sizeBoostBounds =
        sf::FloatRect(25, 25, GRID_SIZE.x - 50, GRID_SIZE.y - 50);

    const sf::Time speedBoostDuration = sf::seconds(5);
    sf::Time       speedBoostTime     = sf::Time::Zero;
    bool           onSpeedBoost       = true;

    const sf::Time invincibleDuration = sf::seconds(3);
    sf::Time       invincibleTime     = sf::Time::Zero;
    bool           isInvincible       = false;

    bool deadFlag = false;

    SceneNode *collidingObstacle = nullptr;
    sf::Vector2f woodVelocity = {0, 0};

    std::string getClassName() const override;
    void saveCurrentNode(std::ostream& out = std::cout) const override;
    void loadCurrentNode(std::istream& in = std::cin) override;
};
