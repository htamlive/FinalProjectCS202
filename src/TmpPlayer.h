//#pragma once
//#include "Entity.h"
//#include "AnimationsByFrames.h"
//enum class DIRECTION
//{
//	UP = 0,
//	RIGHT = 1,
//	DOWN = 2,
//	LEFT = 3,
//	IDLE = 4,
//};
//class TmpPlayer : public Entity
//{
//private:
//	std::vector<AnimationsByFrames*> animations;
//public:
//	TmpPlayer() {
//		animations.push_back(new AnimationsByFrames("FinalProjectCS202/spritesheet/main/goUp.png"));
//		animations.push_back(new AnimationsByFrames("FinalProjectCS202/spritesheet/main/goRight.png"));
//		animations.push_back(new AnimationsByFrames("FinalProjectCS202/spritesheet/main/goDown.png"));
//		animations.push_back(new AnimationsByFrames("FinalProjectCS202/spritesheet/main/goLeft.png"));
//		animations.push_back(new AnimationsByFrames("FinalProjectCS202/spritesheet/main/idleDown.png"));
//		this->sprite = new Sprite();
//		this->sprite->scale(2.5f, 2.5f);
//	}
//
//	~TmpPlayer() {
//		for (auto& x : animations) {
//			delete x;
//			x = nullptr;
//		}
//		animations.clear();
//		delete this->sprite;
//
//	}
//
//	void move(const float& dt, const float dir_x, const float dir_y) override {
//		Entity::move(dt, dir_x, dir_y);
//		if (dir_y > 0) {
//			animations.at((int)DIRECTION::DOWN)->renderSprite(this->sprite);
//		}
//		else if (dir_y < 0) {
//			animations.at((int)DIRECTION::UP)->renderSprite(this->sprite);
//		}
//		else if (dir_x > 0) {
//			animations.at((int)DIRECTION::RIGHT)->renderSprite(this->sprite);
//		}
//		else if(dir_x < 0) {
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
//
