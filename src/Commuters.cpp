#include "Commuters.h"
#include "Consts.h"
#include "TextureHolder.h"

void Vehicle::onLightChanged() {
    auto oldVelocity = getVelocity();
    setVelocity(tmpVelocity);
    tmpVelocity = oldVelocity;
}

Category::Type Vehicle::getCategory() const {
    if (getVelocity() != sf::Vector2f(0, 0)) {
        return Enemy::getCategory();
    } else
        return Obstacle::getCategory();
}

void Vehicle::onStartPlayerCollision() {
    if (getCategory() == Enemy::getCategory()) {
        Enemy::onStartPlayerCollision();
    } else {
        Obstacle::onStartPlayerCollision();
    }
}

void Vehicle::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
    if (getCategory() == Enemy::getCategory()) {
        Enemy::updateCurrent(dt);
    } else {
        Obstacle::updateCurrent(dt);
    }
}

Category::Type Water::getCategory() const {
    return Category::Water;
}

void Water::onStartPlayerCollision() {
    auto effect = std::make_unique<StopOnCommandEffect>();
    effect->concat(EffectFactory::create(EffectType::Drown));
    damageEffect = effect.get();
    player->addEffect(std::move(effect));
}

void Water::onEndPlayerCollision() {
    damageEffect->stop();
    damageEffect = nullptr;
}

void Water::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
    PlayerCollidable::updateCurrent(dt);
}

Water::Water() : Entity(), PlayerCollidable(), startTexture(), midTexture(), endTexture(), squareCount(0) {}

Water::Water(Texture::ID startTexture, Texture::ID midTexture, Texture::ID endTexture, sf::Vector2f position,
             sf::Vector2f sizePerSquare, unsigned int squareCount, sf::Vector2f velocity) : Entity({},
                                                                                                   position,
                                                                                                   {sizePerSquare.x * (float)squareCount,
                                                                                                  sizePerSquare.y},
                                                                                                  velocity),
                                                                                            PlayerCollidable(),
                                                                                            startTexture(startTexture),
                                                                                            midTexture(midTexture),
                                                                                            endTexture(endTexture),
                                                                                            squareCount(squareCount) {}

void Water::drawCurrent(sf::RenderTarget &target, sf::RenderStates state) const {
    sf::Vector2f squareSize = {getSpriteBounds().width / (float)squareCount, getSpriteBounds().height};

    for(auto i = 0; i < squareCount; i++) {
        Texture::ID id = i == 0 ? startTexture : i == squareCount - 1 ? endTexture : midTexture;
        auto sprite = TextureHolder::instance().getSheet(id).getSprite(0);
        auto preScale = sprite.getScale();
        sprite.setScale(squareSize.x / sprite.getLocalBounds().width * preScale.x,
                        squareSize.y / sprite.getLocalBounds().height * preScale.y);
        sf::Vector2f pos = {getSpriteBounds().left + squareSize.x * (float)i, getSpriteBounds().top};
        sprite.setPosition(pos);

        target.draw(sprite, state);
    }
}

Category::Type Enemy::getCategory() const {
    return Category::Enemy;
}

void Enemy::onStartPlayerCollision() {
    auto getDirection = [](sf::Vector2f v) {
        if (v.y != 0) {
            v.y /= std::abs(v.y);
        }
        if (v.x != 0) {
            v.x /= std::abs(v.x);
        }
        return v;
    };

    if (!player->isInvincible()) {
        player->takeDamage();
        sf::Vector2f direction = getAbsPosition() - player->getAbsPosition();
        if (abs(direction.x) > abs(direction.y)) {
            direction.y = 0;
        } else {
            direction.x = 0;
        }
        direction = -getDirection(direction);
        sf::Vector2f newPos = player->getPosition() + direction * (GRID_SIZE.x / 2);
        player->setState(new CollidingState(player, newPos));
    }
}

void Animal::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
    PlayerCollidable::updateCurrent(dt);
}
