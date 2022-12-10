#pragma once
#include "State.h"
#include "Player.h"
#include "PauseMenu.h"
#include "Camera.h"
#include "World.h"

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
    World* world;
    Camera* camera;
	//std::string getMode();

	void updateEventsPauseMenu();

public:

	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::vector<State*>* states);

	~GameState() override;

	//void adjustCells(const int totalX, const int totalY);
	//Vector2u setCenter(const int totalX, const int totalY);

	//bool checkLastPlay();

	//void sinkingDown(const float& dt) { // apply to lanes, cars, ... float downward
	//	
	//}

	void updateEvents() override;

	void updateInput(const float& dt) override;
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};
