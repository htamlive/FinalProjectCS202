#pragma once

#include "Entity.h"

/**
 * @brief The Player class
 *
 * Note: character jumps only once each press. That allows user to control the speed (by pressing faster or slower).
 */
class Player : public Entity {
public:
    Player();

    Player(float x, float y, float w, float h);

    void onKeyPressed(sf::Event::KeyEvent);

    void update(sf::Time dt);

private:
    void updateCurrent(sf::Time dt) override;

    bool isJumping() const;

    void calVelocity(sf::Time dt);

    void onJumpAnimationFinished();

    sf::Vector2f static_pos;

    sf::Time time_jumped;

    Texture::ID jump_texture, idle_texture;
};

//class Player : public Entity
//{
//private:
//	std::vector<AnimationsByFrames*> animations;
//	float w = 32, h = 32;
//
//	void initVariables() {
//		animations.push_back(new AnimationsByFrames("FinalProjectCS202/spritesheet/main/goUp.png"));
//		animations.push_back(new AnimationsByFrames("FinalProjectCS202/spritesheet/main/goRight.png"));
//		animations.push_back(new AnimationsByFrames("FinalProjectCS202/spritesheet/main/goDown.png"));
//		animations.push_back(new AnimationsByFrames("FinalProjectCS202/spritesheet/main/goLeft.png"));
//		animations.push_back(new AnimationsByFrames("FinalProjectCS202/spritesheet/main/idle.png"));
//		this->sprite = new sf::Sprite();
//		this->sprite->scale(2.5f, 2.5f);
//		this->velocity = 150.0f;
//	}
//public:
//	Player() {
//		initVariables();
//	}
//
//	Player(float x, float y) :Entity(Texture::AnimalSprites, 150.0f, x, y, w, h) {
//
//	}
//
//	Player& changeVelocity(float velocity) {
//		this->velocity = velocity;
//		return *this;
//	}
//
//	~Player() {
//		for (auto& x : animations) {
//			delete x;
//			x = nullptr;
//		}
//		animations.clear();
//		delete this->sprite;
//
//	}
//
//	void move(const float& dt, const float& direction_x, const float& direction_y) override {
//		Entity::move(dt, direction_x, direction_y);
//		if (direction_y > 0) {
//			animations.at((int)DIRECTION::DOWN)->renderSprite(this->sprite);
//		}
//		else if (direction_y < 0) {
//			animations.at((int)DIRECTION::UP)->renderSprite(this->sprite);
//		}
//		else if (direction_x > 0) {
//			animations.at((int)DIRECTION::RIGHT)->renderSprite(this->sprite);
//		}
//		else if (direction_x < 0) {
//			animations.at((int)DIRECTION::LEFT)->renderSprite(this->sprite);
//		}
//		else {
//			animations.at((int)DIRECTION::IDLE)->renderSprite(this->sprite);
//		}
//	}
//
//	void update(const float& dt) override {
//		for (auto& x : animations) {
//			x->updateAnimations();
//		}
//	}
//};
