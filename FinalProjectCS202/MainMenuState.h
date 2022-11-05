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
	};

	void update(const float& dt) {

	};

	void updateBtns() {

	};

	void render(sf::RenderTarget* target = nullptr);
};