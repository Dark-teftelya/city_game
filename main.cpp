#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "MenuState.h"
#include "GameConfig.h"
#include <memory>

int main() {
    StateManager manager;

    sf::RenderWindow window(manager.config.resolution, "Gorodki");
    window.setFramerateLimit(60);

    sf::Music music;
    if (music.openFromFile("media/all_mix.mp3")) {
        music.setLoop(true);
        music.setVolume(manager.config.soundEnabled ? 70.f : 0.f);
        music.play();
    }

    manager.setState(std::make_unique<MenuState>(manager));

    sf::Clock clock;

    sf::VideoMode lastMode = manager.config.resolution;
    bool lastSound = manager.config.soundEnabled;

    while (window.isOpen() && manager.isRunning()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            manager.handleInput(event);
        }

        float dt = clock.restart().asSeconds();

        manager.update(dt);

        window.clear();
        manager.draw(window);
        window.display();

        // 🔥 изменение разрешения (ПРАВИЛЬНО)
        if (manager.config.resolution.width != lastMode.width ||
            manager.config.resolution.height != lastMode.height) {

            lastMode = manager.config.resolution;
            window.create(lastMode, "Gorodki");
        }

        // 🔥 изменение звука (НЕ каждый кадр, а только при изменении)
        if (manager.config.soundEnabled != lastSound) {
            lastSound = manager.config.soundEnabled;
            music.setVolume(lastSound ? 70.f : 0.f);
        }
    }

    return 0;
}