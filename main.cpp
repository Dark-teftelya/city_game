#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "MenuState.h"
#include "GameConfig.h"
#include "StateManager.h"
#include <memory>

// constexpr float PI = 3.14159265358979323846f;
int main() {
    GameConfig config;

    sf::RenderWindow window(sf::VideoMode(config.resolution), "Gorodki");
    window.setFramerateLimit(60);

    sf::Music music;
    if (music.openFromFile("media/all_mix.mp3")) {
        music.setLooping(true);           // ← было setLoop
        music.setVolume(config.soundEnabled ? 70.f : 0.f);
        music.play();
    }

    StateManager manager;
    manager.config = config;
    manager.setState(std::make_unique<MenuState>(manager));

    sf::Clock clock;

    while (window.isOpen() && manager.isRunning()) {
        // Новый способ событий в SFML 3
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            manager.handleInput(*event);   // передаём event
        }

        float dt = clock.restart().asSeconds();
        manager.update(dt);

        window.clear();
        manager.draw(window);
        window.display();

        // resize
        if (manager.config.resolution != window.getSize()) {
            window.create(sf::VideoMode(manager.config.resolution), "Gorodki");
            window.setFramerateLimit(60);
        }

        music.setVolume(manager.config.soundEnabled ? 70.f : 0.f);
    }

    return 0;
}