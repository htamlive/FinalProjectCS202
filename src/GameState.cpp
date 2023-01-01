#include "GameState.h"
#include "AudioController.h"
#include "Consts.h"
#include "Enums.h"
#include "Level.h"
#include "SceneNode.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <memory>

GameState::GameState(sf::RenderWindow *window,
                     std::map<std::string, int> *supportedKeys,
                     std::vector<State *> *states)
    : State(window, supportedKeys, states) {
    this->gui->loadWidgetsFromFile("resources/Template/GameTemplate.txt");
    this->initKeyBinds();

    initVariables();
    initGameVariables();
    initMusic();
};

GameState::GameState(sf::RenderWindow *window,
                     std::map<std::string, int> *supportedKeys,
                     std::vector<State *> *states, const std::string &fileName)
    : State(window, supportedKeys, states) {
    this->gui->loadWidgetsFromFile("resources/Template/GameTemplate.txt");
    this->initKeyBinds();

    initVariables();
    loadGameFromFile(fileName);
    initMusic();
};
void GameState::initGameVariables() {
    auto pPlayer = std::make_unique<Player>(
        sf::Vector2f(window->getSize().x / 2 - GRID_SIZE.x,
                     (float)window->getSize().y - GRID_SIZE.y),
        GRID_SIZE);
    player = pPlayer.get();
    player->addEffect(EffectFactory::create(EffectType::Hungry));
    world = new World(sf::Vector2f(window->getSize()));
    world->init();
    world->attachChild(std::move(pPlayer));
    camera = new Camera(*player, *window, *world);
}

void GameState::loadGameFromFile(const std::string& fileName) {
    auto pPlayer = std::make_unique<Player>(
        sf::Vector2f(window->getSize().x / 2 - GRID_SIZE.x,
                     (float)window->getSize().y - GRID_SIZE.y),
        GRID_SIZE);
    player = pPlayer.get();
    player->addEffect(EffectFactory::create(EffectType::Hungry));
    world = new World(sf::Vector2f(window->getSize()));
    ifstream fin(fileName);
    if (!fin) {
        throw std::runtime_error("Cannot open file");
    }

    pPlayer->loadCurrentNode(fin);
    fin.ignore(1000, '\n');
    world = dynamic_cast<World *>(loadNode(fin).release());
    world->attachChild(std::move(pPlayer));

    camera = new Camera(*player, *window, *world);
    camera->load(fin);
    fin.close();
}

void GameState::initVariables() {
    scoreDisplay = new ScoreDisplay(gui);
    pauseMenu = new PauseMenu(window, states);
    // summaryMenu = new SummaryMenu(window, states);
    summaryMenu = nullptr;
}

void GameState::initMusic() {
    AudioController::instance().loadSoundFromFile(
        SoundEffect::CarNoise,
        "resources/music/"
        "mixkit-urban-city-sounds-and-light-car-traffic-369.wav");
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

    if(!player->isDead())
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

    if (!player->isDead() && !camera->checkIsTransistioning()) {
        if (this->ev.type == sf::Event::KeyPressed) {
            this->player->onKeyPressed(this->ev.key);
        }
    }
};

void GameState::saveGameToFile(const std::string& filePath) {
    ofstream fout(filePath);
    /*if (!fout) {
        throw std::runtime_error("Cannot open file");
    }*/
    player->saveCurrentNode(fout);

    auto p = world->detachChild(*player);
    world->saveNode(fout);
    world->attachChild(std::move(p));

    camera->save(fout);

    fout.close();
}

void GameState::update(const float &dt) {
    if (player->isDead() && !summaryMenu)
        summaryMenu =
            new SummaryMenu(window, states, scoreDisplay->finalScore());
    if (!player->isDead()) {
        auto pos = player->getAbsPosition();
        int score = (WINDOW_VIDEO_MODE.height - player->getAbsPosition().y) /
                    GRID_SIZE.y;
        scoreDisplay->update(score);
    }

    string savePath = pauseMenu->returnedSavePath();
    if (savePath != "") {
        //saveGameWithFileDialog();
        saveGameToFile(savePath);
        //pauseMenu->endState();
        //endState();
    }

    float transDt = dt;
    //if (camera->checkIsTransistioning()) {
    //    transDt = 0;
    //}
    if(pauseMenu->isPausing() && !camera->checkIsTransistioning()) transDt = 0;

    updateInput(transDt);
    world->update(sf::seconds(transDt));
    camera->update(sf::seconds(dt));
    std::set<SceneNode::Pair> collisionPairs;
    world->checkSceneCollision(*world, collisionPairs);
    // Queue to remove all colliding nodes
    // Prevent segmentation fault
    // Reason: The deleted node still exists in the collisionPairs
    vector<SceneNode *> removeQueue;
    // std::cout << "Player: " << player->getAbsPosition().x << " " <<
    // player->getAbsPosition().y << "\n";
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
                if (!player->isInvincible() && (nodeB->getCategory() == Category::Obstacle ||
                    nodeB->getCategory() == Category::Enemy)) {
                    camera->shake(sf::seconds(0.5f), 10.f);
                }
            }

            switch (nodeB->getCategory()) {
            case Category::HealthBoost:
                //                    player->addEffect(EffectFactory::create(EffectType::HealthBoost));
                removeQueue.push_back(nodeB);
                break;
            case Category::SmallSizeBoost:
                player->addEffect(
                    EffectFactory::create(EffectType::SmallSizeBoost));
                removeQueue.push_back(nodeB);
                break;
            case Category::SpeedBoost:
                player->addEffect(
                    EffectFactory::create(EffectType::SpeedBoost));
                removeQueue.push_back(nodeB);
                break;
            case Category::InvincibleBoost:
                player->addEffect(
                    EffectFactory::create(EffectType::InvincibleBoost));
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
};

void GameState::render(sf::RenderTarget *target) {
    if (!target) {
        target = this->window;
    }
    // this->player.render(target);
    // this->gui->draw();
    target->draw(*world);
    this->gui->draw();
    pauseMenu->render(target);

    if (summaryMenu)
        summaryMenu->render(target);
};
