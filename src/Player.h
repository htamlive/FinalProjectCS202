#pragma once

#include "Entity.h"

/**
 * Note: character jumps only once each press. That allows user to control the speed (by pressing faster or slower).
 */
class Player : public Entity {
public:
    Player();

    Player(float x, float y, float w, float h);

    void onKeyPressed(sf::Event::KeyEvent);

    

    void update(sf::Time dt) {
        if (!isJumping()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                animation = AnimationMachine(Texture::PlayerGoUp, sf::seconds(.5f / alpha), true);
                jump({ destination.x, destination.y - GRID_SIZE.y });
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                animation = AnimationMachine(Texture::PlayerGoDown, sf::seconds(.5f / alpha), true);
                jump({ destination.x, destination.y + GRID_SIZE.y });
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                animation = AnimationMachine(Texture::PlayerGoLeft, sf::seconds(.5f / alpha), true);
                jump({ destination.x - GRID_SIZE.x, destination.y });
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                animation = AnimationMachine(Texture::PlayerGoRight, sf::seconds(.5f / alpha), true);
                jump({ destination.x + GRID_SIZE.x, destination.y });
            }

        }

        Entity::SceneNode::update(dt);
    }

private:
    void drawCurrent(sf::RenderTarget &target, sf::RenderStates state) const override;

    void updateCurrent(sf::Time dt) override;

    bool isJumping() const;

    bool shouldStand() {
        time_jumped - sf::seconds(0.5f) < JUMP_DURATION;
    }

    void calVelocity(sf::Time dt);

    void onJumpAnimationFinished();

    void jump(sf::Vector2f dest);

    sf::Vector2f destination;

    sf::Time time_jumped;
};

//enum class DIRECTION
//{
//	UP = 0,
//	RIGHT = 1,
//	DOWN = 2,
//	LEFT = 3,
//	IDLE = 4,
//};
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
