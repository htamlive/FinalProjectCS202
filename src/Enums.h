#pragma once

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
    };
}

namespace Event {
    enum ID {
        LightChanged
    };
}
