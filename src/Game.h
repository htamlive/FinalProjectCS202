#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <thread>
#include "MainMenuState.h"


class Game {
private:
    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event ev;
    std::vector<sf::VideoMode> videoModes;
    sf::ContextSettings windowSettings;
    std::map<std::string, int> supportedKeys;
    bool fullscreen;

    sf::Clock dtClock;
    float dt;

    std::vector<State *> states;


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
        AudioController::instance().loadSoundFromFile(SoundEffect::Invisible, "resources/music/invisible.wav");
        AudioController::instance().loadSoundFromFile(SoundEffect::Small, "resources/music/small.wav");
        AudioController::instance().loadSoundFromFile(SoundEffect::Speed, "resources/music/speed.wav");
        AudioController::instance().loadSoundFromFile(SoundEffect::InvincibleVoice, "resources/music/yummyDemon.wav");
        AudioController::instance().loadSoundFromFile(SoundEffect::SpeedVoice, "resources/music/iamspeed.wav");

        AudioController::instance().playMusic(Music::Game, true);

        int value;
        ifstream fin;
        fin.open("resources/textFile/MusicController.txt");
        fin >> value;
        AudioController::instance().setMusicVolume(value);
        fin.open("resources/textFile/SoundController.txt");
        fin >> value;
        AudioController::instance().setSoundVolume(value);
        fin.close();

    }

    void initKeys() {
        this->supportedKeys.emplace("Escape", sf::Keyboard::Key::Escape);
        this->supportedKeys.emplace("A", sf::Keyboard::Key::A);
        this->supportedKeys.emplace("W", sf::Keyboard::Key::W);
        this->supportedKeys.emplace("D", sf::Keyboard::Key::D);
        this->supportedKeys.emplace("S", sf::Keyboard::Key::S);
    }

    void initMainCharacterTextures() {
        TextureHolder::instance().load(Texture::ID::PlayerIdleUp, "resources/spritesheet/character/idleUp.png",
                                       {128, 128},
                                       6);
        TextureHolder::instance().load(Texture::ID::PlayerIdleDown, "resources/spritesheet/character/idleDown.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerIdleLeft, "resources/spritesheet/character/idleLeft.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerIdleRight, "resources/spritesheet/character/idleRight.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerJumpLeft, "resources/spritesheet/character/goLeft.png",
                                       {128, 128},
                                       6);
        TextureHolder::instance().load(Texture::ID::PlayerJumpRight, "resources/spritesheet/character/goRight.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerJumpUp, "resources/spritesheet/character/goUp.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerJumpDown, "resources/spritesheet/character/goDown.png",
                                       {128, 128},
                                       4);
        TextureHolder::instance().load(Texture::ID::PlayerIdleUpInvincible, "resources/spritesheet/character/invisible/idleUpInvisible.png",
                                       {128, 128},
                                       6);
        TextureHolder::instance().load(Texture::ID::PlayerIdleDownInvincible, "resources/spritesheet/character/invisible/idleDownInvisible.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerIdleLeftInvincible, "resources/spritesheet/character/invisible/idleLeftInvisible.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerIdleRightInvincible, "resources/spritesheet/character/invisible/idleRightInvisible.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerJumpLeftInvincible, "resources/spritesheet/character/invisible/goLeftInvisible.png",
                                       {128, 128},
                                       6);
        TextureHolder::instance().load(Texture::ID::PlayerJumpRightInvincible, "resources/spritesheet/character/invisible/goRightInvisible.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerJumpUpInvincible, "resources/spritesheet/character/invisible/goUpInvisible.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerJumpDownInvincible, "resources/spritesheet/character/invisible/goDownInvisible.png",
                                       {128, 128},
                                       4);
        TextureHolder::instance().load(Texture::ID::PlayerIdleUpStunned, "resources/spritesheet/character/stunned/idleUpStun.png", {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerIdleDownStunned, "resources/spritesheet/character/stunned/idleDownStun.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerIdleLeftStunned, "resources/spritesheet/character/stunned/idleLeftStun.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerIdleRightStunned, "resources/spritesheet/character/stunned/idleRightStun.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::RIP, "resources/spritesheet/character/rip.png", {128, 128}, 1);
    }

    void initTrafficLightTextures() {
        TextureHolder::instance().load(Texture::ID::GreenLight, "./resources/images/greenLight.png");
        TextureHolder::instance().load(Texture::ID::RedLight, "./resources/images/redLight.png");
        TextureHolder::instance().load(Texture::ID::RedToGreen, "./resources/spritesheet/character/redToGreen.png",
                                       {128, 128}, 5);
        TextureHolder::instance().load(Texture::ID::GreenToRed, "./resources/spritesheet/character/greenToRed.png",
                                       {128, 128}, 5);
    }

    void initWaterTextures() {
        TextureHolder::instance().load(Texture::ID::WaterAndWood, "resources/images/waterAndWood.png", { 128, 128 }, 16,
            4);
        TextureHolder::instance().add(Texture::ID::WaterTopLane, { Texture::ID::WaterAndWood, 0, false, false });
        TextureHolder::instance().add(Texture::ID::WaterBeforeWoodTopLane,
            { Texture::ID::WaterAndWood, 1, false, false });
        TextureHolder::instance().add(Texture::ID::TopWoodLane, { Texture::ID::WaterAndWood, 2, false, false });
        TextureHolder::instance().add(Texture::ID::WaterAfterWoodTopLane, { Texture::ID::WaterAndWood, 3, false, false });
        TextureHolder::instance().add(Texture::ID::WaterMidLane, { Texture::ID::WaterAndWood, 4, false, false });
        TextureHolder::instance().add(Texture::ID::WaterBeforeWoodMidLane,
            { Texture::ID::WaterAndWood, 5, false, false });
        TextureHolder::instance().add(Texture::ID::MidWoodLane, { Texture::ID::WaterAndWood, 6, false, false });
        TextureHolder::instance().add(Texture::ID::WaterAfterWoodMidLane, { Texture::ID::WaterAndWood, 7, false, false });
        TextureHolder::instance().add(Texture::ID::WaterBotLane, { Texture::ID::WaterAndWood, 8, false, false });
        TextureHolder::instance().add(Texture::ID::WaterBeforeWoodBotLane,
            { Texture::ID::WaterAndWood, 9, false, false });
        TextureHolder::instance().add(Texture::ID::BotWoodLane, { Texture::ID::WaterAndWood, 10, false, false });
        TextureHolder::instance().add(Texture::ID::WaterAfterWoodBotLane,
            { Texture::ID::WaterAndWood, 11, false, false });
        TextureHolder::instance().add(Texture::ID::WaterMonoLane, { Texture::ID::WaterAndWood, 12, false, false });
        TextureHolder::instance().add(Texture::ID::WaterBeforeWoodMonoLane,
            { Texture::ID::WaterAndWood, 13, false, false });
        TextureHolder::instance().add(Texture::ID::MonoWoodLane, { Texture::ID::WaterAndWood, 14, false, false });
        TextureHolder::instance().add(Texture::ID::WaterAfterWoodMonoLane,
            { Texture::ID::WaterAndWood, 15, false, false });
    }

    void initLaneTextures() {
        TextureHolder::instance().load(Texture::ID::Road, "./resources/images/VehicleRoad.png", {128, 128}, 9);
        TextureHolder::instance().add(Texture::ID::TopRoadLane, {Texture::ID::Road, 1, false, false});
        TextureHolder::instance().add(Texture::ID::MidRoadLane, {Texture::ID::Road, 4, false, false});
        TextureHolder::instance().add(Texture::ID::BotRoadLane, {Texture::ID::Road, 7, false, false});
        TextureHolder::instance().add(Texture::ID::MonoRoadLane, {Texture::ID::Road, 8, false, false});

        initWaterTextures();
    }

    void initTheme() {
        TextureHolder::instance().load(Texture::LightningTheme, "./resources/spritesheet/lightning.png", {128,128},1);

    }

    void initLoad() {
        TextureHolder::instance().load(Texture::ID::RightRedTruck, "./resources/spritesheet/vehicles/redTruckRight.png",
            { 128, 128 }, 4);
        TextureHolder::instance().load(Texture::ID::LeftRedTruck, "./resources/spritesheet/vehicles/redTruckLeft.png",
            { 128, 128 }, 4);
        TextureHolder::instance().load(Texture::ID::LeftBlueCar, "./resources/spritesheet/vehicles/blueCar.png",
            { 128, 128 }, 1);
        TextureHolder::instance().load(Texture::ID::LeftGreenCar, "./resources/spritesheet/vehicles/greenCar.png",
            { 128, 128 }, 1);
        TextureHolder::instance().load(Texture::ID::LeftRedCar, "./resources/spritesheet/vehicles/redCar.png", 
            { 128, 128 }, 1);
        TextureHolder::instance().load(Texture::ID::RightCucumber,"./resources/spritesheet/animals/cucumber/moveRight.png",
            { 128, 128 }, 6);
        TextureHolder::instance().load(Texture::ID::RightPlane, "./resources/spritesheet/animals/plane/goRight.png",
            { 128, 128 }, 2);
        TextureHolder::instance().load(Texture::ID::LeftPlane, "./resources/spritesheet/animals/plane/goLeft.png",
            { 128, 128 }, 2);

        TextureHolder::instance().load(Texture::ID::Background, "./resources/images/bg_2.png");
        TextureHolder::instance().load(Texture::ID::Obstacle, "resources/spritesheet/obstacle3.png", { 225, 214 });
        TextureHolder::instance().load(Texture::ID::HealthBoost, "resources/spritesheet/regen.png");
        TextureHolder::instance().load(Texture::ID::SpeedBoost, "resources/spritesheet/speed.png");
        TextureHolder::instance().load(Texture::ID::SmallSizeBoost, "resources/spritesheet/smallSize.png");
        TextureHolder::instance().load(Texture::ID::InvincibleBoost, "resources/spritesheet/invisible.png");
        TextureHolder::instance().load(Texture::ID::Null, "resources/spritesheet/NULL.png", { 32, 32 }, 1);
    }

    void initAdd() {
        TextureHolder::instance().add(Texture::ID::RightBlueCar, { Texture::ID::LeftBlueCar, true, false });

        TextureHolder::instance().add(Texture::ID::RightGreenCar, { Texture::ID::LeftGreenCar, true, false });

        TextureHolder::instance().add(Texture::ID::RightRedCar, { Texture::ID::LeftRedCar, true, false });

        TextureHolder::instance().add(Texture::ID::LeftCucumber, { Texture::ID::RightCucumber, 0, 5, true, false });
    }

    void initTextures() {
        // TODO: add stunned animation
        initLoad();
        initAdd();
        initLaneTextures();
		initTrafficLightTextures();
		initMainCharacterTextures();
        initTheme();

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
