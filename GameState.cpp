#include "GameState.h"
#include "MenuState.h"
#include "StateManager.h"
#include <memory>
#include <cmath>

GameState::GameState(StateManager& manager) : State(manager) {
    if (!font.loadFromFile("media/arial.ttf")) {
        // fallback если шрифт не найден
    }

    field.setSize(sf::Vector2f(340.f, 340.f));
    field.setPosition(230.f, 240.f);
    field.setFillColor(sf::Color(45, 45, 45));
    field.setOutlineThickness(6.f);
    field.setOutlineColor(sf::Color::White);

    bat.setSize(sf::Vector2f(20.f, 95.f));
    bat.setPosition(100.f, 440.f);
    bat.setFillColor(sf::Color::Yellow);

    powerBarBg.setSize(sf::Vector2f(20.f, 150.f));
    powerBarBg.setPosition(50.f, 300.f);
    powerBarBg.setFillColor(sf::Color(60, 60, 60));
    powerBarBg.setOutlineThickness(2.f);
    powerBarBg.setOutlineColor(sf::Color::White);

    powerBar.setSize(sf::Vector2f(20.f, 0.f));
    powerBar.setPosition(50.f, 450.f);
    powerBar.setFillColor(sf::Color::Red);

    scoreText.setFont(font);
    scoreText.setCharacterSize(26);
    scoreText.setFillColor(sf::Color::White);

    levelText.setFont(font);
    levelText.setCharacterSize(24);
    levelText.setFillColor(sf::Color::Cyan);

    instructionText.setFont(font);
    instructionText.setCharacterSize(20);
    instructionText.setFillColor(sf::Color(200, 200, 200));

    resetGorodki(1);
}

void GameState::resetGorodki(int level) {
    gorodki.clear();
    score = 0;
    isThrowing = false;
    isCharging = false;
    power = 0.f;
    angle = 45.0f;
    currentLevel = level;

    const float width   = 36.f;
    const float height  = 36.f;
    const float spacing = 12.f;
    const float baseY   = groundY - height;

    if (level == 1) { // Пирамида
        float startX = 310.f;
        for (int i = 0; i < 3; ++i) {
            Gorodok g;
            g.shape.setSize({width, height});
            g.shape.setPosition(startX + i * (width + spacing), baseY);
            g.shape.setFillColor(sf::Color(210, 110, 50));
            g.shape.setOutlineThickness(3);
            g.shape.setOutlineColor(sf::Color::White);
            g.velocity = {0, 0};
            g.isAlive = true;
            gorodki.push_back(g);
        }

        startX = 322.f;
        for (int i = 0; i < 2; ++i) {
            Gorodok g;
            g.shape.setSize({width, height});
            g.shape.setPosition(startX + i * (width + spacing), baseY - height);
            g.shape.setFillColor(sf::Color(210, 110, 50));
            g.shape.setOutlineThickness(3);
            g.shape.setOutlineColor(sf::Color::White);
            g.velocity = {0, 0};
            g.isAlive = true;
            gorodki.push_back(g);
        }

        Gorodok g;
        g.shape.setSize({width, height});
        g.shape.setPosition(358.f, baseY - height * 2);
        g.shape.setFillColor(sf::Color(210, 110, 50));
        g.shape.setOutlineThickness(3);
        g.shape.setOutlineColor(sf::Color::White);
        g.velocity = {0, 0};
        g.isAlive = true;
        gorodki.push_back(g);
    }
    else if (level == 2) { // Линия
        float startX = 290.f;
        for (int i = 0; i < 5; ++i) {
            Gorodok g;
            g.shape.setSize({width, height});
            g.shape.setPosition(startX + i * (width + spacing), baseY);
            g.shape.setFillColor(sf::Color(210, 110, 50));
            g.shape.setOutlineThickness(3);
            g.shape.setOutlineColor(sf::Color::White);
            g.velocity = {0, 0};
            g.isAlive = true;
            gorodki.push_back(g);
        }
    }
    else { // Квадрат 2x2
        float startX = 310.f;
        float startY = baseY;
        for (int y = 0; y < 2; ++y) {
            for (int x = 0; x < 2; ++x) {
                Gorodok g;
                g.shape.setSize({width, height});
                g.shape.setPosition(startX + x * (width + spacing), startY - y * height);
                g.shape.setFillColor(sf::Color(210, 110, 50));
                g.shape.setOutlineThickness(3);
                g.shape.setOutlineColor(sf::Color::White);
                g.velocity = {0, 0};
                g.isAlive = true;
                gorodki.push_back(g);
            }
        }
    }
}

void GameState::handleInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) 
            manager.setState(std::make_unique<MenuState>(manager));

        if (event.key.code == sf::Keyboard::R) 
            resetGorodki(currentLevel);

        if (event.key.code == sf::Keyboard::Num1) resetGorodki(1);
        if (event.key.code == sf::Keyboard::Num2) resetGorodki(2);
        if (event.key.code == sf::Keyboard::Num3) resetGorodki(3);

        if (event.key.code == sf::Keyboard::Left)  
            angle = std::max(20.f, angle - 2.f);
        if (event.key.code == sf::Keyboard::Right) 
            angle = std::min(70.f, angle + 2.f);
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !isThrowing) {
        isCharging = true;
        power = 0.f;
    }

    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space && isCharging) {
        isCharging = false;
        isThrowing = true;

        float rad = angle * M_PI / 180.0f;
        float strength = 750.f + power * 7.f;
        batVelocity.x = std::cos(rad) * strength;
        batVelocity.y = -std::sin(rad) * strength;
    }
}

void GameState::updatePhysics(float dt) {
    if (isCharging) {
        power = std::min(power + 90.f * dt, maxPower);
        powerBar.setSize(sf::Vector2f(20.f, power * 1.5f));
        powerBar.setPosition(50.f, 450.f - power * 1.5f);
        return;
    }

    if (!isThrowing) return;

    bat.move(batVelocity * dt);
    batVelocity.y += 1050.f * dt;

    for (auto& g : gorodki) {
        if (!g.isAlive) continue;
        if (bat.getGlobalBounds().intersects(g.shape.getGlobalBounds())) {
            g.isAlive = false;
            g.velocity.x = 150.f + (rand() % 350);
            g.velocity.y = -300.f - (rand() % 250);
            score++;
        }
    }

    for (auto& g : gorodki) {
        if (!g.isAlive) continue;

        g.shape.move(g.velocity * dt);
        g.velocity.y += 720.f * dt;
        g.velocity *= 0.965f;

        for (auto& other : gorodki) {
            if (&g == &other || !other.isAlive) continue;
            if (g.shape.getGlobalBounds().intersects(other.shape.getGlobalBounds())) {
                if (g.shape.getPosition().y < other.shape.getPosition().y) {
                    g.shape.setPosition(g.shape.getPosition().x, other.shape.getPosition().y - g.shape.getSize().y);
                } else {
                    other.shape.setPosition(other.shape.getPosition().x, g.shape.getPosition().y - other.shape.getSize().y);
                }
                g.velocity.y = 0;
                other.velocity.y = 0;
            }
        }

        if (g.shape.getPosition().y + g.shape.getSize().y >= groundY) {
            g.shape.setPosition(g.shape.getPosition().x, groundY - g.shape.getSize().y);
            g.velocity.y = 0.f;
            g.velocity.x *= 0.75f;
            if (std::abs(g.velocity.x) < 12.f) g.velocity.x = 0.f;
        }
    }

    if (bat.getPosition().x > 950.f || bat.getPosition().y > 700.f) {
        isThrowing = false;
        bat.setPosition(100.f, 440.f);
    }
}

void GameState::update(float dt) {
    updatePhysics(dt);

    scoreText.setPosition(20.f, 20.f);
    scoreText.setString(L"Выбито: " + sf::String(std::to_string(score) + " / 5"));

    levelText.setPosition(20.f, 65.f);
    levelText.setString(L"Уровень " + sf::String(std::to_string(currentLevel)));

    instructionText.setPosition(520.f, 20.f);
    instructionText.setString(
        L"Space — сила\n"
        L"← → — угол " + sf::String(std::to_string((int)angle)) + L"°\n"
        L"1 2 3 — уровень\n"
        L"R — рестарт\n"
        L"ESC — меню"
    );
}

void GameState::draw(sf::RenderWindow& window) {
    window.draw(field);
    window.draw(powerBarBg);
    window.draw(powerBar);

    for (const auto& g : gorodki) {
        if (g.isAlive) window.draw(g.shape);
    }

    window.draw(bat);
    window.draw(scoreText);
    window.draw(levelText);
    window.draw(instructionText);
}
