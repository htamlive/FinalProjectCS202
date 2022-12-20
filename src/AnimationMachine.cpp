#include "AnimationMachine.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

AnimationMachine::AnimationMachine(Texture::ID textureID, sf::Time duration,
                                   bool loop)
    : id(textureID), duration(duration), loop(loop) {}

void AnimationMachine::update(sf::Time dt) {
    if (elapsedTime < duration) {
        elapsedTime += dt;
        if (loop && elapsedTime >= duration) {
            elapsedTime = sf::Time::Zero;
        }
    }
}

sf::Sprite AnimationMachine::toSprite() const {
    auto &sheet = getSheet();
    auto frameTime = duration / (float)sheet.getCount();
    auto index = std::min((unsigned int)(elapsedTime / frameTime), sheet.getCount() - 1);
    sf::Sprite sprite = sheet.getSprite(index);
    return sprite;
}

bool AnimationMachine::isFinished() const {
    auto &sheet = getSheet();
    auto frameTime = duration / (float)sheet.getCount();
    return !loop && (int)(elapsedTime / frameTime) >= sheet.getCount();
}

Texture::ID AnimationMachine::getID() const { return id; }

Sheet const &AnimationMachine::getSheet() const {
    return TextureHolder::instance().getSheet(id);
}

void AnimationMachine::save(std::ostream &out) const {
    std::cout << "Saving AnimationMachine" << std::endl;
    out << (int)id << " " << duration.asMilliseconds() << " " << loop << " ";
}

void AnimationMachine::load(std::istream &in) {
    int id;
    in >> id;
    this->id = (Texture::ID)id;
    int duration;
    in >> duration;
    this->duration = sf::milliseconds(duration);
    in >> loop;
    std::cout << "Loaded AnimationMachine" << std::endl;
}
