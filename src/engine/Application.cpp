#include "Application.h"

namespace engine {
    void Application::enterLoop() {
        window.create(sf::VideoMode(800, 600), "myproject");
        maxFramePeriod = 16667;
        while (window.isOpen())
        {
            loop();
        }
    }

    void Application::loop() {
        sf::Event event;
            while (window.pollEvent(event))
            {
                window.close();
            }

            if (mainClock.getElapsedTime().asMicroseconds() > maxFramePeriod)
            {
                mainClock.restart();
                window.clear();
                window.display();
            }
    }
}