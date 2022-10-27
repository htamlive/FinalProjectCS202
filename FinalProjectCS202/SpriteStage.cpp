#include "SpriteStage.h"
#include "TextureHolder.h"

SpriteStage::SpriteStage(TextureType type) : type(type), stage(0) {
    size = TextureHolder::instance().getSpritesSize(type);
}

TextureType SpriteStage::getType() const {
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
