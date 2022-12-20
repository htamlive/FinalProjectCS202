// #include "Enums.h"
// #include "SceneNode.h"
// #include "Entity.h"
// #include "TextureHolder.h"
// #include "Player.h"
// #include "GameLoader.h"
//
// #include <SFML/Graphics/RenderWindow.hpp>
// #include <iostream>
// #include <memory>
// #include <fstream>
// #include <SFML/Graphics.hpp>
//
// int main() {
//     TextureHolder::instance().load(Texture::LeftVehicle, "../resources/images/greenCar.png");
//     std::ofstream fout("testSave.txt");
//     SceneNode root;
//     std::unique_ptr<Entity> e(new Entity(Texture::LeftVehicle, {100, 100}, {100, 100}, {0, 0}));
//     std::unique_ptr<Entity> e2(new Entity(Texture::LeftVehicle, {200, 10}, {200, 200}, {0, 0}));
//     std::unique_ptr<Player> p(new Player);
//
//     e->attachChild(std::move(e2));
//     root.attachChild(std::move(e));
//     root.move({100, 100});
//     root.saveNode(fout);
//     fout.close();
//
//     std::ifstream fin("testSave.txt");
//     auto root2 = loadNode(fin);
//     fin.close();
//
//     sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
//
//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }
//
//         window.clear(sf::Color::White);
//         window.draw(*root2);
//         window.display();
//     }
//
// }
