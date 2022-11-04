#pragma once
#include <ctime>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/Widget.hpp>

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

public:

	State(sf::RenderWindow* window, std::vector<State*>* states);
	virtual ~State();
	sf::Event ev;

	const bool& getQuit() const;
	void endState();
	virtual void updateMousePos();
	virtual void updateInput(const float& dt) = 0;

	virtual void updateEvents() = 0;

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

