#pragma once

#include "Entity.h"

class LightObserver {
public:
    virtual void onLightChanged() = 0;
};

/**
 * Light always starts as green.
 */
class Light : public Entity {
public:
    Light() = default;

    Light(sf::Vector2f position, sf::Vector2f size, sf::Time greenTimer, sf::Time redTimer);

    void addObserver(LightObserver *observer);

    std::string getClassName() const override;

    void saveCurrentNode(std::ostream& out = std::cout) const override;

    void loadCurrentNode(std::istream& in = std::cin) override;

protected:
    void updateCurrent(sf::Time dt) override;

private:
    std::vector<LightObserver *> observers;

    void changeLight();

    void changingPhase();

    sf::Time nextTime, currentTime, timer;

    std::pair<std::pair<Texture::ID, Texture::ID>, std::pair<Texture::ID, Texture::ID>> sprites = {{Texture::ID::GreenLight,
                                                                                                           Texture::ID::GreenToRed},
                                                                                                   {Texture::ID::RedLight,
                                                                                                           Texture::ID::RedToGreen}};
};
