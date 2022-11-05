// FinalProjectCS202.cpp : Defines the entry point for the application.
#include "Game.h"

#include "FinalProjectCS202.h"
//#include "Entity.h"
//#include "TextureHolder.h"
//#include "AudioController.h"
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>


int main()
{

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