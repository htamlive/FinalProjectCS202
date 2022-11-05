#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "State.h"

class MainMenuState : public State {
private:
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	sf::Font font;

	int curOpt = 1;
public:
	bool isWordMode = true;
	MainMenuState(sf::RenderWindow* window, std::vector<State*>* states);

	void initBackground() {

	};

	void initButtons() {

	};

	~MainMenuState() {

	};

	void updateInput(const float& dt) {

	};

	void updateEvents() {

	};

	void update(const float& dt) {

	};

	void updateBtns() {

	};

	void render(sf::RenderTarget* target = nullptr);
};