#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include <iostream>
class AnimationsByFrames
{
private:
	sf::Clock animationTimer;
	sf::Texture textureSheet;
	float secondPerFrame;
	sf::IntRect curFrame;
	int textureWidth;

	void initVariables()
	{
		this->animationTimer.restart();
		this->curFrame = sf::IntRect(0,0,32,32);
	}
public:
	AnimationsByFrames(const sf::String& textureSheetPath, float secondPerFrame = 0.1f, int textureWidth = 32) :
				secondPerFrame(secondPerFrame), textureWidth(textureWidth) 
	{
		try
		{
			if (!this->textureSheet.loadFromFile(textureSheetPath)) {
                throw std::runtime_error("Error path: " + textureSheetPath);
			}
			//std::cout << this->textureSheet.getSize().x << " " << this->textureSheet.getSize().y << "\n";
			this->initVariables();
		}
		catch (const std::exception& error)
		{
			
		}
	}

	~AnimationsByFrames() = default;

	void updateAnimations() {
		if (this->animationTimer.getElapsedTime().asSeconds() >= this->secondPerFrame) {
			this->curFrame.left += this->textureWidth;
			if (this->curFrame.left >= textureSheet.getSize().x) this->curFrame.left = 0;

			this->animationTimer.restart();
		}
	}

	void renderSprite(sf::Sprite *sprite) {
		sprite->setTexture(this->textureSheet);
		sprite->setTextureRect(this->curFrame);
	}
};

