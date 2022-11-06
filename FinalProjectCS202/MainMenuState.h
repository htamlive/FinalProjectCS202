#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "State.h"
#include "SettingState.h"

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
		this->gui->get<tgui::Button>("btnPlay")->onClick([&]() {
			cout << "helllo\n";
			});
		this->gui->get<tgui::Button>("btnLoad")->onClick([&]() {
			cout << "123\n";
			});
		this->gui->get<tgui::Button>("btnSetting")->onClick([&, this]() {
			cout << "oooooo\n";
			this->states->push_back(new SettingState(this->window, this->states));
			});
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