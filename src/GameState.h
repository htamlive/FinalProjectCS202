#pragma once
#include "State.h"
#include "Player.h"
#include "PauseMenu.h"

class GameState : public State
{
private:
	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	sf::Font font;

	int curLv, rows, columns, mines, currentFlags;
	float height, width;
	bool lastPlay;

	Player* player;
	PauseMenu* pauseMenu;
	//std::string getMode();

	void updateEventsPauseMenu() {
		pauseMenu->ev = this->ev;
		pauseMenu->updateEvents();
	}

public:

	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::vector<State*>* states) : State(window, supportedKeys, states) {
		this->gui->loadWidgetsFromFile("resources/Template/GameTemplate.txt");
		this->initKeyBinds();

        player = new Player({0, 0}, GRID_SIZE);
		pauseMenu = new PauseMenu(window, states);
	};

	~GameState() override {
		delete player;
		delete pauseMenu;
	};

	//void adjustCells(const int totalX, const int totalY);
	//Vector2u setCenter(const int totalX, const int totalY);

	//bool checkLastPlay();

	//void sinkingDown(const float& dt) { // apply to lanes, cars, ... float downward
	//	
	//}

	void updateEvents() override {
		this->gui->handleEvent(this->ev);

		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->endState();
			break;
		case sf::Event::TextEntered:

			//update
			break;
		default:
			break;
		}

		updateEventsPauseMenu();

		if (pauseMenu->getQuit()) {
			this->endState();
		}
	};

	void updateInput(const float& dt) override {
		this->pauseMenu->updateInput();

		if (this->ev.type == sf::Event::KeyPressed) {
            this->player->onKeyPressed(this->ev.key);
        }
	};

	void update(const float& dt) override {
		float transDt = dt;
		if (pauseMenu->isPausing()) transDt = 0;
		updateInput(transDt);
		//this->player.update(dt);
		player->update(sf::Time(sf::seconds(transDt)));
	};

	void render(sf::RenderTarget* target = nullptr) override {
		if (!target) {
			target = this->window;
		}
		//this->player.render(target);
		this->gui->draw();
		target->draw(*player);
		pauseMenu->render(target);
	};
};