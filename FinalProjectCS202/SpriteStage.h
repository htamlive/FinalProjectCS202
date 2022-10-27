#pragma once

#include <cstdlib>

#include "Enums.h"

class SpriteStage {
private:
    TextureType type;
    int stage;
    std::size_t size;

public:
    SpriteStage() = default;

    SpriteStage(TextureType);

    TextureType getType() const;

    int getStage() const;

    /**
     * Moves to next stage.
     *
     * @return <tt>int</tt> current stage after moving.
     */
    int next();
    /**
     * Moves to previous stage.
     *
     * @return <tt>int</tt> current stage after moving.
     */
    int prev();
};