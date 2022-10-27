#include "Entity.h"

Entity::Entity(TextureType type, float velocity, float x, float y, float w, float h) : spriteStage(type),
                                                                                       velocity(velocity),
                                                                                       box(x, y, w, h) {}

void Entity::move(float dt, float direction_x, float direction_y) {

}

void Entity::update() {

}

void Entity::render() {

}
