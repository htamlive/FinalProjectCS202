#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "State.h"

class SettingState : public State {
private:
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	sf::Font font;

	int curOpt = 1;
public:
	bool isWordMode = true;
	SettingState(sf::RenderWindow* window, std::vector<State*>* states);

	void initBackground() {

	};

	void initButtons() {
		this->gui->get<tgui::Button>("btnMusic")->onClick([&]() {
			cout << "helllo\n";
			});
		this->gui->get<tgui::Button>("btnSound")->onClick([&]() {
			cout << "123\n";
			});
		this->gui->get<tgui::Button>("btnBack")->onClick([&]() {
			cout << "oooooo\n";
			this->gui->loadWidgetsFromFile("resources/Template/MainMenuTemplateCPY.txt");
			this->quit = true;
			});
	};

	~SettingState() override = default;;

	void updateInput(const float& dt) override {

	};

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
	};

	void update(const float& dt) override {

	};

	void updateBtns() {

	};

	void render(sf::RenderTarget* target = nullptr) override;
};