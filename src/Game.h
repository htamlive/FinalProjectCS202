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
        AudioController::instance().loadMusicFromFile(Music::Game, APPDATA_PATH + "/resources/music/music_zapsplat_easy_cheesy.wav");
        AudioController::instance().loadSoundFromFile(SoundEffect::GameOver, APPDATA_PATH + "/resources/music/NegativeBeep.wav");
        AudioController::instance().loadSoundFromFile(SoundEffect::Jump, APPDATA_PATH + "/resources/music/jumpSound.wav");
        AudioController::instance().loadSoundFromFile(SoundEffect::Stun, APPDATA_PATH + "/resources/music/BirdsSound.wav");
        AudioController::instance().loadSoundFromFile(SoundEffect::Hitting, APPDATA_PATH + "/resources/music/hitCat.wav");
        AudioController::instance().loadSoundFromFile(SoundEffect::Regen, APPDATA_PATH + "/resources/music/regen.wav");
        AudioController::instance().loadSoundFromFile(SoundEffect::Invisible, "/resources/music/invisible.wav");
        AudioController::instance().loadSoundFromFile(SoundEffect::Small, APPDATA_PATH + "/resources/music/small.wav");
        AudioController::instance().loadSoundFromFile(SoundEffect::Speed, APPDATA_PATH + "/resources/music/speed.wav");
        AudioController::instance().loadSoundFromFile(SoundEffect::InvincibleVoice, APPDATA_PATH + "/resources/music/yummyDemon.wav");
        AudioController::instance().loadSoundFromFile(SoundEffect::SpeedVoice, APPDATA_PATH + "/resources/music/iamspeed.wav");

        AudioController::instance().playMusic(Music::Game, true);

        int value;
        ifstream fin;
        fin.open(APPDATA_PATH + "/resources/textFile/MusicController.txt");
        fin >> value;
        AudioController::instance().setMusicVolume(value);
        fin.open(APPDATA_PATH + "/resources/textFile/SoundController.txt");
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
        TextureHolder::instance().load(Texture::ID::PlayerIdleUp, APPDATA_PATH + "/resources/spritesheet/character/idleUp.png",
                                       {128, 128},
                                       6);
        TextureHolder::instance().load(Texture::ID::PlayerIdleDown, APPDATA_PATH + "/resources/spritesheet/character/idleDown.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerIdleLeft, APPDATA_PATH + "/resources/spritesheet/character/idleLeft.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerIdleRight, APPDATA_PATH + "/resources/spritesheet/character/idleRight.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerJumpLeft, APPDATA_PATH + "/resources/spritesheet/character/goLeft.png",
                                       {128, 128},
                                       6);
        TextureHolder::instance().load(Texture::ID::PlayerJumpRight, APPDATA_PATH + "/resources/spritesheet/character/goRight.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerJumpUp, APPDATA_PATH + "/resources/spritesheet/character/goUp.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerJumpDown, APPDATA_PATH + "/resources/spritesheet/character/goDown.png",
                                       {128, 128},
                                       4);
        TextureHolder::instance().load(Texture::ID::PlayerIdleUpInvincible, APPDATA_PATH + "/resources/spritesheet/character/invisible/idleUpInvisible.png",
                                       {128, 128},
                                       6);
        TextureHolder::instance().load(Texture::ID::PlayerIdleDownInvincible, APPDATA_PATH + "/resources/spritesheet/character/invisible/idleDownInvisible.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerIdleLeftInvincible, APPDATA_PATH + "/resources/spritesheet/character/invisible/idleLeftInvisible.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerIdleRightInvincible, APPDATA_PATH + "/resources/spritesheet/character/invisible/idleRightInvisible.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerJumpLeftInvincible, APPDATA_PATH + "/resources/spritesheet/character/invisible/goLeftInvisible.png",
                                       {128, 128},
                                       6);
        TextureHolder::instance().load(Texture::ID::PlayerJumpRightInvincible, APPDATA_PATH + "/resources/spritesheet/character/invisible/goRightInvisible.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerJumpUpInvincible, APPDATA_PATH + "/resources/spritesheet/character/invisible/goUpInvisible.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerJumpDownInvincible, APPDATA_PATH + "/resources/spritesheet/character/invisible/goDownInvisible.png",
                                       {128, 128},
                                       4);
        TextureHolder::instance().load(Texture::ID::PlayerIdleUpStunned, APPDATA_PATH + "/resources/spritesheet/character/stunned/idleUpStun.png", {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerIdleDownStunned, APPDATA_PATH + "/resources/spritesheet/character/stunned/idleDownStun.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerIdleLeftStunned, APPDATA_PATH + "/resources/spritesheet/character/stunned/idleLeftStun.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::PlayerIdleRightStunned, APPDATA_PATH + "/resources/spritesheet/character/stunned/idleRightStun.png",
                                       {128, 128}, 6);
        TextureHolder::instance().load(Texture::ID::RIP, APPDATA_PATH + "/resources/spritesheet/character/rip.png", {128, 128}, 1);
    }

    void initTrafficLightTextures() {
        TextureHolder::instance().load(Texture::ID::GreenLight, APPDATA_PATH + "/resources/images/greenLight.png");
        TextureHolder::instance().load(Texture::ID::RedLight, APPDATA_PATH + "/resources/images/redLight.png");
        TextureHolder::instance().load(Texture::ID::RedToGreen, APPDATA_PATH + "/resources/spritesheet/character/redToGreen.png",
                                       {128, 128}, 5);
        TextureHolder::instance().load(Texture::ID::GreenToRed, APPDATA_PATH + "/resources/spritesheet/character/greenToRed.png",
                                       {128, 128}, 5);
    }

    void initWaterTextures() {
        TextureHolder::instance().load(Texture::ID::WaterAndWood, APPDATA_PATH + "/resources/images/waterAndWood.png", { 128, 128 }, 16,
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
        TextureHolder::instance().load(Texture::ID::Road, APPDATA_PATH + "/resources/images/VehicleRoad.png", {128, 128}, 9);
        TextureHolder::instance().add(Texture::ID::TopRoadLane, {Texture::ID::Road, 1, false, false});
        TextureHolder::instance().add(Texture::ID::MidRoadLane, {Texture::ID::Road, 4, false, false});
        TextureHolder::instance().add(Texture::ID::BotRoadLane, {Texture::ID::Road, 7, false, false});
        TextureHolder::instance().add(Texture::ID::MonoRoadLane, {Texture::ID::Road, 8, false, false});

        initWaterTextures();
    }

    void initTheme() {
        TextureHolder::instance().load(Texture::LightningTheme, APPDATA_PATH + "/resources/spritesheet/lightning.png", {128,128},1);

    }

    void initLoad() {
        TextureHolder::instance().load(Texture::ID::RightRedTruck, APPDATA_PATH + "/resources/spritesheet/vehicles/redTruckRight.png",
            { 128, 128 }, 4);
        TextureHolder::instance().load(Texture::ID::LeftRedTruck, APPDATA_PATH + "/resources/spritesheet/vehicles/redTruckLeft.png",
            { 128, 128 }, 4);
        TextureHolder::instance().load(Texture::ID::LeftBlueCar, APPDATA_PATH + "/resources/spritesheet/vehicles/blueCar.png",
            { 128, 128 }, 1);
        TextureHolder::instance().load(Texture::ID::LeftGreenCar, APPDATA_PATH + "/resources/spritesheet/vehicles/greenCar.png",
            { 128, 128 }, 1);
        TextureHolder::instance().load(Texture::ID::LeftRedCar, APPDATA_PATH + "/resources/spritesheet/vehicles/redCar.png",
            { 128, 128 }, 1);
        TextureHolder::instance().load(Texture::ID::RightCucumber, APPDATA_PATH + "/resources/spritesheet/animals/cucumber/moveRight.png",
            { 128, 128 }, 6);
        TextureHolder::instance().load(Texture::ID::RightPlane, APPDATA_PATH + "/resources/spritesheet/animals/plane/goRight.png",
            { 128, 128 }, 2);
        TextureHolder::instance().load(Texture::ID::LeftPlane, APPDATA_PATH + "/resources/spritesheet/animals/plane/goLeft.png",
            { 128, 128 }, 2);

        TextureHolder::instance().load(Texture::ID::Background, APPDATA_PATH + "/resources/images/bg_2.png");
        TextureHolder::instance().load(Texture::ID::Obstacle, APPDATA_PATH + "/resources/spritesheet/obstacle3.png", { 225, 214 });
        TextureHolder::instance().load(Texture::ID::HealthBoost, APPDATA_PATH + "/resources/spritesheet/regen.png");
        TextureHolder::instance().load(Texture::ID::SpeedBoost, APPDATA_PATH + "/resources/spritesheet/speed.png");
        TextureHolder::instance().load(Texture::ID::SmallSizeBoost, APPDATA_PATH + "/resources/spritesheet/smallSize.png");
        TextureHolder::instance().load(Texture::ID::InvincibleBoost, APPDATA_PATH + "/resources/spritesheet/invisible.png");
        TextureHolder::instance().load(Texture::ID::Null, APPDATA_PATH + "/resources/spritesheet/NULL.png", { 32, 32 }, 1);
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
