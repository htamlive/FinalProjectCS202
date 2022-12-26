#pragma once

#include "Effect.h"
#include "Entity.h"
#include "Enums.h"
#include "SceneNode.h"
#include "Effects.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

// [x] Boost tăng tốc
// [x] Boost small size
// [x] Bị xỉn xong đi ngược
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

    friend class CollidingState;

    friend class ObstacleCollidingState;

    friend class InvincibleState;

    friend class DyingState;

    friend class DeadState;

    friend class PlayerEffect;

public:
    Player();

    Player(sf::Vector2f position, sf::Vector2f size);

    void onKeyPressed(sf::Event::KeyEvent);

    Category::Type getCategory() const override;

    void setState(PlayerState *newState);

    void addHealth(float delta);

    bool isDead();

    void addEffect(std::unique_ptr<Effect> effect);

    bool isInvincible() const;

    sf::Vector2f getDirectionVec() const;

    void addPlatformVelocity(sf::Vector2f velocity);

protected:
    void updateCurrent(sf::Time dt) override;

    void drawCurrent(sf::RenderTarget &target,
                     sf::RenderStates states) const override;

private:
    void drawHealthBar(sf::RenderTarget &target, sf::RenderStates states) const;

    sf::Vector2f getNearestGridPosition(sf::Vector2f pos) const;

    void applyEffects(sf::Time dt);

private:
    Texture::ID jumpTexture, idleTexture, ripTexture;

    PlayerState *state;

    float jumpDurationScale = 1;
    sf::Vector2i distanceScale = {1, 1};
    int invincibleBoostCount = 0;
    std::vector<std::tuple<std::unique_ptr<Effect>, sf::Time, unsigned int>> effects;

    sf::Vector2f platformVelocity = {0, 0};
    float health = MAX_HEALTH;
    bool deadFlag = false;
};