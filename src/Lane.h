#pragma once

#include "SceneNode.h"
#include "Enums.h"

class Lane : public SceneNode {
public:
    virtual void setPosY(float) = 0;

    virtual void setLaneHeight(float) = 0;

    std::string getClassName() const override {
        return "Lane";
    }
};
