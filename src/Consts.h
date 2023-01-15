#pragma once

#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "Random.h"
#include <filesystem>

#ifdef __linux__ 
const float SYSTEM_SCALE = 1.0f;
const std::string APPDATA_PATH = ".";
const std::string DOCUMENTS_PATH = ".";
#elif _WIN32

#include <TGUI/Backend/SFML-Graphics.hpp>
const float SYSTEM_SCALE = 1.0f;
const std::string APPDATA_PATH = std::filesystem::path(std::getenv("APPDATA")).string() + '\\' + "Crossing Cat\\Windows";
const std::string DOCUMENTS_PATH = std::filesystem::path(std::getenv("USERPROFILE")).string() + "\\Documents";

#elif __APPLE__
const float SYSTEM_SCALE = 1.5f;
const std::string APPDATA_PATH = ".";
const std::string DOCUMENTS_PATH = ".";
#include <ApplicationServices/ApplicationServices.h>
#include <TGUI/TGUI.hpp>
#else

#endif



const float VEHICLE_LANE_PROB = 0.5;

const float ANIMAL_LANE_PROB = 0.3;

const float RIVER_LANE_PROB = 1 - VEHICLE_LANE_PROB - ANIMAL_LANE_PROB;

const std::pair<Category::Type, float> BOOST_PROBS[] = {
    {Category::HealthPickup,     0.6},
    {Category::SmallSizePickup,  0.15},
    {Category::SpeedPickup,      0.2},
    {Category::InvinciblePickup, 0.05},
};


const sf::Time DEF_ANIMATION_DURATION = sf::seconds(.9f);

const sf::Time JUMP_DURATION = sf::milliseconds(300);

const sf::Time LIGHT_CHANGING_DURATION = sf::seconds(1.f);

const sf::Time INVINCIBLE_AFTER_DAMAGED_DURATION = sf::seconds(3);

const sf::Time RECOIL_AFTER_COLLIDING_DURATION = sf::seconds(0.3);

const sf::Time STUNNED_DURATION = sf::seconds(0.5);

const sf::Time MIN_RED_LIGHT_DURATION = sf::seconds(2);

const sf::Time MAX_RED_LIGHT_DURATION = sf::seconds(4);

const sf::Time MIN_GREEN_LIGHT_DURATION = sf::seconds(5);

const sf::Time MAX_GREEN_LIGHT_DURATION = sf::seconds(10);


const sf::VideoMode WINDOW_VIDEO_MODE = {(unsigned int)(1024*SYSTEM_SCALE), (unsigned int)(768* SYSTEM_SCALE) };

const tgui::Vector2f DEF_FILE_DIALOG_POS = { 200*SYSTEM_SCALE, 170*SYSTEM_SCALE};

const tgui::Vector2f DEF_FILE_DIALOG_SIZE = { 650*SYSTEM_SCALE,500*SYSTEM_SCALE };

const sf::Vector2f GRID_SIZE{64* SYSTEM_SCALE, 64* SYSTEM_SCALE };

const sf::Vector2u DEF_SPRITE_SIZE = {128, 128};

const float MINIMUM_WIDTH_BETWEEN_VEHICLES = GRID_SIZE.x * 1.5f *SYSTEM_SCALE;

const sf::Vector2f DEF_COMMUTER_SIZE = {100 * SYSTEM_SCALE, 100 * SYSTEM_SCALE};

const float DEF_LANE_HEIGHT = 66.f * SYSTEM_SCALE;

const float DEF_LIGHT_HEIGHT = DEF_LANE_HEIGHT * 1.2f;

const float DESTROY_PADDING = 100 * SYSTEM_SCALE;

const sf::FloatRect DESTROY_BORDER = {-DESTROY_PADDING, -DESTROY_PADDING, (float)WINDOW_VIDEO_MODE.width + DESTROY_PADDING * 2, (float)WINDOW_VIDEO_MODE.height + DESTROY_PADDING * 2};


const sf::Vector2f DEF_PLAYER_VELOCITY = {100 * SYSTEM_SCALE, 100 * SYSTEM_SCALE};

const float MAX_HEALTH = 100;

const float HEALTH_PER_FOOD = MAX_HEALTH / 5;

const float DAMAGE_PER_ENEMY = -MAX_HEALTH / 100 * 40;

const float HEALTH_REDUCTION_RATE = -MAX_HEALTH / 50;

const float HEALTH_REDUCTION_RATE_WHEN_DROWN = -MAX_HEALTH / 5;

const float SIZE_SMALLER_BOOST_SCALE = 0.5;

const float JUMP_DURATION_BOOST_SCALE = 0.5;

const auto DEF_FREQUENCY_FUNCTION = [](double speed) {
    auto spawnRate = 400 / speed;
    return Random<std::normal_distribution<double>>(std::normal_distribution<double>(spawnRate, spawnRate / 3));
};

const sf::Time SMALL_SIZE_BOOST_DURATION = sf::seconds(5);

const sf::Time SPEED_BOOST_DURATION = sf::seconds(5);

const sf::Time INVINCIBLE_BOOST_DURATION = sf::seconds(5);