#pragma once
#include "State.h"
#include "Player.h"
#include "PauseMenu.h"
#include "Camera.h"
#include "World.h"
#include "SummaryMenu.h"

class GameState : public State
{
private:
	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	sf::Font font;

	int curLv, rows, columns, mines, currentFlags;
	float height, width;
	bool lastPlay;

	class Player* player;
	PauseMenu* pauseMenu;
	SummaryMenu* summaryMenu;
    World* world;
    Camera* camera;
	//std::string getMode();

	void updateEventsPauseMenu();

	void updateEventsSummaryMenu() {
		if (summaryMenu) {
			summaryMenu->ev = this->ev;
			summaryMenu->updateEvents();
		}
	};

	void initVariables() {
		auto pPlayer = std::unique_ptr<Player>(
			new Player({ window->getSize().x / 2 - GRID_SIZE.x,
							  (float)window->getSize().y - GRID_SIZE.y },
				GRID_SIZE));
		player = pPlayer.get();
		pauseMenu = new PauseMenu(window, states);
		//summaryMenu = new SummaryMenu(window, states);
		summaryMenu = nullptr;
		world = new World(sf::Vector2f(window->getSize()));
		world->setDebug(true, true);
		camera = new Camera(*player, *window, *world);
		world->attachChild(std::move(pPlayer));
	}

public:

	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::vector<State*>* states);

	~GameState() override;

	//void adjustCells(const int totalX, const int totalY);
	//Vector2u setCenter(const int totalX, const int totalY);

	//bool checkLastPlay();

	//void sinkingDown(const float& dt) { // apply to lanes, cars, ... float downward
	//	
	//}
	void initMusic();
	void playAgain() {
		delVariables();
		initVariables();
	}
	void updateEvents() override;

	void updateInput(const float& dt) override;
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
	void delVariables() {
		delete pauseMenu;
		delete summaryMenu;
		delete world;
		delete camera;
	};

};
