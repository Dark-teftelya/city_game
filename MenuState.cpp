#include "MenuState.h"
#include "StateManager.h"
#include "GameState.h"
#include "RulesState.h"
#include "SettingsState.h"
#include <memory>

MenuState::MenuState(StateManager& manager) : State(manager) {

    font.loadFromFile("media/arial.ttf");

    std::vector<std::string> menuItems = {
        "PLAY", "RULES", "SETTINGS", "EXIT"
    };

    for (size_t i = 0; i < menuItems.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(menuItems[i]);
        text.setCharacterSize(40);
        text.setFillColor(i == 0 ? sf::Color::Yellow : sf::Color::White);
        text.setPosition(250.f, 180.f + i * 60.f);
        options.push_back(text);
    }
}

void MenuState::handleInput(sf::Event& event) {

    if (event.type != sf::Event::KeyPressed)
        return;

    if (event.key.code == sf::Keyboard::Up) {
        options[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex = (selectedIndex - 1 + 4) % 4;
        options[selectedIndex].setFillColor(sf::Color::Yellow);
    }

    else if (event.key.code == sf::Keyboard::Down) {
        options[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex = (selectedIndex + 1) % 4;
        options[selectedIndex].setFillColor(sf::Color::Yellow);
    }

    else if (event.key.code == sf::Keyboard::Enter) {

        if (selectedIndex == 0)
            manager.setState(std::make_unique<GameState>(manager));

        else if (selectedIndex == 1)
            manager.setState(std::make_unique<RulesState>(manager));

        else if (selectedIndex == 2)
            manager.setState(std::make_unique<SettingsState>(manager));

        else if (selectedIndex == 3)
            manager.setState(nullptr); // exit
    }
}

void MenuState::update(float dt) {}

void MenuState::draw(sf::RenderWindow& window) {
    for (const auto& text : options)
        window.draw(text);
}
