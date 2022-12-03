#include "State.h"

class PauseMenu : public State {
private:
	tgui::Group::Ptr myGroup;
	void initButtons() {
		myGroup->get<tgui::Button>("backBtn")->onClick([&]() {
			myGroup->setVisible(false);
			});
		myGroup->get<tgui::Button>("exitBtn")->onClick([&]() {
			quit = true;
			});
	}
	void initVariables() {
		quit = false;
	}
public:
	PauseMenu(sf::RenderWindow* window, vector<State*>* states) : State(window, states) {
		this->gui->loadWidgetsFromFile("resources\\Template\\PauseMenuTemplate.txt", false);
		myGroup = this->gui->get<tgui::Group>("PauseMenu");
		myGroup->setVisible(false);
		this->initVariables();
		this->initButtons();
		
	}

	void updateInput() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(sf::Keyboard::Escape))) {
			myGroup->setVisible(true);
		}
	}

	bool isPausing() {
		return myGroup->isVisible();
	}

	void render(sf::RenderTarget* target) override {
		this->gui->draw();
	}

	void update(const float& dt) override {

	}

	void updateInput(const float& dt) {

	}

	void updateEvents() {
		this->gui->handleEvent(this->ev);
	}

};