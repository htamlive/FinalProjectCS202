#include <TGUI/TGUI.hpp>
#ifdef __linux__ 

#elif _WIN32

#include <TGUI/Backend/SFML-Graphics.hpp>
#else

#endif
#include <string>
class ScoreDisplay {
private:
	int curScore = 0;
	void initButtons() {

	}
	void intVariables() {

	}
	tgui::Gui* gui;
public:
	ScoreDisplay(tgui::Gui* gui): gui(gui) {
		
	}


	void update(int score) {
		curScore = max(score, curScore);
		this->gui->get<tgui::Label>("lblScore")->setText(std::to_string(curScore));
	}

	int finalScore() {
		return curScore;
	}

};