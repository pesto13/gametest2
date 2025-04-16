#include <SFML/Graphics.hpp>
#include "player/player.hpp"
#include "engine/2d/sprite2d.hpp"
#include "engine/2d/collisionSystem.hpp"
#include <iostream>

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({1000, 800}), "SFML game");

    Sprite2d teddy({"assets/sprite/teddy/01-Idle/01-Idle", "assets/sprite/teddy/03-Walk/02-Walk_Happy"});
    teddy.setPosition({400, 300}); // Set the initial position of the sprite

    sf::RectangleShape ground({1000.0f, 50.0f}); // Larghezza pari alla finestra, altezza di 50 pixel
    ground.setFillColor(sf::Color::Green);       // Colore del terreno
    ground.setPosition({0.0f, 750.0f});          // Posizionato alla base della finestra (800 - 50)

    sf::RectangleShape rect({200, 50});
    rect.setFillColor(sf::Color::Red); // Set the color of the rectangle
    rect.setPosition({100, 100});      // Set the position of the rectangle

    CollisionSystem collisionSystem;                            // Create an instance of the collision system
    std::vector<sf::RectangleShape> obstacles = {rect, ground}; // List of obstacles (rectangles)

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

        teddy.input(delta);                                // Handle input for the sprite
        collisionSystem.checkCollisions(teddy, obstacles); // Check for collisions
        // Draw the shape
        teddy.update(delta);
        teddy.drawWithOutline(window, sf::Color::Red, 5.0f); // Esempio con contorno rosso di spessore approssimativo
        // teddy.draw(window);
        window.draw(rect);   // Draw the rectangle
        window.draw(ground); // Draw the rectangle

        // Update the window (do this ONCE per frame, AFTER drawing everything)
        window.display();
    }

    return EXIT_SUCCESS;
}
