#pragma once

#include <SFML/Graphics.hpp>

class Box : public sf::RectangleShape {
public:
    Box() = default;

    /**
     * @param x top left x
     * @param y top left y
     * @param h height of the box
     * @param w width of the box
     */
    Box(float x, float y, float w, float h);

    /**
     * Checks for collisions between 2 boxes. Touching on edges or corners are counted.
     *
     * @return <tt>true</tt> if collision is detected, otherwise <tt>false</tt>.
     */
    bool isCollided(const Box &other) const;
    /**
     * Gets distance between centers of 2 boxes.
     *
     * @return <tt>float</tt>
     */
    float getDis(const Box &) const;
};