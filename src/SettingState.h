#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
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
		//For Music Alteration
		ifstream fin;
		fin.open(APPDATA_PATH + "/resources/textFile/MusicController.txt");

		int value;
		fin >> value;
		this->gui->get<tgui::Slider>("sliderMusic")->setValue(value);
		this->gui->get<tgui::EditBox>("eBoxMusic")->setText(to_string(value));

		fin.close();

		//To Sound Alteration
		fin.open(APPDATA_PATH + "/resources/textFile/SoundController.txt");

		fin >> value;
		this->gui->get<tgui::Slider>("sliderSound")->setValue(value);
		this->gui->get<tgui::EditBox>("eBoxSound")->setText(to_string(value));

		fin.close();
	};

	void setValue(string type, int value) {
		ofstream fout;
		fout.open(APPDATA_PATH + "/resources/textFile/" + type + "Controller.txt", ios::trunc);
		
		fout << value;
		
		fout.close();
	}

	void initButtons() {
		this->gui->get<tgui::Slider>("sliderMusic")->onValueChange([&]() {
			
			int val = this->gui->get<tgui::Slider>("sliderMusic")->getValue();
			
			std::cout << val << std::endl;

			setValue("Music", val);

			this->gui->get<tgui::EditBox>("eBoxMusic")->setText(to_string(val));
			//AudioController::instance().playMusic(Music::Game);
			AudioController::instance().setMusicVolume(val);
		});

		this->gui->get<tgui::Slider>("sliderSound")->onValueChange([&]() {
				int val = this->gui->get<tgui::Slider>("sliderSound")->getValue();
				
				std::cout << val << std::endl;

				setValue("Sound", val);

				this->gui->get<tgui::EditBox>("eBoxSound")->setText(to_string(val));
				AudioController::instance().setSoundVolume(val);
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