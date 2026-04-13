#pragma once
#include <SFML/System/Vector2.hpp>

struct GameConfig {
    bool soundEnabled = true;

    sf::Vector2u resolution = {800, 600};

    float musicVolume = 70.f;
};