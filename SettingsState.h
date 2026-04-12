#pragma once
#include "State.h"
#include "GameConfig.h"
#include <SFML/Graphics.hpp>
#include <vector>

class SettingsState : public State {
private:
    sf::Font font;
    std::vector<sf::Text> options;
    int selectedIndex = 0;
    void updateTextColors();
public:
    SettingsState(StateManager& manager);
    void handleInput(sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
};
