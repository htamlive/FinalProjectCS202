#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <map>
#include <string>
#include <memory>

namespace SoundEffect {
    enum ID {
        Hit,
    };
}


namespace Music {
    enum ID {
        Game, Menu, Pause
    };
}

/**
 * A Singleton unit used for controlling audio
 * Only classes that inherit SoundPlayable will be able to access audio play interface
*/
class AudioController {
    AudioController();
    static AudioController* _instance;

    friend class SoundPlayable;

    std::map<Music::ID, std::string> musicPlaylist;
    std::map<SoundEffect::ID, std::unique_ptr<sf::SoundBuffer>> soundBar;

    sf::Music music;
    sf::Sound sound;
    float musicVolume;
    bool isMuted;
  
    void loadMusicFromFile(Music::ID type, const std::string &path);
    void loadSoundFromFile(SoundEffect::ID id, const std::string &path);
    sf::SoundBuffer& getSoundBuffer(SoundEffect::ID id);
    void updateSettings();
    void playSound(SoundEffect::ID id);

public:
    AudioController(const AudioController&) = delete;
    void operator=(const AudioController&) = delete;
    static AudioController &instance();

    void playMusic(Music::ID id);
    void resumeMusic();
    void pauseMusic();
    void setMuted(bool);
    void setMusicVolumn(float vol);
};
