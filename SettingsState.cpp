#include "SettingsState.h"
#include "MenuState.h"
#include <memory>

SettingsState::SettingsState(StateManager& manager) : State(manager) {
    font.loadFromFile("media/arial.ttf");

    std::vector<std::string> labels = {"Звук:", "Размер окна:"};
    for (size_t i = 0; i < labels.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(32);
        text.setPosition(150.f, 180.f + i * 70.f);
        options.push_back(text);
    }
    updateTextColors();
}

void SettingsState::updateTextColors() {
    options[0].setString(L"Звук:     " + sf::String(manager.config.soundEnabled ? L"Вкл" : L"Выкл"));
    options[1].setString(L"Размер окна:  " + sf::String(
        manager.config.resolution.width == 800 ? L"800x600" :
        manager.config.resolution.width == 1024 ? L"1024x768" : L"1280x720"));
    for (size_t i = 0; i < options.size(); ++i) {
        options[i].setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
    }
}

void SettingsState::handleInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) {
            selectedIndex = (selectedIndex + 1) % 2;
            updateTextColors();
        }

        if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
            if (selectedIndex == 0) {
                manager.config.soundEnabled = !manager.config.soundEnabled;
            } else if (selectedIndex == 1) {
                // Цикл разрешений
                if (manager.config.resolution.width == 800)
                    manager.config.resolution = sf::VideoMode(1024, 768);
                else if (manager.config.resolution.width == 1024)
                    manager.config.resolution = sf::VideoMode(1280, 720);
                else
                    manager.config.resolution = sf::VideoMode(800, 600);
            }
            updateTextColors();
        }

        if (event.key.code == sf::Keyboard::Enter) {
            manager.setState(std::make_unique<MenuState>(manager));
        }

        if (event.key.code == sf::Keyboard::Escape) {
            manager.setState(std::make_unique<MenuState>(manager));
        }
    }
}

void SettingsState::update(float dt) {}
void SettingsState::draw(sf::RenderWindow& window) {
    sf::Text title(L"НАСТРОЙКИ", font, 40);
    title.setPosition(280.f, 80.f);
    window.draw(title);

    for (const auto& t : options) {
        window.draw(t);
    }
}
