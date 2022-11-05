#include "SpriteStage.h"
#include "TextureHolder.h"

SpriteStage::SpriteStage() : type(Texture::ID::VehicleSprites), stage(-1), size(-1) {}

SpriteStage::SpriteStage(Texture::ID type) : type(type), stage(-1) {
    size = TextureHolder::instance().getSpritesSize(type);
}

Texture::ID SpriteStage::getType() const {
    return type;
}

int SpriteStage::getStage() const {
    return stage;
}

int SpriteStage::next(unsigned int step) {
    return (stage = (stage + (int) step) % (int) size);
}

int SpriteStage::prev(unsigned int step) {
    step %= size;
    return (stage = (stage + (int) size - (int) step) % (int) size);
}
