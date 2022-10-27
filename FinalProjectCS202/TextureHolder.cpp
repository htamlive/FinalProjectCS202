#include "TextureHolder.h"

TextureHolder *TextureHolder::self = nullptr;

TextureHolder &TextureHolder::instance() {
    if (self == nullptr) {
        self = new TextureHolder;
    }
    return *self;
}

void TextureHolder::load(TextureType type, const std::string &filename, std::size_t stage = 0) {
    std::unique_ptr<sf::Texture> texture{};
    texture->loadFromFile(filename);
    auto &sprites = textures[type];
    sprites.insert(sprites.begin() + (int) stage, std::move(texture));
}

std::size_t TextureHolder::load(TextureType type, const std::vector<std::string> &filenames) {
    auto &sprites = textures[type];
    for (auto &filename: filenames) {
        std::unique_ptr<sf::Texture> texture{};
        texture->loadFromFile(filename);
        sprites.emplace_back(std::move(texture));
    }
    return sprites.size();
}

sf::Texture &TextureHolder::get(const SpriteStage &spriteStage) {
    auto type = spriteStage.getType();
    auto stage = spriteStage.getStage();
    auto found = textures.find(type);
    return *(found->second[stage]);
}

sf::Texture const &TextureHolder::get(const SpriteStage &spriteStage) const {
    auto type = spriteStage.getType();
    auto stage = spriteStage.getStage();
    auto found = textures.find(type);
    return *(found->second[stage]);
}

std::size_t TextureHolder::getSpritesSize(TextureType type) const {
    auto found = textures.find(type);
    return found->second.size();
}
