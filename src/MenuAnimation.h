#include <TGUI/TGUI.hpp>
#include <stdlib.h>
#include <time.h>
#define X first 
#define Y second

class MenuAnimation {
private:
	tgui::Gui* gui;
	float timeManage;
	float timeOverall;
	float vX, vY;
	bool turnBack;
	pair<int, int> a[5], b[5];
	string s[5];
public:
	MenuAnimation()
	{
		timeManage = 110;
		timeOverall = 6;
		vX = vY = 0;

		// random 1 of 4 edges: up:0, down:1, left:2, right:3
		a[0] = { 1, -32 };
		a[1] = { 1, 768 };
		a[2] = { -32, 1 };
		a[3] = { 1024, 1 };

		b[0] = { 1,-32+25 };
		b[1] = { 1, 768-25 };
		b[2] = { -32+25, 1 };
		b[3] = { 1024-25, 1 };

		s[0] = "toDown";
		s[1] = "toUp";
		s[2] = "toRight";
		s[3] = "toLeft";

		this->gui->get<tgui::Picture>("toDown")->setRotation(180f);
		this->gui->get<tgui::Picture>("toRight")->setRotation(-90f);
		this->gui->get<tgui::Picture>("toLeft")->setRotation(90f);

	}
	MenuAnimation(tgui::Gui*& gui)
	{
		this->gui = gui;
		timeManage = 0;
		timeOverall = 5;
		vX = vY = 0;
	}
	void SetGui(tgui::Gui*& gui)
	{
		this->gui = gui;
	}
	void setXY(float x, float y, int kind)
	{
		this->gui->get<tgui::Picture>(s[kind])->setPosition(tgui::Vector2f(x, y));
	}
	//tgui::Vector2f getXY()
	//{
	//	return this->gui->get<tgui::Picture>(s[kind])->getPosition();
	//}
	float velocityX(float x, float x1)
	{
		return float((x1 - x) / timeOverall);
	}
	float velocityY(float y, float y1)
	{
		return float((y1 - y) / timeOverall);
	}
	void moveXY(float x, float y, int time, int kind)
	{
		this->gui->get<tgui::Picture>(s[kind])->moveWithAnimation(tgui::Vector2f(x, y), tgui::Duration(1000));
	}

	int randHorizontal()
	{
		return rand() % (1024 - 32);
	}
	int randVerticle()
	{
		return rand() % (768 - 32);
	}
	bool check()
	{
		return (timeManage < timeOverall);
		/*float x = 0, y = 0;
		tgui::Vector2f(x, y) = this->getXY();
		return x < 300;*/
	}
	~MenuAnimation()
	{
		
	}

	void resettimeManage() {
		timeManage = 0;
	}
	bool checkDone() {
		return timeManage >= timeOverall*2;
	}
	bool inProcess() {
		return timeManage != 0.f;
	}

	void setEdge(int kind)
	{
		// random 1 of 4 edges: up:0, down:1, left:2, right:3
		// set beginning position 

		int temp;
		if (kind == 0 || kind == 1)
		{
			temp = randHorizontal();
			a[kind].X = b[kind].X = temp;
		}
		else
		{
			temp = randVerticle();
			a[kind].Y = b[kind].Y = temp;
		}
		this->setXY(a[kind].X, a[kind].Y, kind);
	}

	void update(const float & dt) {
		static bool flag = true;
		static int kind = 0;
		
		timeManage += dt;
		srand(time(0));

		if (this->checkDone()) // timeManage >= timeOverall*2
		{
			this->gui->get<tgui::Picture>(s[kind])->setVisible(false);
			this->resettimeManage();
			// random 1 of 4 edges: up:0, down:1, left:2, right:3
			kind = (rand() % 4);

			//pass kind to setEdge
			this->setEdge(kind);
		}
		else if (this->check()) //timeManage < timeOverall
		{
			if(flag) {
				flag = false;
				this->gui->get<tgui::Picture>(s[kind])->setVisible(true);
				this->moveXY(b[kind].X, b[kind].Y, timeOverall, kind);
			}

			
			//cout << dt << endl;
		}
		else
		{
			if (!flag) {
				flag = true;
				this->moveXY(a[kind].X, a[kind].Y, timeOverall, kind);
			}
			//ve vi tri cu
			//;
		}
	}
};