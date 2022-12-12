#pragma once

enum Category {
    None       = 0,
    Scene      = 1 << 0,
    Player     = 1 << 1,
    Enemy      = 1 << 2,
    Obstacle   = 1 << 3,
};

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
    };
}

namespace Event {
    enum ID {
        LightChanged
    };
}
