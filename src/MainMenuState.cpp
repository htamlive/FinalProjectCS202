#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::vector<State*>* states) : State(window, states)
{
	this->gui->loadWidgetsFromFile(APPDATA_PATH + "/resources/Template/MainMenuTemplateCPY.txt");

	//initBackground();

	//initSearchBar();
	initButtons();
	
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}

	target->draw(this->background);
	this->gui->draw();
	Meow.render(target);


}
