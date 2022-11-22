#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <thread>
#include "MainMenuState.h"


class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	std::map<std::string, int> supportedKeys;
	bool fullscreen;

	sf::Clock dtClock;
	float dt;

	std::vector<State*> states;


	void initVariables();
	void initWindow();
	void initState();

	void initKeys()
	{
		this->supportedKeys.emplace("Escape", sf::Keyboard::Key::Escape);
		this->supportedKeys.emplace("A", sf::Keyboard::Key::A);
		this->supportedKeys.emplace("W", sf::Keyboard::Key::W);
		this->supportedKeys.emplace("D", sf::Keyboard::Key::D);
		this->supportedKeys.emplace("S", sf::Keyboard::Key::S);
	}

	void initTexture() {
		TextureHolder::instance().load(Texture::PlayerStanding, "resources/spritesheet/main/idle.png", { 32, 32 }, 6);
		TextureHolder::instance().load(Texture::PlayerGoLeft, "resources/spritesheet/main/goLeft.png", { 32, 32 }, 6);
		TextureHolder::instance().load(Texture::PlayerGoRight, "resources/spritesheet/main/goRight.png", { 32, 32 }, 6);
		TextureHolder::instance().load(Texture::PlayerGoUp, "resources/spritesheet/main/goUp.png", { 32, 32 }, 6);
		TextureHolder::instance().load(Texture::PlayerGoDown, "resources/spritesheet/main/goDown.png", { 32, 32 }, 4);
		TextureHolder::instance().load(Texture::Null, "resources/spritesheet/NULL.png", { 32, 32 }, 1);
	};

	void updateEvents();
	void updateDt();


public:
	Game();
	virtual ~Game();

	const bool running() const;

	void endApplication();

	void updateSFMLEvents();
	void update();

	void render();
	void run();

	void closeWindow();
	void keyReleasedProc();
	void mouseProc();
};