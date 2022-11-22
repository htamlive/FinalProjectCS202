#pragma once

namespace Texture {
    enum ID {
        VehicleSprites,
        AnimalSprites,
        StandingSprites,
        JumpingSprites,
        RedLightSprite,
        GreenLightSprite,

        Null,

        PlayerStanding,
        PlayerGoLeft,
        PlayerGoRight,
        PlayerGoUp,
        PlayerGoDown,
    };
}

namespace Event {
    enum ID {
        LightChanged
    };
}