#pragma once

namespace Category {
enum Type {
    None,
    Scene,
    Player,
    Enemy,
    Obstacle,
    SmallSizeBoost,
    SpeedBoost,
    HealthBoost,
    InvincibleBoost,
    Health,
    Wood
};
}

enum class EffectType {
    HealthBoost,
    SmallSizeBoost,
    SpeedBoost,
    InvincibleBoost,
    Hungry,
    HitEnemy,
    Drunk
};

namespace Texture {
enum ID {
    LeftVehicle,
    RightVehicle,
    LeftCucumber,
    RightCucumber,
    LeftPlane,
    RightPlane,
    PlayerJumpLeft,
    PlayerJumpRight,
    PlayerJumpUp,
    PlayerJumpDown,
    PlayerIdleLeft,
    PlayerIdleRight,
    PlayerIdleUp,
    PlayerIdleDown,
    RedLight,
    GreenLight,
    RedToGreen,
    GreenToRed,
    Road,
    Null,
    TopRoadLane,
    MidRoadLane,
    BotRoadLane,
    MonoRoadLane,
    SafeLane,
    Background,
    Obstacle,
    Object,
    RIP,
    HealthBoost,
    Water,
    Wood
};
}