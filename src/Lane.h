#pragma once

#include "SceneNode.h"
#include "Enums.h"

class Lane : public virtual SceneNode {
public:
    virtual void setPosY(float) = 0;

    virtual void setLaneHeight(float) = 0;
};

