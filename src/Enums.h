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
    Health,
    Wood
};
}

namespace Texture {
enum ID {
    LeftVehicle,
    RightVehicle,
    LeftAnimal,
    RightAnimal,
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