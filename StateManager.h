#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameConfig.h"

class State;

class StateManager {
private:
    std::unique_ptr<State> currentState;
    bool running = true;

public:
    GameConfig config;
    sf::Music music;
    sf::RenderWindow* window = nullptr;

    void setState(std::unique_ptr<State> newState);

    void handleInput(sf::Event& event);
    void update(float dt);
    void draw(sf::RenderWindow& window);

    bool isRunning() const { return running; }
};