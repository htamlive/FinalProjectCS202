#pragma once

#include "Lane.h"

class SafeLane : public Lane {
private:
    float height;
    Texture::ID texture;

public:
    SafeLane();

    SafeLane(float y, Texture::ID texture);

    SafeLane(float y, float height, Texture::ID texture);

    void setLaneHeight(float) override;

    void setPosY(float) override;

    float getTopY() const override;

    float getBottomY() const override;

    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
};