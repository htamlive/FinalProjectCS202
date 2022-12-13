#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "State.h"
#include "AudioController.h"

class SettingState : public State {
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
	SettingState(sf::RenderWindow* window, std::vector<State*>* states);

	void initBackground() {

	};

	void initButtons() {
		//this->gui->get<tgui::Button>("btnMusic")->onClick([&,this]() {
		//	cout << "helllo\n";
		//	this->gui->get<tgui::Button>("MusicOn")->setVisible(true);
		//	});
		//this->gui->get<tgui::Button>("btnSound")->onClick([&]() {
		//	cout << "123\n";
		//	this->gui->get<tgui::Button>("SoundOn")->setVisible(true);
		//	});
		//this->gui->get<tgui::Button>("btnBack")->onClick([&]() {
		//	cout << "oooooo\n";
		//	//this->gui->loadWidgetsFromFile("resources/Template/MainMenuTemplateCPY.txt");
		//	this->quit = true;
		//	});
		//this->gui->get<tgui::Button>("MusicOn")->onClick([&]() {
		//	this->gui->get<tgui::Button>("MusicOn")->setVisible(false);
		//	});
		//this->gui->get<tgui::Button>("SoundOn")->onClick([&]() {
		//	this->gui->get<tgui::Button>("SoundOn")->setVisible(false);
		//	});
		this->gui->get<tgui::Slider>("sliderMusic")->onValueChange([&]() {
			float temp = this->gui->get<tgui::Slider>("sliderMusic")->getValue();
			std::cout << temp << std::endl;
			AudioController::instance().playMusic(Music::Game);
			AudioController::instance().setMusicVolume(temp);
		});

		
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

	~SettingState() override = default;;

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

	};

	void updateBtns() {

	};

	void render(sf::RenderTarget* target = nullptr) override;
};