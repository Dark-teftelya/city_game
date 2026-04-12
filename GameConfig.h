#pragma once
#include <SFML/Graphics.hpp>

struct GameConfig {
    bool soundEnabled = true;
    sf::VideoMode resolution = sf::VideoMode(800, 600);
    float musicVolume = 70.f;
};
