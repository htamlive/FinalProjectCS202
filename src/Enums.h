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
        Null,
    };
}

namespace Event {
    enum ID {
        LightChanged
    };
}