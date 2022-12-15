#include "Game.h"

void Game::initVariables()
{
	this->window = nullptr;
	this->dt = 0.f;
	this->fullscreen = false;
}

void Game::initWindow()
{

	this->videoModes = sf::VideoMode::getFullscreenModes();

	this->videoMode = WINDOW_VIDEO_MODE;
	//{1300, 800}
	unsigned antialiasing_level = 0;

	this->fullscreen = false;
	this->windowSettings.antialiasingLevel = antialiasing_level;
	if (this->fullscreen) {
		this->window = new sf::RenderWindow(this->videoMode, "Crossing Road", sf::Style::Fullscreen, windowSettings);
	}
	else {

		std::string name;
		name += "Crossing Road";
		//Image icon;
		//icon.loadFromFile("images/icon.png");

		this->window = new sf::RenderWindow(this->videoMode, "Crossing Road", sf::Style::Titlebar | sf::Style::Close, windowSettings);
		
		//this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	}

	this->window->setFramerateLimit(120);
	this->window->setVerticalSyncEnabled(false);


}

void Game::initState()
{
	this->states.push_back(new MainMenuState(this->window, &supportedKeys, &this->states));
	//this->states.push_back(new LoadingState(this->window, &this->states));
}


Game::Game() {
    this->initTextures();
	this->initVariables();
	this->initWindow();
	this->initState();
	this->initMusic();
	this->initKeys();
}

Game::~Game() {
	delete this->window;

	while (!this->states.empty()) {
		delete this->states.back();
		this->states.pop_back();
	}
}

bool Game::running() const
{
	return this->window->isOpen();
}

void Game::updateEvents()
{
	switch (this->ev.type)
	{
	case sf::Event::Closed:
		closeWindow();
		break;
	case sf::Event::KeyReleased:
		keyReleasedProc();
		break;
	case sf::Event::MouseButtonReleased:
		mouseProc();
        break;
    default:
        break;
	}
}

void Game::endApplication()
{
	//std::cout << "Ending application!\n";
}

void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();

	//system("cls");
	//std::cout << this->dt << "\n";
}


void Game::updateSFMLEvents()
{
	if (!this->states.empty()) {
		while (this->window->pollEvent(this->states.back()->ev)) this->states.back()->updateEvents();
	}
	else {
		while (this->window->pollEvent(this->ev)) this->updateEvents();
	}
}

void Game::update()
{

	this->updateSFMLEvents();
	if (!this->states.empty()) {
		this->states.back()->update(this->dt);
		if (this->states.back()->getQuit()) {
			this->states.back()->endState();
			delete this->states.back();
			this->states.pop_back();
		}

	}
	else {
		this->endApplication();
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();
	if (!this->states.empty()) {
		this->states.back()->render();
	}
	this->window->display();
}

void Game::run()
{
	while (this->running())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}

void Game::closeWindow()
{
	this->window->close();
}

void Game::keyReleasedProc()
{
	switch (ev.key.code)
	{
	case sf::Keyboard::Enter:
		//field.restart();
        break;
	case sf::Keyboard::Escape:
		this->window->close();
        break;
    default:
        break;
	}
}

void Game::mouseProc()
{
	switch (this->ev.mouseButton.button)
	{
	case sf::Mouse::Left:
		std::cout << "\nLeft click " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y;
		//field.open_cell(mouse_cell_x, mouse_cell_y);
		break;
	case sf::Mouse::Right:
		std::cout << "\nRight click";
		//field.flag_cell(mouse_cell_x, mouse_cell_y);
        break;
    default:
        break;
    }
}

