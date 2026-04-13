#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>
#include <vector>

class MenuState : public State {
private:
    sf::Font font;
    std::vector<sf::Text> options;
    int selectedIndex = 0;
public:
    MenuState(StateManager& manager);
    void handleInput(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
};