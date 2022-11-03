#pragma once

#include "Box.h"
#include "Enums.h"
#include "SpriteStage.h"
#include "Renderable.h"

class Entity : public Renderable {
protected:
    float velocity;
    Box box;
    SpriteStage spriteStage;

public:
    Entity() = default;

    Entity(Texture::ID type, float velocity, float x, float y, float w, float h);
    
    // TODO: how does it move?
    void move(float dt, float direction_x, float direction_y);

    // TODO: update every frame? what does it do?
    virtual void update();

    void render() override;
};