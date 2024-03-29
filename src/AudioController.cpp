#include "AudioController.h"
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <memory>
#include <iostream>
#include <stdexcept>

AudioController &AudioController::instance() {
    static AudioController _instance;
    return _instance;
}

void AudioController::playSound(SoundEffect::ID id) {
    if (isMuted)
        return;
    sounds.emplace_back(getSoundBuffer(id));
    sounds.back().setVolume(soundVolume);
    sounds.back().play();
}

sf::SoundBuffer &AudioController::getSoundBuffer(SoundEffect::ID id) {
    auto found = soundBar.find(id);
    return *found->second;
}

void AudioController::pauseSound() {
    while(sounds.size())
    {
        sounds.pop_front();
    }
}

void AudioController::playMusic(Music::ID id, bool loop) {
    auto filename = musicPlaylist.find(id)->second;

    if (music.openFromFile(filename)) {
        music.play();
        music.setLoop(loop);
    } else {
        std::cerr << "Loading music from \"" + filename + "\" failed.\n";
    }
}

void AudioController::pauseMusic() {
    music.pause();
}

void AudioController::resumeMusic() {
    music.play();
}

void AudioController::setMuted(bool mute) {
    isMuted = mute;

    updateSettings();
}

void AudioController::setMusicVolume(float vol) {
    musicVolume = vol;

    updateSettings();
}

void AudioController::updateSettings() {
    if (isMuted) {
        music.setVolume(0);
    } else {
        music.setVolume(musicVolume);
    }

}

void AudioController::loadMusicFromFile(Music::ID id, const std::string &path) {
    musicPlaylist.insert({id, path});
}

void AudioController::loadSoundFromFile(SoundEffect::ID id, const std::string &path) {
    std::unique_ptr<sf::SoundBuffer> pBuffer(new sf::SoundBuffer);
    if (pBuffer->loadFromFile(path)) {
        soundBar.insert({id, std::move(pBuffer)});
    } else {
        std::cerr << "Loading sound effect from \"" << path << "\" failed.\n";
    }
}

void AudioController::removeStoppedSounds() {
    sounds.remove_if([](const auto &sound) {
        return sound.getStatus() == sf::Sound::Stopped;
    });
}
