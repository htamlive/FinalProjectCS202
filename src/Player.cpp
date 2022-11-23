#include "Player.h"
#include "TextureHolder.h"
#include "Consts.h"
#include "AudioController.h"
#include <iostream>

void Player::update(sf::Time dt)
{
    if (!isJumping()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            animation = AnimationMachine(Texture::PlayerGoUp, sf::seconds(.5f), true);
            jump({ destination.x, destination.y - GRID_SIZE.y });
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            animation = AnimationMachine(Texture::PlayerGoDown, sf::seconds(.5f), true);
            jump({ destination.x, destination.y + GRID_SIZE.y });
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            animation = AnimationMachine(Texture::PlayerGoLeft, sf::seconds(.5f), true);
            jump({ destination.x - GRID_SIZE.x, destination.y });
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            animation = AnimationMachine(Texture::PlayerGoRight, sf::seconds(.5f), true);
            jump({ destination.x + GRID_SIZE.x, destination.y });
        }

    }

    Entity::SceneNode::update(dt);
}

void Player::drawCurrent(sf::RenderTarget &target, sf::RenderStates state) const {
    // Downcast Vehicle back to sf::Transformable then upcast to sf::Sprite to preserve properties i.e., position, scale, origin, rotation.
    //std::cout << "Hello\n";
    sf::Sprite sprite = *this;
    animation.toSprite(sprite);
    target.draw(sprite, state);
}

void Player::updateCurrent(sf::Time dt) {
    //if (animation.getID() == Texture::ID::JumpingSprites && animation.isFinished()) {
    //    onJumpAnimationFinished();
    //}

    if (!isJumping() && animation.getID() != Texture::PlayerStanding) {
        onJumpAnimationFinished();
    }

    calVelocity(dt);

    Entity::updateCurrent(dt);
}

Player::Player() { destination = getPosition(); }

Player::Player(float x, float y, float w, float h) : Entity({0, 0}, x, y, w, h, Texture::ID::PlayerStanding,
                                                            JUMP_DURATION, false) {
    destination = getPosition();
    animation = AnimationMachine(Texture::PlayerStanding, sf::seconds(1.f), true);
    this->scale({ 1.5f, 1.5f });
}

void Player::onKeyPressed(sf::Event::KeyEvent event) {
    //animation = AnimationMachine(Texture::PlayerStanding, sf::seconds(1.f), true);
    if (!isJumping()) {
        switch (event.code) {
            case sf::Keyboard::W:
            case sf::Keyboard::Up:
                animation = AnimationMachine(Texture::PlayerGoUp, sf::seconds(.5f), true);
                jump({destination.x, destination.y - GRID_SIZE.y});
                break;
            case sf::Keyboard::S:
            case sf::Keyboard::Down:
                animation = AnimationMachine(Texture::PlayerGoDown, sf::seconds(.5f), true);
                jump({destination.x, destination.y + GRID_SIZE.y});
                break;
            case sf::Keyboard::A:
            case sf::Keyboard::Left:
                animation = AnimationMachine(Texture::PlayerGoLeft, sf::seconds(.5f), true);
                jump({destination.x - GRID_SIZE.x, destination.y});
                break;
            case sf::Keyboard::D:
            case sf::Keyboard::Right:
                animation = AnimationMachine(Texture::PlayerGoRight, sf::seconds(.5f), true);
                jump({destination.x + GRID_SIZE.x, destination.y});
                break;
            default:
                
                break;
        }
    }

}

bool Player::isJumping() const {
    //std::cout << time_jumped.asSeconds() << "\n";
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
    animation = AnimationMachine(Texture::PlayerStanding, sf::seconds(1.f),true);
}

void Player::jump(sf::Vector2f dest) {
    destination = dest;
    //animation = {Texture::ID::JumpingSprites, JUMP_DURATION, false};
    time_jumped = sf::Time::Zero;
    //AudioController::instance().playSound(SoundEffect::ID::Jump);
}