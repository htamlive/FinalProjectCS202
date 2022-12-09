#pragma once

#include "SceneNode.h"
#include "Enums.h"

class Lane : public SceneNode {
public:
    virtual float getTopY() const = 0;

    virtual float getBottomY() const = 0;

    virtual void setPosY(float) = 0;

    virtual void setLaneHeight(float) = 0;
};

