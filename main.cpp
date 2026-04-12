#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "MenuState.h"
#include "GameConfig.h"
#include "StateManager.h"
#include <memory>

int main() {
    // 1. Создаём конфиг первым
    GameConfig config;

    // 2. Создаём окно с текущим разрешением
    sf::RenderWindow window(config.resolution, "Gorodki");
    window.setFramerateLimit(60);

    // 3. Музыка
    sf::Music music;
    if (music.openFromFile("media/all_mix.mp3")) {
        music.setLoop(true);
        music.setVolume(config.soundEnabled ? 70.f : 0.f);
        music.play();
    }

    // 4. StateManager
    StateManager manager;
    manager.config = config;                    // копируем настройки

    manager.setState(std::make_unique<MenuState>(manager));

    sf::Clock clock;

    sf::VideoMode lastResolution = config.resolution;
    bool lastSoundEnabled = config.soundEnabled;

    while (window.isOpen() && manager.isRunning()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            manager.handleInput(event);
        }

        float dt = clock.restart().asSeconds();
        manager.update(dt);

        window.clear(sf::Color::Black);
        manager.draw(window);
        window.display();

        // Применяем изменение разрешения
        if (manager.config.resolution.width != lastResolution.width ||
            manager.config.resolution.height != lastResolution.height) {

            lastResolution = manager.config.resolution;

            window.create(sf::VideoMode(lastResolution.width, lastResolution.height), "Gorodki");
            window.setFramerateLimit(60);
        }

        // Применяем изменение звука
        if (manager.config.soundEnabled != lastSoundEnabled) {
            lastSoundEnabled = manager.config.soundEnabled;
            music.setVolume(lastSoundEnabled ? 70.f : 0.f);
        }
    }

    return 0;
}