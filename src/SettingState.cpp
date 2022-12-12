#include "SettingState.h"

SettingState::SettingState(sf::RenderWindow* window, std::vector<State*>* states) : State(window, states)
{
	this->gui->loadWidgetsFromFile("resources/Template/MainMenuTemplate.txt");


	//initBackground();

	//initSearchBar();
	initButtons();

	this->gui->get<tgui::Slider>("sliderMusic")->onValueChange([&]() {
		int val = this->gui->get<tgui::Slider>("sliderMusic")->getValue();
		this->gui->get<tgui::EditBox>("eBoxMusic")->setText(to_string(val));
		});

	this->gui->get<tgui::Slider>("sliderSound")->onValueChange([&]() {
		int val = this->gui->get<tgui::Slider>("sliderSound")->getValue();
		this->gui->get<tgui::EditBox>("eBoxSound")->setText(to_string(val));
		});

}

void SettingState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	target->draw(this->background);
	this->gui->draw();
	
}

