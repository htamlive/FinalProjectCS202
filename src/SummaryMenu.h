#include "State.h"
#include <fstream>
class SummaryMenu : public State {
private:
	tgui::Group::Ptr myGroup;
	bool playAgain;
	void initButtons() {
		myGroup->get<tgui::Button>("exitBtn")->onClick([&]() {
			quit = true;
			});
		myGroup->get<tgui::Button>("exitBtn")->onMouseEnter([&]() {
			zoomBig("exitBtn");
			});
		myGroup->get<tgui::Button>("exitBtn")->onMouseLeave([&]() {
			zoomSmall("exitBtn");
			});

		myGroup->get<tgui::Button>("playAgainBtn")->onClick([&]() {
			quit = true;
		playAgain = true;
			});
		myGroup->get<tgui::Button>("playAgainBtn")->onMouseEnter([&]() {
			zoomBig("playAgainBtn");
			});
		myGroup->get<tgui::Button>("playAgainBtn")->onMouseLeave([&]() {
			zoomSmall("playAgainBtn");
			});
	}
	void initVariables() {
		quit = false;
		playAgain = false;
	}

	void saveScore(int score) {
		std::ifstream ifs(APPDATA_PATH + "/data/scores.txt");
		vector<int> v(3);
		for (int i = 0; i < 3; ++i) {
			ifs >> v[i];
		}
		v.push_back(score);
		sort(v.rbegin(), v.rend());
		ifs.close();
		std::ofstream ofs(APPDATA_PATH + "/data/scores.txt");
		for (int i = 0; i < 3; ++i) {
			ofs << v[i] << "\n";
		}
		ofs.close();
	}
	
public:
	SummaryMenu(sf::RenderWindow* window, vector<State*>* states, int finalScore) : State(window, states) {
		this->gui->loadWidgetsFromFile(APPDATA_PATH + "/resources/Template/SummaryBoardTemplate.txt");

		myGroup = this->gui->get<tgui::Group>("SummaryBox");
		myGroup->setVisible(true);
		this->initVariables();
		this->initButtons();
		
		myGroup->get<tgui::Label>("lblFinalScore")->setText(tgui::String(finalScore));
		saveScore(finalScore);

		myGroup->setScale(SYSTEM_SCALE);
		//scaling();
		//scaling(myGroup->getWidgets());
	}

	void updateInput() {
		
	}

	void render(sf::RenderTarget* target) override {
		
		this->gui->draw();
	}
	void zoomBig(string Button) {
		this->gui->get<tgui::Button>(Button)->setScale({ 1.1f, 1.1f }, { 0.5f,0.5f });
	}
	void zoomSmall(string Button) {
		this->gui->get<tgui::Button>(Button)->setScale({ 1.0f / 1.1f, 1.0f / 1.1f }, { 0.5f,0.5f });
	}
	void update(const float& dt) override {
		
	}

	void updateInput(const float& dt) override {

	}

	void updateEvents() override {
		this->gui->handleEvent(this->ev);
	}

	bool checkPlayAgain() {
		return playAgain;
	}

};