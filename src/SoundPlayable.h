#pragma once
#include "AudioController.h"
#include <memory>

class SoundPlayable {
    AudioController &controller;

public:
    SoundPlayable(AudioController &controller);
    void playSound(SoundEffect::ID id);
};
