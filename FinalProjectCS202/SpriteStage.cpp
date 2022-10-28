#include "SpriteStage.h"
#include "TextureHolder.h"

SpriteStage::SpriteStage(Texture::ID type) : type(type), stage(0) {
    size = TextureHolder::instance().getSpritesSize(type);
}

Texture::ID SpriteStage::getType() const {
    return type;
}

int SpriteStage::getStage() const {
    return stage;
}

int SpriteStage::next() {
    return (stage = (stage + 1) % (int) size);
}

int SpriteStage::prev() {
    return (stage = (stage + (int) size - 1) % (int) size);
}
