#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <chrono>
#include <cmath>
#include "State.h"
#include "AudioController.h"
const long double PI = acos(-1);
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
	float w = 2.f, angle = 0.f, A = 360.f, totatTime = 0.f, opa = 0.f;

	void initRank() {
		vector<int> v(3);
		ifstream ifs("data/scores.txt");
		for (int i = 0; i < 3; ++i) {
			ifs >> v[i];
			if (v[i] == 0) continue;
			tgui::String label = "lblTop" + std::to_string(i + 1);
			this->gui->get<tgui::Label>(label)->setText(tgui::String(v[i]));
		}
		ifs.close();


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
	template <class T> const T& min(const T& a, const T& b) {
		return !(b < a) ? a : b;     // or: return !comp(b,a)?a:b; for version (2)
	}
	void update(const float& dt) override {
		totatTime += dt;
		
		
		//cout << beginn<< " " << angle << "\n";
		
		if (totatTime > PI/2/w)
		{
			totatTime = -3;
			angle = -1;
			auto pos = this->gui->get<tgui::Picture>("Picture1")->getPosition();
			//this->gui->get<tgui::Picture>("Picture1")->moveWithAnimation({ pos.x, pos.y - 1.f }, sf::seconds(.75f));
			
		}
		else if (totatTime >= 0) {
			auto pos = this->gui->get<tgui::Picture>("Picture1")->getPosition();
			this->gui->get<tgui::Picture>("Picture1")->setPosition({ pos.x, 110 - A/4 * sin(2 * w * totatTime) });
			angle = A * sin(w * totatTime);

			this->gui->get<tgui::Picture>("Picture1")->setRotation(angle,{0.5f, 0.5f});
		}

		this->gui->get<tgui::Picture>("goldenGlow")->setInheritedOpacity(min<float>(abs(totatTime) * 1.2, 1.f));
		this->gui->get<tgui::Picture>("silverGlow")->setInheritedOpacity(min<float>(abs(totatTime) * 1.2, 1.f));
		this->gui->get<tgui::Picture>("bronzeGlow")->setInheritedOpacity(min<float>(abs(totatTime) * 1.2, 1.f));
	};

	void updateBtns() {

	};

	void render(sf::RenderTarget* target = nullptr) override;
};
