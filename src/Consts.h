#pragma once

#include <SFML/Graphics.hpp>
#include "Enums.h"

const sf::Time DEF_ANIMATION_DURATION = sf::seconds(.9f);

const sf::Time JUMP_DURATION = sf::milliseconds(600);

const sf::Time LIGHT_CHANGING_DURATION = sf::seconds(1.5);


const sf::VideoMode WINDOW_VIDEO_MODE = {1024, 768};

/**
 * Or space between jumps
 */
const sf::Vector2f GRID_SIZE{64, 64};

const sf::Vector2u DEF_SPRITE_SIZE = {128, 128};

const float MINIMUM_WIDTH_BETWEEN_VEHICLES = GRID_SIZE.x * 1.5f;

const sf::Vector2f DEF_COMMUTER_SIZE = {90, 90};

const float DEF_LANE_HEIGHT = 66.f;


const sf::Vector2f DEF_PLAYER_VELOCITY = {100, 100};
