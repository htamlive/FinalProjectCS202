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
    Wood,
    Water
};
}

enum class EffectType {
    HealthBoost,
    SmallSizeBoost,
    SpeedBoost,
    InvincibleBoost,
    Hungry,
    HitEnemy,
    Drunk,
    Drown
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
    TopRiverLane,
    MidRiverLane,
    BotRiverLane,
    MonoRiverLane,
    SafeLane,
    Background,
    Obstacle,
    Object,
    RIP,
    HealthBoost,
    WaterAndWood,
    Water,
    WaterBeforeWood,
    WaterAfterWood,
    Wood
};
}