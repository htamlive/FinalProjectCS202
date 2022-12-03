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
        TopVehicleLane,
        MidVehicleLane,
        BotVehicleLane,
        MonoVehicleLane
    };
}

namespace Event {
    enum ID {
        LightChanged
    };
}
