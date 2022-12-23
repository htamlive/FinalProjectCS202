#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <thread>
#include "MainMenuState.h"


class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	std::map<std::string, int> supportedKeys;
	bool fullscreen;

	sf::Clock dtClock;
	float dt;

	std::vector<State*> states;


	void initVariables();
	void initWindow();
	void initState();

	void initMusic() {
		//AudioController::instance().loadSoundFromFile(SoundEffect::Hit, "resources/mallHit.wav");
		AudioController::instance().loadMusicFromFile(Music::Game, "resources/music/music_zapsplat_easy_cheesy.wav");
		AudioController::instance().loadSoundFromFile(SoundEffect::GameOver, "resources/music/NegativeBeep.wav");
		AudioController::instance().loadSoundFromFile(SoundEffect::Jump, "resources/music/jumpSound.wav");
		AudioController::instance().loadSoundFromFile(SoundEffect::Stun, "resources/music/BirdsSound.wav");
		AudioController::instance().loadSoundFromFile(SoundEffect::Hitting, "resources/music/hitCat.wav");
		AudioController::instance().loadSoundFromFile(SoundEffect::Regen, "resources/music/regen.wav");
		AudioController::instance().playMusic(Music::Game,true);

		int value;
		ifstream fin;
		fin.open("resources/textFile/MusicController.txt");
		fin >> value;
		AudioController::instance().setMusicVolume(value);
		fin.close();

	}

	void initKeys()
	{
		this->supportedKeys.emplace("Escape", sf::Keyboard::Key::Escape);
		this->supportedKeys.emplace("A", sf::Keyboard::Key::A);
		this->supportedKeys.emplace("W", sf::Keyboard::Key::W);
		this->supportedKeys.emplace("D", sf::Keyboard::Key::D);
		this->supportedKeys.emplace("S", sf::Keyboard::Key::S);
	}

	void initMainCharacterTextures() {
		TextureHolder::instance().load(Texture::ID::PlayerIdleUp, "resources/spritesheet/main/idleUp.png", { 128, 128 }, 6);
		TextureHolder::instance().load(Texture::ID::PlayerIdleDown, "resources/spritesheet/main/idleDown.png", { 128, 128 }, 6);
		TextureHolder::instance().load(Texture::ID::PlayerIdleLeft, "resources/spritesheet/main/idleLeft.png", { 128, 128 }, 6);
		TextureHolder::instance().load(Texture::ID::PlayerIdleRight, "resources/spritesheet/main/idleRight.png", { 128, 128 }, 6);
		TextureHolder::instance().load(Texture::ID::PlayerJumpLeft, "resources/spritesheet/main/goLeft.png", { 128, 128 }, 6);
		TextureHolder::instance().load(Texture::ID::PlayerJumpRight, "resources/spritesheet/main/goRight.png", { 128, 128 }, 6);
		TextureHolder::instance().load(Texture::ID::PlayerJumpUp, "resources/spritesheet/main/goUp.png", { 128, 128 }, 6);
		TextureHolder::instance().load(Texture::ID::PlayerJumpDown, "resources/spritesheet/main/goDown.png", { 128, 128 }, 4);
        TextureHolder::instance().load(Texture::ID::RIP, "resources/spritesheet/main/rip.png", { 128, 128 }, 1);
    }

	void initTrafficLightTextures() {
		TextureHolder::instance().load(Texture::ID::GreenLight, "./resources/images/greenLight.png");
		TextureHolder::instance().load(Texture::ID::RedLight, "./resources/images/redLight.png");
        TextureHolder::instance().load(Texture::ID::RedToGreen, "./resources/spritesheet/main/redToGreen.png", { 128, 128 }, 5);
        TextureHolder::instance().load(Texture::ID::GreenToRed, "./resources/spritesheet/main/greenToRed.png", { 128, 128 }, 5);
    }

	void initLaneTextures() {
		TextureHolder::instance().load(Texture::ID::Road, "./resources/images/VehicleRoad.png", { 128, 128 }, 9);
		TextureHolder::instance().add(Texture::ID::TopRoadLane, { Texture::ID::Road, 1, false, false });
		TextureHolder::instance().add(Texture::ID::MidRoadLane, { Texture::ID::Road, 4, false, false });
		TextureHolder::instance().add(Texture::ID::BotRoadLane, { Texture::ID::Road, 7, false, false });
		TextureHolder::instance().add(Texture::ID::MonoRoadLane, { Texture::ID::Road, 8, false, false });
        TextureHolder::instance().load(Texture::ID::Water, "./resources/images/water.png");
	}

	void initTextures() {
        // TODO: redraw vehicles in other direction
        // TODO: add stunned animation
        TextureHolder::instance().load(Texture::ID::RightVehicle,"./resources/images/truck_1.png", {128, 128}, 4);
        TextureHolder::instance().add(Texture::ID::LeftVehicle, {Texture::ID::RightVehicle, 0, 3, true, false});
        TextureHolder::instance().load(Texture::ID::RightCucumber, "./resources/spritesheet/cucumber/moveRight.png", {128, 128}, 6);
        TextureHolder::instance().add(Texture::ID::LeftCucumber, {Texture::ID::RightCucumber, 0, 5, true, false});
        TextureHolder::instance().load(Texture::ID::RightPlane, "./resources/spritesheet/plane/goRight.png", {128, 128}, 2);
        TextureHolder::instance().load(Texture::ID::LeftPlane, "./resources/spritesheet/plane/goLeft.png", {128, 128}, 2);
        TextureHolder::instance().load(Texture::ID::Wood, "./resources/images/wood.png");
		//TextureHolder::instance().load(Texture::ID::Background,"./resources/images/bg.jpg");
		TextureHolder::instance().load(Texture::ID::Background, "./resources/images/bg_1.png");
        initLaneTextures();
		initTrafficLightTextures();
		initMainCharacterTextures();
		//TextureHolder::instance().load(Texture::ID::Obstacle, "resources/spritesheet/obstacle1.png", { 28, 19 });
		TextureHolder::instance().load(Texture::ID::Obstacle, "resources/spritesheet/obstacle1.png", { 282, 378 });
        TextureHolder::instance().load(Texture::ID::Object, "resources/spritesheet/objects.png", { 16, 16 }, 45, 5);
        TextureHolder::instance().add(Texture::ID::HealthBoost, {Texture::ID::Object, 18, false, false });
        TextureHolder::instance().load(Texture::ID::Null, "resources/spritesheet/NULL.png", { 32, 32 }, 1);
	};

	void updateEvents();
	void updateDt();


public:
	Game();
	virtual ~Game();

	bool running() const;

	void endApplication();

	void updateSFMLEvents();
	void update();

	void render();
	void run();

	void closeWindow();
	void keyReleasedProc();
	void mouseProc();
};
