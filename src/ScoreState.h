#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <chrono>
#include "State.h"
#include "AudioController.h"

class ScoreState : public State {
private:
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	sf::Font font;

	int curOpt = 1;

	void zoomBig(string Button) {
		this->gui->get<tgui::Button>(Button)->setScale({ 1.1f, 1.1f }, { 0.5f,0.5f });
	}
	void zoomSmall(string Button) {
		this->gui->get<tgui::Button>(Button)->setScale({ 1.0f / 1.1f, 1.0f / 1.1f }, { 0.5f,0.5f });
	}
public:
	bool isWordMode = true;
	ScoreState(sf::RenderWindow* window, std::vector<State*>* states);



	void initBackground() {

	};

	void initButtons() {
		
		this->gui->get<tgui::Button>("btnBack")->onMouseEnter([&]() {
			zoomBig("btnBack");
			});

		this->gui->get<tgui::Button>("btnBack")->onMouseLeave([&]() {
			zoomSmall("btnBack");
			});

		this->gui->get<tgui::Button>("btnBack")->onClick([&]() {
			endState();
			});
	};

	~ScoreState() override = default;;

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
		cout << dt << endl;
		static int countt = 6, beginn = 0, angle = 0;
		beginn += dt;
		if (angle < 360 && beginn < countt)
		{
			angle += 2;
			this->gui->get<tgui::Picture>("Picture1")->setRotation(angle);
		}
		else if (beginn >= countt)
		{
			angle = 0;
			beginn = 0;
		}
	};

	void updateBtns() {

	};

	void render(sf::RenderTarget* target = nullptr) override;
};