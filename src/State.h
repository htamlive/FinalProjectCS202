#pragma once
#include <ctime>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>
#include <chrono>
#include <ctime> 

#include <TGUI/TGUI.hpp>
//#include <TGUI/Backend/SFML-Graphics.hpp>
#include <map>
#include "AudioController.h"
#include "Consts.h"


using namespace std;

class State
{
protected:
	std::vector<State*>* states;
	sf::RenderWindow* window;
	bool quit;
	tgui::Gui* gui;
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	std::map<std::string, sf::Texture*> textures;


	virtual void initKeyBinds() {
		this->keybinds.emplace("MOVE_LEFT", this->supportedKeys->at("A"));
		this->keybinds.emplace("MOVE_UP", this->supportedKeys->at("W"));
		this->keybinds.emplace("MOVE_RIGHT", this->supportedKeys->at("D"));
		this->keybinds.emplace("MOVE_DOWN", this->supportedKeys->at("S"));
		this->keybinds.emplace("CLOSE", this->supportedKeys->at("Escape"));
	}

	void scaling() {
		auto widgets = gui->getWidgets();
		scaling(widgets);
	}

	void scaling(const std::vector<tgui::Widget::Ptr>& widgets) {
		for (auto widget : widgets) {
			auto pos = widget->getPosition();
			auto dim = widget->getSize();
			widget->setPosition(pos * SYSTEM_SCALE);
			widget->setSize(dim * SYSTEM_SCALE);

			auto textSize = widget->getTextSize();
			widget->setTextSize(int(textSize * SYSTEM_SCALE));
		}
	}

public:

	State(sf::RenderWindow* window, std::vector<State*>* states);

	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::vector<State*>* states) : ev() {
		this->window = window;
		this->states = states;
		this->gui = new tgui::Gui(*window);
		this->quit = false;
		this->supportedKeys = supportedKeys;
	};
	virtual ~State();
	sf::Event ev;

	[[nodiscard]] const bool& getQuit() const;
	void endState();
	virtual void updateMousePos();
	virtual void updateInput(const float& dt) = 0;

	virtual void updateEvents() = 0;

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

