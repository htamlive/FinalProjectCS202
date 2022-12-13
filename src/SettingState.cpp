#include "SettingState.h"

SettingState::SettingState(sf::RenderWindow* window, std::vector<State*>* states) : State(window, states)
{
	this->gui->loadWidgetsFromFile("resources/Template/MainMenuTemplate.txt");


	//initBackground();

	//initSearchBar();
	initButtons();



}

void SettingState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	target->draw(this->background);
	this->gui->draw();
	
}

