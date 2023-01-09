#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "SettingState.h"
#include "GameState.h"
#include "MenuAnimation.h"
#include "ScoreState.h"
#include <TGUI/Widgets/FileDialog.hpp>

class MainMenuState : public State {
private:
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	sf::Font font;
	tgui::FileDialog::Ptr fileDialog;
	
	MenuAnimation Meow;
	int curOpt = 1;

	void zoomBig(string Button) {
		this->gui->get<tgui::Button>(Button)->setScale({ 1.1f, 1.1f }, { 0.5f,0.5f });
	}
	void zoomSmall(string Button) {
		this->gui->get<tgui::Button>(Button)->setScale({ 1.0f / 1.1f, 1.0f / 1.1f }, { 0.5f,0.5f });
	}
	float totalTime = 0.f;
	const float overTime = 1;

	void initFileDialog() {
		fileDialog = tgui::FileDialog::create("Load game", "Load");
		this->gui->add(fileDialog, "fileDialog");
		fileDialog->setPosition(DEF_FILE_DIALOG_POS);
		fileDialog->setSize(DEF_FILE_DIALOG_SIZE);
		fileDialog->setTextSize(fileDialog->getTextSize() * SYSTEM_SCALE);
		fileDialog->setFileMustExist(true);
		fileDialog->setPositionLocked(true);
		fileDialog->setPath(fileDialog->getPath().asString() + "/saved games");
		

		fileDialog->onFileSelect([&]() {
			auto res = fileDialog->getSelectedPaths();
			if (res.empty()) return;
			auto path = fileDialog->getSelectedPaths()[0].asString();

			this->states->push_back(new GameState(this->window, this->supportedKeys, this->states, path.toStdString()));
			});

		fileDialog->onClose([&]() {
			gui->remove(fileDialog);
			});
	}
public:
	bool isWordMode = true;
	MainMenuState(sf::RenderWindow* window, std::vector<State*>* states);

	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::vector<State*>* states)
		: MainMenuState(window, states) {
		this->supportedKeys = supportedKeys;
		
		Meow.SetGui(this->gui);
		
		//this->gui->getContainer()->setScale(SCALE);
		scaling();
	};

	void initBackground() {

	};

	void initButtons() {
		this->gui->get<tgui::Button>("btnPlay")->onClick([&]() {
			this->states->push_back(new GameState(this->window, this->supportedKeys, this->states));
			});
		this->gui->get<tgui::Button>("btnLoad")->onClick([&]() {
			initFileDialog();
			
			});
		this->gui->get<tgui::Button>("btnSetting")->onClick([&, this]() {
			cout << "setting button pressed\n";
			this->states->push_back(new SettingState(this->window, this->states));
			});

		this->gui->get<tgui::Button>("btnScore")->onClick([&, this]() {
			//cout << "setting button pressed\n";
			this->states->push_back(new ScoreState(this->window, this->states));
			});

		this->gui->get<tgui::Button>("btnPlay")->onMouseLeave([&, this]() {
			zoomSmall("btnPlay");
			});
		this->gui->get<tgui::Button>("btnLoad")->onMouseLeave([&, this]() {
			zoomSmall("btnLoad");
			});
		this->gui->get<tgui::Button>("btnSetting")->onMouseLeave([&, this]() {
			zoomSmall("btnSetting");
			});
		this->gui->get<tgui::Button>("btnScore")->onMouseLeave([&, this]() {
			zoomSmall("btnScore");
			});

		this->gui->get<tgui::Button>("btnPlay")->onMouseEnter([&, this]() {
			zoomBig("btnPlay");
			});
		this->gui->get<tgui::Button>("btnLoad")->onMouseEnter([&, this]() {
			zoomBig("btnLoad");
			});
		this->gui->get<tgui::Button>("btnSetting")->onMouseEnter([&, this]() {
			zoomBig("btnSetting");
			});
		this->gui->get<tgui::Button>("btnScore")->onMouseEnter([&, this]() {
			zoomBig("btnScore");
			});
	};

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
		Meow.update(dt); 

		totalTime += dt;
		if (totalTime > overTime)
		{
			totalTime = -totalTime;
		}
		this->gui->get<tgui::Picture>("silverGlow")->setInheritedOpacity(min(1.27f*abs(totalTime),1.f));
	};

	void render(sf::RenderTarget* target = nullptr) override;
};
