#pragma once

#include <cstdlib>

#include "Enums.h"

class SpriteStage {
private:
    Texture::ID type;
    int stage;
    std::size_t size;

public:
    SpriteStage();

    SpriteStage(Texture::ID);

    Texture::ID getType() const;

    int getStage() const;

    /**
     * Moves to next stage.
     *
     * @return <tt>int</tt> current stage after moving.
     */
    int next(unsigned int step = 1);

    /**
     * Moves to previous stage.
     *
     * @return <tt>int</tt> current stage after moving.
     */
    int prev(unsigned int step = 1);
};