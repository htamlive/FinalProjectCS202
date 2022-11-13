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