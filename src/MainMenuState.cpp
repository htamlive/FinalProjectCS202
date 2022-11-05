#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::vector<State*>* states) : State(window, states)
{
	this->gui = new tgui::Gui(ref(*window));
	this->gui->loadWidgetsFromFile("FinalProjectCS202/Template/MainMenuTemplate.txt");
	//initBackground();

	//initSearchBar();
	//initButtons();
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	target->draw(this->background);
	this->gui->draw();
}
