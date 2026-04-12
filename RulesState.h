#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>

class RulesState : public State {
private:
    sf::Font font;
    sf::Text message;
public:
    RulesState(StateManager& manager);
    void handleInput(sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
};
