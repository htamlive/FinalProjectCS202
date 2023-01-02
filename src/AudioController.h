#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <map>
#include <string>
#include <memory>
#include <list>

namespace SoundEffect {
    enum ID {
        Hit,
        Jump,
        GreenLight,
        RedLight,
        ButtonPressed, 
        CarNoise,
        GameOver,
        Stun,
        Hitting,
        Regen,
        Invisible,
        Small,
        Speed
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
    AudioController() = default;
    static AudioController _instance;

    std::map<Music::ID, std::string> musicPlaylist;
    std::map<SoundEffect::ID, std::unique_ptr<sf::SoundBuffer>> soundBar;

    sf::Music music;
    std::list<sf::Sound> sounds;
    float musicVolume;
    bool isMuted;

    sf::SoundBuffer& getSoundBuffer(SoundEffect::ID id);
    void updateSettings();

public:
    AudioController(const AudioController&) = delete;
    void operator=(const AudioController&) = delete;
    static AudioController &instance();

    void playMusic(Music::ID id, bool loop = false);
    void resumeMusic();
    void pauseMusic();
    void pauseSound();
    void setMuted(bool);
    void setMusicVolume(float vol);
    void loadMusicFromFile(Music::ID type, const std::string &path);
    void loadSoundFromFile(SoundEffect::ID id, const std::string &path);
    void playSound(SoundEffect::ID id);

    void removeStoppedSounds();
};
