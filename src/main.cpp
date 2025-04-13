#include <SFML/Graphics.hpp>
#include "player/player.hpp"
#include "engine/2d/sprite2d.hpp"
#include <iostream>

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML game");
    Sprite2d sp("assets/sprite/teddy/01-Idle/01-Idle");

    sf::Clock clock; // This clock will track the time elapsed
    while (window.isOpen())
    {
        // Calculate delta time
        sf::Time deltaTime = clock.restart();
        float delta = deltaTime.asSeconds();

        // Process events
        std::optional<sf::Event> event;
        while (auto ev = window.pollEvent())
        {
            event = ev; // Store the latest event (if any occurred this frame)
            if (event->is<sf::Event::Closed>())
                window.close();
            // You can handle other global events here if needed
        }

        // Clear the screen (do this ONCE per frame, AFTER processing all events)
        window.clear(sf::Color::Black);

        // Draw the shape
        sp.update(delta); // Pass the last polled event (or std::nullopt if no event occurred)
        sp.draw(window);

        // Update the window (do this ONCE per frame, AFTER drawing everything)
        window.display();
    }

    return EXIT_SUCCESS;
}
