#pragma once

#include <SFML/Graphics.hpp>

const sf::Time DEF_ANIMATION_DURATION = sf::seconds(6.f);

const sf::Time JUMP_DURATION = sf::milliseconds(300);

const sf::Time LIGHT_CHANGING_DURATION = sf::seconds(1.5);

/**
 * Or space between jumps
 */
const sf::Vector2f GRID_SIZE{25, 25};

const sf::Vector2u DEF_SPRITE_SIZE = {128, 128};
