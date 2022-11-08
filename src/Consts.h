#pragma once

#include <SFML/Graphics.hpp>

const sf::Time DEF_ANIMATION_DURATION = sf::seconds(1.f);

const sf::Time JUMP_DURATION = sf::milliseconds(30);

const sf::Time PAUSE_BETWEEN_JUMPS = sf::milliseconds(15);

/**
 * Or space between jumps
 */
const sf::Vector2f GRID_SIZE{66, 66};

const sf::Vector2u DEF_SPRITE_SIZE = {128, 128};