#include "GameState.h"
#include "Consts.h"
#include "Enums.h"
#include "Level.h"
#include "SceneNode.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <memory>
#include "AudioController.h"

GameState::GameState(sf::RenderWindow *window,
                     std::map<std::string, int> *supportedKeys,
                     std::vector<State *> *states)
    : State(window, supportedKeys, states) {
    this->gui->loadWidgetsFromFile("resources/Template/GameTemplate.txt");
    this->initKeyBinds();

    initVariables();
    initMusic();
};

void GameState::initVariables() {
    auto pPlayer = std::make_unique<Player>(
        sf::Vector2f(window->getSize().x / 2 - GRID_SIZE.x,
                          (float)window->getSize().y - GRID_SIZE.y),
            GRID_SIZE);
    player = pPlayer.get();
    player->addEffect(EffectFactory::create(EffectType::Hungry));

    pauseMenu = new PauseMenu(window, states);
    //summaryMenu = new SummaryMenu(window, states);
    summaryMenu = nullptr;
    world = new World(sf::Vector2f(window->getSize()));
    ifstream fin("save.v1");
    if (fin) {
        world = dynamic_cast<World*>(loadNode(fin).release());
        std::cout << "Loaded world" << std::endl;
        fin.close();
    } else {
        world->init();
    }
    // world->setDebug(true, true);
    camera = new Camera(*player, *window, *world);
    fin.open("camera.v1");
    if (fin) {
        camera->load(fin);
    }
    fin.close();
    pPlayer->setPosition(sf::Vector2f(window->getView().getSize().x / 2 - GRID_SIZE.x,
                      window->getView().getCenter().y + (float)window->getSize().y / 2 - GRID_SIZE.y));
    std::cout << "Player pos: " << pPlayer->getPosition().y << std::endl;
    world->attachChild(std::move(pPlayer));
    std::cout << "Player abs pos: " << player->getAbsPosition().y << std::endl;
}

void GameState::initMusic() {
    AudioController::instance().loadSoundFromFile(SoundEffect::CarNoise, "resources/music/mixkit-urban-city-sounds-and-light-car-traffic-369.wav");
    AudioController::instance().playSound(SoundEffect::CarNoise);
}

GameState::~GameState() {
    delVariables();
    AudioController::instance().pauseSound();
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
    updateEventsSummaryMenu();

    if (pauseMenu->getQuit()) {
        this->endState();
    }
    if (summaryMenu && summaryMenu->getQuit()) {
        if (summaryMenu->checkPlayAgain()) {
            this->playAgain();
        } else 
            this->endState();
    }
};

void GameState::updateInput(const float &dt) {
    this->pauseMenu->updateInput();

    if (!player->isDead()) {
        if (this->ev.type == sf::Event::KeyPressed) {
            this->player->onKeyPressed(this->ev.key);
        }
    }

};

void GameState::update(const float &dt) {
    if (pauseMenu->shouldSave()) {
        ofstream fout("save.v1");
        world->rmPlayer();
        world->saveNode(fout);
        fout.close();

        fout.open("camera.v1");
        camera->save(fout);
        fout.close();
    }

    float transDt = dt;
    if (pauseMenu->isPausing())
        transDt = 0;
    updateInput(transDt);
    world->update(sf::seconds(transDt));
    camera->update(sf::seconds(transDt));

    std::set<SceneNode::Pair> collisionPairs;
    world->checkSceneCollision(*world, collisionPairs);
    // Queue to remove all colliding nodes
    // Prevent segmentation fault
    // Reason: The deleted node still exists in the collisionPairs
    vector<SceneNode*> removeQueue;
    for (auto pair : collisionPairs) {
        if (pair.second->getCategory() == Category::Player) {
            std::swap(pair.first, pair.second);
        }

        auto nodeA = pair.first;
        auto nodeB = pair.second;

        if (nodeA->getCategory() == Category::Player) {
            auto collidable = dynamic_cast<PlayerCollidable *>(nodeB);
            if (collidable) {
                collidable->onPlayerCollision(*player);
            }

            switch (nodeB->getCategory()) {
                case Category::HealthBoost:
//                    player->addEffect(EffectFactory::create(EffectType::HealthBoost));
                    removeQueue.push_back(nodeB);
                    break;
                case Category::SmallSizeBoost:
                    player->addEffect(EffectFactory::create(EffectType::SmallSizeBoost));
                    removeQueue.push_back(nodeB);
                    break;
                case Category::SpeedBoost:
                    player->addEffect(EffectFactory::create(EffectType::SpeedBoost));
                    removeQueue.push_back(nodeB);
                    break;
                case Category::InvincibleBoost:
                    player->addEffect(EffectFactory::create(EffectType::InvincibleBoost));
                    removeQueue.push_back(nodeB);
                    break;
                default:
                    break;
            }
        }
    }
    for (auto *item : removeQueue) {
        world->getCurrentLevel()->removeObject(*item);
    }

    if (player->isDead() && !summaryMenu)
        summaryMenu = new SummaryMenu(window, states);
};

void GameState::render(sf::RenderTarget *target) {
    if (!target) {
        target = this->window;
    }
    // this->player.render(target);
    this->gui->draw();
    target->draw(*world);
    pauseMenu->render(target);

    if (summaryMenu)
        summaryMenu->render(target);
};

