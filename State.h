#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameConfig.h"

class StateManager;

class State {
protected:
    StateManager& manager;
public:
    State(StateManager& m) : manager(m) {}
    virtual ~State() = default;
    virtual void handleInput(sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};

class StateManager {
private:
    std::unique_ptr<State> currentState;
    bool running = true;
public:
    GameConfig config;

    void setState(std::unique_ptr<State> newState) {
        currentState = std::move(newState);
        if (!currentState) running = false;
    }

    void handleInput(sf::Event& event) {
        if (currentState) currentState->handleInput(event);
    }
    void update(float dt) {
        if (currentState) currentState->update(dt);
    }
    void draw(sf::RenderWindow& window) {
        if (currentState) currentState->draw(window);
    }
    bool isRunning() const { return running; }
};
