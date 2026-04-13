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

    virtual void handleInput(const sf::Event& event) = 0;  // ← const добавлено
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};