#include "Player.h"
#include "TextureHolder.h"
#include "Consts.h"
#include "AudioController.h"

void Player::drawCurrent(sf::RenderTarget &target, sf::RenderStates state) const {
    // Downcast Vehicle back to sf::Transformable then upcast to sf::Sprite to preserve properties i.e., position, scale, origin, rotation.
    sf::Transformable trans = *this;
    auto sprite = dynamic_cast<sf::Sprite &>(trans);

    animation.toSprite(sprite);
    target.draw(sprite, state);
}

void Player::updateCurrent(sf::Time dt) {
    if (animation.getID() == Texture::ID::JumpingSprites && animation.isFinished()) {
        onJumpAnimationFinished();
    }
    calVelocity(dt);

    Entity::updateCurrent(dt);
}

Player::Player() { destination = getPosition(); }

Player::Player(float x, float y, float w, float h) : Entity({0, 0}, x, y, w, h, Texture::ID::StandingSprites,
                                                            JUMP_DURATION, false) {
    destination = getPosition();
}

void Player::onKeyPressed(sf::Event::KeyEvent event) {
    if (!isJumping()) {
        switch (event.code) {
            case sf::Keyboard::W:
            case sf::Keyboard::Up:
                jump({destination.x, destination.y - GRID_SIZE.y});
                break;
            case sf::Keyboard::S:
            case sf::Keyboard::Down:
                jump({destination.x, destination.y + GRID_SIZE.y});
                break;
            case sf::Keyboard::A:
            case sf::Keyboard::Left:
                jump({destination.x - GRID_SIZE.x, destination.y});
                break;
            case sf::Keyboard::D:
            case sf::Keyboard::Right:
                jump({destination.x + GRID_SIZE.x, destination.y});
                break;
            default:
                break;
        }
    }
}

bool Player::isJumping() const {
    return time_jumped < JUMP_DURATION;
}

void Player::calVelocity(sf::Time dt) {
    auto length = destination - getPosition();
    if (time_jumped < JUMP_DURATION) {
        auto time_left = JUMP_DURATION - time_jumped;
        time_jumped += dt;
        getVelocity() = {length.x / time_left.asSeconds(), length.y / time_left.asSeconds()};
    } else {
        getVelocity() = {length.x / dt.asSeconds(), length.y / dt.asSeconds()};
    }
}

void Player::onJumpAnimationFinished() {
    animation = {Texture::ID::StandingSprites, DEF_ANIMATION_DURATION, true};
}

void Player::jump(sf::Vector2f dest) {
    destination = dest;
    animation = {Texture::ID::JumpingSprites, JUMP_DURATION, false};
    time_jumped = sf::Time::Zero;

    AudioController::instance().playSound(SoundEffect::ID::Jump);
}