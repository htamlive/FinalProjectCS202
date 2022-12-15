#include "State.h"

class SummaryMenu : public State {
private:
	tgui::Group::Ptr myGroup;
	void initButtons() {
		myGroup->get<tgui::Button>("exitBtn")->onClick([&]() {
			quit = true;
			});
	}
	void initVariables() {
		quit = false;
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

};