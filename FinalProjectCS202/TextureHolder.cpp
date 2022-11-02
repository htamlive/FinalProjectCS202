#include "TextureHolder.h"

TextureHolder &TextureHolder::instance() {
    static TextureHolder *ins = nullptr;
    if (ins == nullptr) {
        ins = new TextureHolder;
    }
    return *ins;
}

void TextureHolder::load(Texture::ID type, const std::string &filename, std::size_t stage = 0) {
    std::unique_ptr<sf::Texture> texture{};
    texture->loadFromFile(filename);
    auto &sprites = textures[type];
    sprites.insert(sprites.begin() + (int) stage, std::move(texture));
}

std::size_t TextureHolder::load(Texture::ID type, const std::vector<std::string> &filenames) {
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

std::size_t TextureHolder::getSpritesSize(Texture::ID type) const {
    auto found = textures.find(type);
    return found->second.size();
}
