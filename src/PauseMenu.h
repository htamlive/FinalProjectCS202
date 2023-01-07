#include "State.h"

class PauseMenu : public State {
private:
    bool mShouldSave = false;
	tgui::Group::Ptr myGroup;
	tgui::FileDialog::Ptr fileDialog;
	tgui::String savePath;
	
	string getNameFile() {

		auto end = std::chrono::system_clock::now();
		std::time_t now = std::chrono::system_clock::to_time_t(end);
		char buffer[80];
		auto myTime = std::localtime(&now);

		strftime(buffer, 80, "%F_%H-%M-%S", myTime);
		string name = string(buffer) + ".meow";
		return name;
	}

	void saveGameWithFileDialog() {
		fileDialog = tgui::FileDialog::create("Save game", "Save");
		this->gui->add(fileDialog, "fileDialog");
		fileDialog->setPosition(DEF_FILE_DIALOG_POS);
		fileDialog->setSize(DEF_FILE_DIALOG_SIZE);
		fileDialog->setTextSize(fileDialog->getTextSize() * SYSTEM_SCALE);
		fileDialog->setFileMustExist(false);
		fileDialog->setPositionLocked(true);
		fileDialog->setFileTypeFilters({{ "name.meow", {"*.meow"} }});
		fileDialog->setFilename(getNameFile());
		fileDialog->setPath(fileDialog->getPath().asString() + "/saved games");
		

		fileDialog->onFileSelect([&]() {
			auto res = fileDialog->getSelectedPaths();
			if (res.empty()) return;
			savePath = fileDialog->getSelectedPaths()[0].asString();
			mShouldSave = true;
		});


		fileDialog->onClose([&]() {
			gui->remove(fileDialog);
			});

	}
	void initButtons() {
		myGroup->get<tgui::Button>("resumeBtn")->onClick([&]() {
			myGroup->setVisible(false);
			});
		myGroup->get<tgui::Button>("exitBtn")->onClick([&]() {
			quit = true;
			});

		this->gui->get<tgui::Button>("saveBtn")->onClick([&, this]() {
			saveGameWithFileDialog();
            
			
			});
		this->gui->get<tgui::Button>("resumeBtn")->onMouseLeave([&, this]() {
			zoomSmall("resumeBtn");
			});
		this->gui->get<tgui::Button>("saveBtn")->onMouseLeave([&, this]() {
			zoomSmall("saveBtn");
			});
		this->gui->get<tgui::Button>("exitBtn")->onMouseLeave([&, this]() {
			zoomSmall("exitBtn");
			});

		this->gui->get<tgui::Button>("resumeBtn")->onMouseEnter([&, this]() {
			zoomBig("resumeBtn");
			});
		this->gui->get<tgui::Button>("saveBtn")->onMouseEnter([&, this]() {
			zoomBig("saveBtn");
			});
		this->gui->get<tgui::Button>("exitBtn")->onMouseEnter([&, this]() {
			zoomBig("exitBtn");
			});
	}
	void initVariables() {
		quit = false;
	}
public:
	PauseMenu(sf::RenderWindow* window, vector<State*>* states) : State(window, states) {
		this->gui->loadWidgetsFromFile("resources/Template/PauseMenuTemplate.txt", false);
		myGroup = this->gui->get<tgui::Group>("PauseMenu");
		myGroup->setVisible(false);
		this->initVariables();
		this->initButtons();
		myGroup->setScale(SYSTEM_SCALE);
		//scaling(myGroup->getWidgets());
	}

	void updateInput() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(sf::Keyboard::Escape))) {
			myGroup->setVisible(true);
		}
	}

	bool isPausing() {
		return myGroup->isVisible();
	}

    string returnedSavePath() {
        if (mShouldSave) {
            mShouldSave = false;
            return savePath.toStdString();
        }
        return "";
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

};
