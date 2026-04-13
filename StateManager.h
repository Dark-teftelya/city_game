#pragma once
#include <memory>
#include "GameConfig.h"
#include "State.h"

class StateManager {
private:
    std::unique_ptr<State> currentState;
    bool running = true;

public:
    GameConfig config;

    void setState(std::unique_ptr<State> newState) {
        currentState = std::move(newState);
        if (!currentState)
            running = false;
    }

    void handleInput(const sf::Event& event) {   // ← const
        if (currentState)
            currentState->handleInput(event);
    }

    void update(float dt) {
        if (currentState)
            currentState->update(dt);
    }

    void draw(sf::RenderWindow& window) {
        if (currentState)
            currentState->draw(window);
    }

    bool isRunning() const {
        return running;
    }
};