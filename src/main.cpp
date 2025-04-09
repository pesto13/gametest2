#include <SFML/Graphics.hpp>
#include "player/player.hpp"
#include "engine/2d/sprite2d.hpp"
#include <iostream>

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML game");
    Sprite2d sp("assets/sprite/teddy/01-Idle/01-Idle");
    // sp.setPosition({400, 300}); // Set the position of the sprite
    // Main game loop
    sf::Clock clock; // This clock will track the time elapsed
    while (window.isOpen())
    {
        // Calculate delta time
        sf::Time deltaTime = clock.restart(); // Restart the clock and get the elapsed time
        float delta = deltaTime.asSeconds();  // Convert to seconds

        // Process events
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Clear the screen
        window.clear(sf::Color::Black);

        // Draw the shape
        sp.update(delta);
        sp.draw(window);

        // Update the window
        window.display();
    }

    return 0;
}
