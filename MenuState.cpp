#include "MenuState.h"
#include "StateManager.h"
#include "GameState.h"
#include "RulesState.h"
#include "SettingsState.h"
#include <memory>

MenuState::MenuState(StateManager& manager) : State(manager) {
    if (!font.openFromFile("media/arial.ttf")) {
    // fallback или лог
    }

    std::vector<std::string> menuItems = {"PLAY", "RULES", "SETTINGS", "EXIT"};

    for (size_t i = 0; i < menuItems.size(); ++i) {
        sf::Text text(font, menuItems[i], 40);                    // ← исправлено
        text.setFillColor(i == 0 ? sf::Color::Yellow : sf::Color::White);
        text.setPosition({250.f, 180.f + i * 60.f});
        options.push_back(std::move(text));
    }
}

void MenuState::handleInput(const sf::Event& event) {             // ← const добавлено
    if (const auto* keyEvent = event.getIf<sf::Event::KeyPressed>()) {
        if (keyEvent->code == sf::Keyboard::Key::Up) {
            options[selectedIndex].setFillColor(sf::Color::White);
            selectedIndex = (selectedIndex - 1 + 4) % 4;
            options[selectedIndex].setFillColor(sf::Color::Yellow);
        }
        else if (keyEvent->code == sf::Keyboard::Key::Down) {
            options[selectedIndex].setFillColor(sf::Color::White);
            selectedIndex = (selectedIndex + 1) % 4;
            options[selectedIndex].setFillColor(sf::Color::Yellow);
        }
        else if (keyEvent->code == sf::Keyboard::Key::Enter) {
            if (selectedIndex == 0)
                manager.setState(std::make_unique<GameState>(manager));
            else if (selectedIndex == 1)
                manager.setState(std::make_unique<RulesState>(manager));
            else if (selectedIndex == 2)
                manager.setState(std::make_unique<SettingsState>(manager));
            else if (selectedIndex == 3)
                manager.setState(nullptr);
        }
    }
}

void MenuState::update(float dt) {}

void MenuState::draw(sf::RenderWindow& window) {
    for (const auto& text : options)
        window.draw(text);
}