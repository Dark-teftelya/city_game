#include "SettingsState.h"
#include "MenuState.h"
#include <memory>
#include "StateManager.h"

SettingsState::SettingsState(StateManager& manager) : State(manager),
    options()   // важно
{
    if (!font.openFromFile("media/arial.ttf")) {
    // fallback или ошибка
    }

    std::vector<std::string> labels = {"Звук:", "Размер окна:"};
    for (size_t i = 0; i < labels.size(); ++i) {
        sf::Text text(font, "", 32);                    // ← исправлено
        text.setPosition({150.f, 180.f + i * 70.f});
        options.push_back(std::move(text));
    }
    updateTextColors();
}

void SettingsState::updateTextColors() {
    options[0].setString(L"Звук:     " + std::wstring(manager.config.soundEnabled ? L"Вкл" : L"Выкл"));
    options[1].setString(L"Размер окна:  " + std::wstring(
        manager.config.resolution.x == 800 ? L"800x600" :
        manager.config.resolution.x == 1024 ? L"1024x768" : L"1280x720"));

    for (size_t i = 0; i < options.size(); ++i) {
        options[i].setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
    }
}

void SettingsState::handleInput(const sf::Event& event) {
    if (const auto* keyEvent = event.getIf<sf::Event::KeyPressed>()) {
        auto code = keyEvent->code;

        if (code == sf::Keyboard::Key::Up || code == sf::Keyboard::Key::Down) {
            selectedIndex = (selectedIndex + 1) % 2;
            updateTextColors();
        }

        if (code == sf::Keyboard::Key::Left || code == sf::Keyboard::Key::Right) {
            if (selectedIndex == 0) {
                manager.config.soundEnabled = !manager.config.soundEnabled;
            } else if (selectedIndex == 1) {
                if (manager.config.resolution.x == 800)
                    manager.config.resolution = {1024, 768};
                else if (manager.config.resolution.x == 1024)
                    manager.config.resolution = {1280, 720};
                else
                    manager.config.resolution = {800, 600};
            }
            updateTextColors();
        }

        if (code == sf::Keyboard::Key::Enter || code == sf::Keyboard::Key::Escape) {
            manager.setState(std::make_unique<MenuState>(manager));
        }
    }
}

void SettingsState::update(float dt) {}

void SettingsState::draw(sf::RenderWindow& window) {
    sf::Text title(font, L"НАСТРОЙКИ", 40);   // ← исправлено
    title.setPosition({280.f, 80.f});
    window.draw(title);

    for (const auto& t : options) {
        window.draw(t);
    }
}