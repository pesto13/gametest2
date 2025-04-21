// CollisionSystem.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../src/player/teddy.hpp"

class Sprite2d; // Forward declaration

class CollisionSystem
{
public:
    void checkCollisions(Teddy &teddy, const std::vector<sf::RectangleShape> &obstacles);

private:
    void resolveCollisionWithIntersection(Teddy &teddy, const sf::FloatRect &otherBounds, const sf::FloatRect &intersection);
};
