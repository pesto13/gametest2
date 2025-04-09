#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
    Player();                                // Constructor
    void setPosition(float x, float y);      // Set the position of the player
    void move(float offsetX, float offsetY); // Move the player by an offset
    void draw(sf::RenderWindow &window);     // Draw the player on the window

private:
    // sf::Sprite sprite;   // The sprite representing the player
    // sf::Texture texture; // The texture for the sprite
};
