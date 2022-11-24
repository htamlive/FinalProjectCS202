#pragma once

namespace Texture {
    enum ID {
        Vehicle,
        Animal,
        PlayerJumpLeft,
        PlayerJumpRight,
        PlayerJumpUp,
        PlayerJumpDown,

        PlayerGoLeft,
        PlayerGoRight,
        PlayerGoUp,
        PlayerGoDown,
        PlayerStanding,

        PlayerIdleLeft,
        PlayerIdleRight,
        PlayerIdleUp,
        PlayerIdleDown,
        RedLight,
        GreenLight,
        Null,
    };
}

namespace Event {
    enum ID {
        LightChanged
    };
}