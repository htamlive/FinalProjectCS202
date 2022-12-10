#pragma once

namespace Identifier {
    enum Catergory {
        None       = 0,
        Scene      = 1 << 0,
        Player     = 1 << 1,
        Vehicle    = 1 << 2,
        Projectile = 1 << 3,
        Pickup     = 1 << 4,
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
    };
}

namespace Event {
    enum ID {
        LightChanged
    };
}
