#include "State.h"

class PauseMenu : public State {
private:
	tgui::Group::Ptr myGroup;
	void initButtons() {
		myGroup->get<tgui::Button>("resumeBtn")->onClick([&]() {
			myGroup->setVisible(false);
			});
		myGroup->get<tgui::Button>("exitBtn")->onClick([&]() {
			quit = true;
			});

		this->gui->get<tgui::Button>("resumeBtn")->onMouseLeave([&, this]() {
			zoomSmall("resumeBtn");
			});
		this->gui->get<tgui::Button>("saveBtn")->onMouseLeave([&, this]() {
			zoomSmall("saveBtn");
			});
		this->gui->get<tgui::Button>("exitBtn")->onMouseLeave([&, this]() {
			zoomSmall("exitBtn");
			});

		this->gui->get<tgui::Button>("resumeBtn")->onMouseEnter([&, this]() {
			zoomBig("resumeBtn");
			});
		this->gui->get<tgui::Button>("saveBtn")->onMouseEnter([&, this]() {
			zoomBig("saveBtn");
			});
		this->gui->get<tgui::Button>("exitBtn")->onMouseEnter([&, this]() {
			zoomBig("exitBtn");
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
	void zoomBig(string Button) {
		this->gui->get<tgui::Button>(Button)->setScale({ 1.1f, 1.1f }, { 0.5f,0.5f });
	}
	void zoomSmall(string Button) {
		this->gui->get<tgui::Button>(Button)->setScale({ 1.0f / 1.1f, 1.0f / 1.1f }, { 0.5f,0.5f });
	}
	void update(const float& dt) override {
		
	}

	void updateInput(const float& dt) {

	}

	void updateEvents() {
		this->gui->handleEvent(this->ev);
	}

};