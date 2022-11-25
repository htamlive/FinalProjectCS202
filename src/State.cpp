#include "State.h"


State::State(sf::RenderWindow* window, std::vector<State*>* states) : ev(), supportedKeys()
{
	this->window = window;
	this->states = states;
	this -> gui = new tgui::Gui(*window);
	this->quit = false;
}


State::~State() = default;

const bool& State::getQuit() const
{
	return this->quit;
}

void State::endState()
{
	this->quit = true;
}


void State::updateMousePos()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}
