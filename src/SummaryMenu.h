#include "State.h"

class SummaryMenu : public State {
private:
	tgui::Group::Ptr myGroup;
	bool playAgain;
	void initButtons() {
		myGroup->get<tgui::Button>("exitBtn")->onClick([&]() {
			quit = true;
			});
		myGroup->get<tgui::Button>("exitBtn")->onMouseEnter([&]() {
			zoomBig("exitBtn");
			});
		myGroup->get<tgui::Button>("exitBtn")->onMouseLeave([&]() {
			zoomSmall("exitBtn");
			});

		myGroup->get<tgui::Button>("playAgainBtn")->onClick([&]() {
			quit = true;
		playAgain = true;
			});
		myGroup->get<tgui::Button>("playAgainBtn")->onMouseEnter([&]() {
			zoomBig("playAgainBtn");
			});
		myGroup->get<tgui::Button>("playAgainBtn")->onMouseLeave([&]() {
			zoomSmall("playAgainBtn");
			});
	}
	void initVariables() {
		quit = false;
		playAgain = false;
	}
	
public:
	SummaryMenu(sf::RenderWindow* window, vector<State*>* states) : State(window, states) {
		this->gui->loadWidgetsFromFile("resources/Template/SummaryBoardTemplate.txt", false);
		myGroup = this->gui->get<tgui::Group>("SummaryBox");
		myGroup->setVisible(true);
		this->initVariables();
		this->initButtons();
		
	}

	void updateInput() {
		
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

	bool checkPlayAgain() {
		return playAgain;
	}

};