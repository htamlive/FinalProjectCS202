#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "SettingState.h"
#include "GameState.h"
#include "MenuAnimation.h"

class MainMenuState : public State {
private:
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	sf::Font font;
	MenuAnimation Meow;
	int curOpt = 1;
public:
	bool isWordMode = true;
	MainMenuState(sf::RenderWindow* window, std::vector<State*>* states);

	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::vector<State*>* states)
		: MainMenuState(window, states) {
		this->supportedKeys = supportedKeys;
		
		Meow.SetGui(this->gui);
		
		//if (Meow.check())
		//{
		//	Meow.moveSection(300, 300, 0.5);
		//	//cout << dt << endl;
		//}

		//this->gui->get<tgui::Picture>("meowPic")->moveWithAnimation(tgui::Vector2f(300, 300), tgui::Duration(4000));
		//this->gui->get<tgui::Picture>("meowPic")->showWithEffect(tgui::ShowEffectType::SlideToRight, tgui::Duration(4000));
		//this->gui->get<tgui::Button>("btnPlay")->showWithEffect(tgui::ShowEffectType::Fade,tgui::Duration(4000));
	};

	void initBackground() {

	};

	void initButtons() {
		this->gui->get<tgui::Button>("btnPlay")->onClick([&]() {
			this->states->push_back(new GameState(this->window, this->supportedKeys, this->states));
			});
		this->gui->get<tgui::Button>("btnLoad")->onClick([&]() {
			cout << "123\n";
			});
		this->gui->get<tgui::Button>("btnSetting")->onClick([&, this]() {
			cout << "oooooo\n";
			this->states->push_back(new SettingState(this->window, this->states));
			});
	};

	~MainMenuState() override = default;;

	void updateInput(const float& dt) override {

	};

	void updateEvents() override {
		this->gui->handleEvent(this->ev);
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->endState();
			break;
		case sf::Event::TextEntered:

			//update
			break;
		default:
			break;
		}
	};

	void update(const float& dt) override {
		srand(time(0));
		/*if (dt < 5000)
		{
			this->gui->get<tgui::Picture>("meowPic")->moveWithAnimation(tgui::Vector2f(300, 300), tgui::Duration(4000));
		}
		else if (dt > 5000)
		{
			this->gui->get<tgui::Picture>("meowPic")->moveWithAnimation(tgui::Vector2f(0, 0), tgui::Duration(4000));
		}*/
		
		//check if animation is done
		// 
		// 
		//Meow.moveXY(300, 300, 3000);

		// at begin timeManage = timeOverall*2
		static int kind = 0;
		if (Meow.checkDone()) // timeManage >= timeOverall*2
		{
			Meow.resettimeManage();
			// random 1 of 4 edges: up:0, down:1, left:2, right:3
			kind = (rand() % 4);
			
			//pass kind to setEdge
			Meow.setEdge(kind);

			// set ending position and calculate velocity
			// and timeManaage = 0
			Meow.direction(300, 300);

			// update will include 2 phases: go and back
			
			//Meow.moveSection()
		}

		Meow.update(dt, kind); 
	};

	void updateBtns() {

	};

	void render(sf::RenderTarget* target = nullptr) override;
};