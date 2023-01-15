// FinalProjectCS202.cpp : Defines the entry point for the application.
#include "Game.h"

//#include "Entity.h"
//#include "TextureHolder.h"
//#include "AudioController.h"

int main(int argc, char** argv)
{
    {
        std::string path = argv[0];
        std::filesystem::current_path(path.substr(0, path.find_last_of('/')));
    }
    //AnimationsByFrames animations("FinalProjectCS202/spritesheet/character/goDown.png");

    //cout << APPDATA_PATH;

    Game game;
    game.run();

    //// check build
    //auto &ins = TextureHolder::instance();
    //auto &audio = AudioController::instance();

    // create the window
    //sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    //string t = "World";

    //tgui::String name;
    //name.clear();
    //name.resize(10);
    //name = t;
    //cout << t.length();
    //// run the program as long as the window is open
    //while (window.isOpen())
    //{
    //    // check all the window's events that were triggered since the last iteration of the loop
    //    sf::Event event{};
    //    while (window.pollEvent(event))
    //    {
    //        // "close requested" event: we close the window
    //        if (event.type == sf::Event::Closed)
    //            window.close();
    //    }

    //    // clear the window with black color
    //    window.clear(sf::Color::Black);

    //    // draw everything here...
    //    // window.draw(...);

    //    // end the current frame
    //    window.display();
    //}

    return 0;
};