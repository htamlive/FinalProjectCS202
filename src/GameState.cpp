#include "GameState.h"
#include "Consts.h"
#include "Enums.h"
#include "SceneNode.h"
#include <SFML/System/Vector2.hpp>
#include <memory>

GameState::GameState(sf::RenderWindow *window,
                     std::map<std::string, int> *supportedKeys,
                     std::vector<State *> *states)
    : State(window, supportedKeys, states) {
    this->gui->loadWidgetsFromFile("resources/Template/GameTemplate.txt");
    this->initKeyBinds();

    auto pPlayer =
        std::unique_ptr<class Player>(new class Player(
                    {window->getSize().x / 2 - GRID_SIZE.x / 2, (float) window->getSize().y - GRID_SIZE.y},
                    GRID_SIZE));
    player = pPlayer.get();
    pauseMenu = new PauseMenu(window, states);
    world = new World(sf::Vector2f(window->getSize()));
    world->setDebug(true, true);
    camera = new Camera(*player, *window, *world);
    world->attachChild(std::move(pPlayer));
};

GameState::~GameState() {
    delete pauseMenu;
    delete world;
    delete camera;
};

void GameState::updateEventsPauseMenu() {
    pauseMenu->ev = this->ev;
    pauseMenu->updateEvents();
}

void GameState::updateEvents() {
    this->gui->handleEvent(this->ev);

    switch (this->ev.type) {
    case sf::Event::Closed:
        this->endState();
        break;
    case sf::Event::TextEntered:

        // update
        break;
    default:
        break;
    }

    updateEventsPauseMenu();

    if (pauseMenu->getQuit()) {
        this->endState();
    }
};

void GameState::updateInput(const float &dt) {
    this->pauseMenu->updateInput();

    if (this->ev.type == sf::Event::KeyPressed) {
        this->player->onKeyPressed(this->ev.key);
    }
};

void GameState::update(const float &dt) {
    float transDt = dt;
    if (pauseMenu->isPausing())
        transDt = 0;
    updateInput(transDt);
    world->update(sf::seconds(transDt));
    camera->update(sf::seconds(transDt));
    // this->player.update(dt);
    player->update(sf::Time(sf::seconds(transDt)));

    std::set<SceneNode::Pair> collisionPairs;
    world->checkSceneCollision(*world, collisionPairs);
    using namespace Identifier;
    for (auto pair : collisionPairs) {
        if (pair.first == player || pair.second == player) {
            endState();
        }
    }
};

void GameState::render(sf::RenderTarget *target) {
    if (!target) {
        target = this->window;
    }
    // this->player.render(target);
    this->gui->draw();
    target->draw(*world);
    target->draw(*player);
    pauseMenu->render(target);
};
