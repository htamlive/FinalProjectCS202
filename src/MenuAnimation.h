#include <TGUI/TGUI.hpp>
#include <stdlib.h>
#include <time.h>

class MenuAnimation {
private:
	tgui::Gui* gui;
	float timeManage;
	float timeOverall;
	float vX, vY;
	bool turnBack;
	pair<int, int> a[5], b[5];
public:
	MenuAnimation()
	{
		timeManage = 11;
		timeOverall = 5;
		vX = vY = 0;
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
	void setXY(float x, float y)
	{
		this->gui->get<tgui::Picture>("meowPic")->setPosition(tgui::Vector2f(x, y));
	}
	tgui::Vector2f getXY()
	{
		return this->gui->get<tgui::Picture>("meowPic")->getPosition();
	}
	float velocityX(float x, float x1)
	{
		return float((x1 - x) / timeOverall);
	}
	float velocityY(float y, float y1)
	{
		return float((y1 - y) / timeOverall);
	}
	void moveXY(float x, float y, int time)
	{
		this->gui->get<tgui::Picture>("meowPic")->moveWithAnimation(tgui::Vector2f(x, y), tgui::Duration(1000));
	}
	bool check()
	{
		return (timeManage < timeOverall);
		/*float x = 0, y = 0;
		tgui::Vector2f(x, y) = this->getXY();
		return x < 300;*/
	}
	void moveSection(float x, float y, const float& dt)
	{
		//get x0, y0;
		float x0 = 0, y0 = 0;
		x0 = this->getXY().x;
		y0 = this->getXY().y;

		// x = x0 + vt
		// y = y0 + vt
				
		//moveXY(x0 + vX*dt, y0 + vY*dt, dt);
		moveXY(x, y, dt);
		//cout << dt << endl;
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
	void direction(float x, float y)
	{
		timeManage = 0;//set time = 0
		float x0 = 90, y0 = 100;
		x0 = this->getXY().x;
		y0 = this->getXY().y;
		vX = velocityX(x0, x);
		vY = velocityY(y0, y);
	}

	int setEdge(int num)
	{
		// random 1 of 4 edges: up:0, down:1, left:2, right:3
		// set beginning position 
		this -> setXY(90, 100);



	}

	void update(const float & dt) {
		static bool flag = true;
		timeManage += dt;
		if (this->check()) //timeManage < timeOverall
		{
			if(flag) {
				flag = false;
				this->moveXY(300, 300, timeOverall);
			}

			
			//cout << dt << endl;
		}
		else
		{
			if (!flag) {
				flag = true;
				this->moveXY(90, 100, timeOverall);
			}
			//ve vi tri cu
			//;
		}
	}
};