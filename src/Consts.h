#pragma once

#include <SFML/Graphics.hpp>

const sf::Time DEF_ANIMATION_DURATION = sf::seconds(6.f);

const sf::Time JUMP_DURATION = sf::seconds(0.6f);

/**
 * Or space between jumps
 */
const sf::Vector2f GRID_SIZE{32, 32};

const sf::Vector2u DEF_SPRITE_SIZE = {128, 128};