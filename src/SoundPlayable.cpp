#include "SoundPlayable.h"

SoundPlayable::SoundPlayable(AudioController &ctrl) : controller(ctrl) {}

void SoundPlayable::playSound(SoundEffect::ID id) {
    controller.playSound(id);
}
