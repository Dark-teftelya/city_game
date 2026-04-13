#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>
#include <vector>

struct Gorodok {
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    bool isAlive = true;
};

class GameState : public State {
private:
    sf::Font font;
    sf::Text scoreText;
    sf::Text instructionText;
    sf::Text levelText;

    sf::RectangleShape field;
    sf::RectangleShape bat;
    sf::RectangleShape powerBar;
    sf::RectangleShape powerBarBg;

    std::vector<Gorodok> gorodki;

    sf::Vector2f batVelocity;
    bool isThrowing = false;
    bool isCharging = false;
    float power = 0.0f;
    float angle = 45.0f;
    int score = 0;
    int currentLevel = 1;

    const float groundY = 535.f;
    const float maxPower = 100.f;

    void resetGorodki(int level);
    void updatePhysics(float dt);

public:
    GameState(StateManager& manager);
    void handleInput(const sf::Event& event) override;   // ← const добавлено
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
};