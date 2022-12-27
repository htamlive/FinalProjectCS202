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
    LeftRedTruck,
    RightRedTruck,
    LeftBlueCar,
    RightBlueCar,
    LeftGreenCar,
    RightGreenCar,
    LeftRedCar,
    RightRedCar,
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
    Background,
    Obstacle,
    Object,
    RIP,
    SmallSizeBoost,
    SpeedBoost,
    HealthBoost,
    InvincibleBoost,
    WaterAndWood,
    TopWoodLane,
    MidWoodLane,
    BotWoodLane,
    MonoWoodLane,
    WaterTopLane,
    WaterMidLane,
    WaterBotLane,
    WaterMonoLane,
    WaterBeforeWoodTopLane,
    WaterBeforeWoodMidLane,
    WaterBeforeWoodBotLane,
    WaterBeforeWoodMonoLane,
    WaterAfterWoodTopLane,
    WaterAfterWoodMidLane,
    WaterAfterWoodBotLane,
    WaterAfterWoodMonoLane
};
}