#include <TGUI/TGUI.hpp>
#include <stdlib.h>
#include <time.h>

class MenuAnimation {
private:
	tgui::Gui* gui;
	float timeManage, timeOverall, timeMoving, m_size, realSize, showBound;
	
	sf::Vector2f a[5], b[5], velocity;
	sf::Sprite sprite;
	sf::Texture texture;
	std::vector<float> rotations;

	void initVariables() {
		timeManage = 11;
		timeOverall = 6;
		timeMoving = 2;
		m_size = 82;
		realSize = 128;
		showBound = 55;
	}

	enum class _DIRECTION
	{
		TO_DOWN = 0,
		TO_UP = 1,
		TO_RIGHT = 2,
		TO_LEFT = 3,
	};
public:
	MenuAnimation()
	{

		initVariables();

		// random 1 of 4 edges: up:0, down:1, left:2, right:3
		a[(int)_DIRECTION::TO_DOWN] = { 0, -82 };
		a[(int)_DIRECTION::TO_UP] = { 0, 768 };
		a[(int)_DIRECTION::TO_RIGHT] = { -82, 0 };
		a[(int)_DIRECTION::TO_LEFT] = { 1024, 0 };

		b[(int)_DIRECTION::TO_DOWN] = { 0, showBound };
		b[(int)_DIRECTION::TO_UP] = { 0, 768 - showBound };
		b[(int)_DIRECTION::TO_RIGHT] = { showBound, 0 };
		b[(int)_DIRECTION::TO_LEFT] = { 1024 - showBound, 0};

		rotations.resize(4);
		rotations[(int)_DIRECTION::TO_DOWN] = 180.f;
		rotations[(int)_DIRECTION::TO_UP] = 0.f;
		rotations[(int)_DIRECTION::TO_RIGHT] = 90.f;
		rotations[(int)_DIRECTION::TO_LEFT] = 270.f;

		this->texture.loadFromFile("resources\\spritesheet\\\main\\idleDown_128_128.png", sf::IntRect(0, 0, 128, 128));
		this->sprite.setTexture(texture);
		this->sprite.setScale({ m_size / realSize, m_size / realSize });
		this->sprite.setOrigin({ 0.5f, 0.5f });

	}
	MenuAnimation(tgui::Gui*& gui)
	{
		this->gui = gui;
	}
	void SetGui(tgui::Gui*& gui)
	{
		this->gui = gui;

	}
	void setXY(tgui::Vector2f pos, int kind)
	{
		//this->gui->get<tgui::Picture>(s[kind])->setPosition(pos);
		this->sprite.setPosition(pos);
		this->sprite.setRotation(rotations[kind]);
		
	}
	//tgui::Vector2f getXY()
	//{
	//	return this->gui->get<tgui::Picture>(s[kind])->getPosition();
	//}
	void moveXY(tgui::Vector2f pos, int time, int kind)
	{
		//this->gui->get<tgui::Picture>(s[kind])->moveWithAnimation(pos, tgui::Duration(sf::seconds(1)));
	}

	void moveCharacter(int kind, const float& dt) {
		tgui::Vector2f nwPos = tgui::Vector2f(this->sprite.getPosition() + velocity * dt);
		this->sprite.setPosition(nwPos);
	}

	tgui::Vector2f calcVelocity(tgui::Vector2f pos, int time, int kind) {
		return (pos - tgui::Vector2f(this->sprite.getPosition()))/time;
	}

	int randHorizontal(){
		srand(time(NULL));
		return rand()*rand()%1000000007 % (1024 - (int)m_size*3/2);
	}
	int randVerticle(){
		srand(time(NULL));
		return rand()*rand()%1000000007 % (768 - (int)m_size*3/2);
	}
	void resettimeManage() {
		timeManage = 0;
	}
	bool checkDone() {
		return timeManage >= timeOverall;
	}
	bool checkMoveTo(){
		return (timeManage < timeMoving);
	}
	bool checkMoveBack() {
		return (timeManage > timeOverall - timeMoving);
	}
	bool checkResting() {
		return !checkMoveBack() && !checkMoveTo();
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
			a[kind].x = b[kind].x = temp;
		}
		else
		{
			temp = randVerticle();
			a[kind].y = b[kind].y = temp;
		}
		//cout << "set " << a[kind].X << " " << a[kind].Y << "\n";
		this->setXY(a[kind], kind);
	}

	void update(const float & dt) {
		static bool flag = true;
		static int kind = 0;
		
		timeManage += dt;
		

		if (checkDone())
		{
			//cout << "invisible\n";
			//this->gui->get<tgui::Picture>(s[kind])->setVisible(false);
			this->resettimeManage();
			// random 1 of 4 edges: up:0, down:1, left:2, right:3
			srand(time(NULL));
			kind = ((1ll*rand()*rand()%1000000007 + rand()*rand()) % 4);
			//kind = 1;
			//pass kind to setEdge
			this->setEdge(kind);

			flag = true;
		}
		if (checkMoveTo())
		{
			if(flag) {
				flag = false;
				//this->gui->get<tgui::Picture>(s[kind])->setVisible(true);
				velocity = this->calcVelocity(b[kind], timeMoving, kind);
			} else moveCharacter(kind, dt);
			//cout << dt << endl;
		}
		if (checkMoveBack())
		{
			if (!flag) {
				flag = true;
				velocity = this->calcVelocity(a[kind], timeMoving, kind);
			} else moveCharacter(kind, dt);
		}
		if (checkResting()) {
			velocity = { 0, 0 };
		}

	}
	
	void render(sf::RenderTarget* target) {
		target->draw(this->sprite);
	}
};