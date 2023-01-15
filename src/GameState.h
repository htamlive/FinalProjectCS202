#pragma once
#include "State.h"
#include <memory>
#include "Player.h"
#include "PauseMenu.h"
#include "Camera.h"
#include "World.h"
#include "GameLoader.h"
#include "SummaryMenu.h"
#include "ScoreDisplay.h"


#include <fstream>
class GameState : public State
{
private:
	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	sf::Font font;

	int curLv, rows, columns, mines, currentFlags;
	float height, width;
	bool lastPlay;

	Player* player = nullptr;
	PauseMenu* pauseMenu;
	SummaryMenu* summaryMenu;
	ScoreDisplay* scoreDisplay;

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

	void initVariables();
    void initGameVariables();
    void loadGameFromFile(const std::string& fileName);
    void saveGameToFile(const std::string& fileName);

public:

	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::vector<State*>* states);
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::vector<State*>* states, const std::string& fileName);

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
		initGameVariables();
	}
	void updateEvents() override;

	void updateSummary();
	void updateScore();
	void updateSaveGame();
	void updateCollision(std::set<SceneNode::Pair>& collisionPairs);
	void updateInput(const float& dt) override;
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
	void delVariables() {
		AudioController::instance().removeStoppedSounds();
		delete scoreDisplay;
		delete pauseMenu;
		delete summaryMenu;
		delete world;
		delete camera;
	};
};
