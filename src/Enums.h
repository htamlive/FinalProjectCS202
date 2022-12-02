#pragma once

namespace Texture {
    enum ID {
        Vehicle,
        Animal,
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
        TopLane,
        MidLane,
        BotLane
    };
}

namespace Event {
    enum ID {
        LightChanged
    };
}
