#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::vector<State*>* states) : State(window, states)
{
	this->gui = new tgui::Gui(ref(*window));
	this->gui->loadWidgetsFromFile("FinalProjectCS202/Template/MainMenuTemplate.txt");
	//initBackground();

	//initSearchBar();
	//initButtons();

	//auto x = tgui::Button::create("Nice to meet you");
	
	//this->gui->add(x, "btnLoad");
	tgui::Button::Ptr y = this->gui->get<tgui::Button>("btnPlay");
	//std::cout << y.size() << "\n";
	y->setPosition(100, 200);

	//this->gui->saveWidgetsToFile("FinalProjectCS202/Template/MainMenuTemplateCPY.txt");
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	target->draw(this->background);
	this->gui->draw();
}
