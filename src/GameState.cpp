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
        Entity *nodeA = nullptr, *nodeB = nullptr;
        if (pair.second->getCategory() == Category::Player) {
            std::swap(pair.first, pair.second);
        }
        nodeA = reinterpret_cast<Entity *>(pair.first);
        nodeB = reinterpret_cast<Entity *>(pair.second);

        if (nodeA->getCategory() == Category::Player) {
            switch (nodeB->getCategory()) {
                case Category::Obstacle:
                    player->onCollision(nodeB);
                    break;
                case Category::Enemy:
                    player->onCollision(nodeB);
                    break;
                case Category::Wood: {
                    player->onCollideWithWood(nodeB->getVelocity());
                    break;
                }
                case Category::HealthBoost:
                    player->addEffect(EffectFactory::create(EffectType::HealthBoost));
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
