#include "RulesState.h"
#include "StateManager.h"
#include "MenuState.h"
#include <memory>

RulesState::RulesState(StateManager& manager) : State(manager) {
    font.loadFromFile("media/arial.ttf");
    message.setFont(font);
    message.setString(
        L"ПРАВИЛА ИГРЫ «ГОРОДКИ»\n\n"
        L"Цель игры:\n"
        L"Выбить все 5 городков из «города» битой\n"
        L"за наименьшее количество бросков.\n\n"
        L"Поле:\n"
        L"• Город 2×2 метра\n"
        L"• Расстояние броска: 13 метров\n\n"
        L"Как играть:\n"
        L"1. Бросаешь биту\n"
        L"2. Выбитые за пределы города — засчитаны\n"
        L"3. Оставшиеся нужно добивать\n"
        L"4. На каждую фигуру 1–2 броска\n\n"
        L"ESC — вернуться в меню"
    );
    message.setCharacterSize(22);
    message.setFillColor(sf::Color::White);
    message.setPosition(70.f, 40.f);
}

void RulesState::handleInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        manager.setState(std::make_unique<MenuState>(manager));
    }
}

void RulesState::update(float dt) {}
void RulesState::draw(sf::RenderWindow& window) {
    window.draw(message);
}
