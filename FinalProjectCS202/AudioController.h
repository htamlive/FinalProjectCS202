#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <map>
#include <string>
#include <memory>
#include "Enums.h"

namespace SoundEffect
{
    enum ID { Hit, };
}


namespace Music
{
    enum ID { Game, Menu, Pause };
}

class AudioController {
    std::map<Music::ID, std::string> musicPlaylist;
    std::map<SoundEffect::ID, std::unique_ptr<sf::SoundBuffer>> soundBar;

    sf::Music music;
    sf::Sound sound;
    float musicVolume;
    bool isMuted;

    AudioController();
    static AudioController* _instance;

    void loadMusicFromFile(Music::ID type, const std::string &path);
    void loadSoundFromFile(SoundEffect::ID id, const std::string &path);
    sf::SoundBuffer& getSoundBuffer(SoundEffect::ID id);
    void updateSettings();

public:
    AudioController(const AudioController&) = delete;
    void operator=(const AudioController&) = delete;
    static AudioController &instance();

    void playMusic(Music::ID id);
    void resumeMusic();
    void pauseMusic();
    void playSound(SoundEffect::ID id);
    void setMuted(bool);
    void setMusicVolumn(float vol);
};
