#pragma once

namespace Category {
    enum Type {
        None       = 0,
        Scene      = 1 << 0,
        Player     = 1 << 1,
        Enemy      = 1 << 2,
        Obstacle   = 1 << 3,
        Reward     = 1 << 4,
    };
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
        Obstacle,
        Object,
    };
}

namespace Event {
    enum ID {
        LightChanged
    };
}
