#include "ScoreState.h"

ScoreState::ScoreState(sf::RenderWindow* window, std::vector<State*>* states) : State(window, states)
{
	this->gui->loadWidgetsFromFile("resources/Template/ScoreBoardTemplate.txt");


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

