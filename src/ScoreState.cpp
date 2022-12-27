#include "ScoreState.h"

ScoreState::ScoreState(sf::RenderWindow* window, std::vector<State*>* states) : State(window, states)
{
	this->gui->loadWidgetsFromFile("resources/Template/ScoreBoardTemplate.txt");

	//this->gui->get<tgui::Picture>("Picture1")->setOrigin(0.5f,0.5f);
	initBackground();

	//initSearchBar();
	initButtons();


}

void ScoreState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	target->draw(this->background);
	this->gui->draw();
	
}

