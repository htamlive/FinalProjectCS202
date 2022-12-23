#pragma once

#include <SFML/Graphics.hpp>
#include "Enums.h"

const float VEHICLE_LANE_PROB = 0.5
        ;
const float ANIMAL_LANE_PROB = 0.2;

const float RIVER_LANE_PROB = 1 - VEHICLE_LANE_PROB - ANIMAL_LANE_PROB;


const sf::Time DEF_ANIMATION_DURATION = sf::seconds(.9f);

const sf::Time JUMP_DURATION = sf::milliseconds(300);

const sf::Time LIGHT_CHANGING_DURATION = sf::seconds(1.f);

const sf::Time INVINCIBLE_AFTER_DAMAGED_DURATION = sf::seconds(3);


const sf::VideoMode WINDOW_VIDEO_MODE = {1024, 768};

const sf::Vector2f GRID_SIZE{64, 64};

const sf::Vector2u DEF_SPRITE_SIZE = {128, 128};

const float MINIMUM_WIDTH_BETWEEN_VEHICLES = GRID_SIZE.x * 1.5f;

const sf::Vector2f DEF_COMMUTER_SIZE = {100, 100};

const float DEF_LANE_HEIGHT = 66.f;

const float DEF_LIGHT_HEIGHT = DEF_LANE_HEIGHT * 1.2f;

const float DESTROY_PADDING = 100;

const sf::FloatRect DESTROY_BORDER = {-DESTROY_PADDING, -DESTROY_PADDING, (float)WINDOW_VIDEO_MODE.width + DESTROY_PADDING * 2, (float)WINDOW_VIDEO_MODE.height + DESTROY_PADDING * 2};


const sf::Vector2f DEF_PLAYER_VELOCITY = {100, 100};

const float HEALTH_PER_FOOD = 20;

const float DAMAGE_PER_ENEMY = -40;

const float HEALTH_REDUCTION_RATE = -2;

const float MAX_HEALTH = 100;

const float SIZE_SMALLER_BOOST_SCALE = 0.75;
