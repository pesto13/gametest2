
// CollisionSystem.cpp
#include "CollisionSystem.hpp"
#include "Sprite2d.hpp"
#include <iostream>

void CollisionSystem::checkCollisions(Sprite2d &entity, const std::vector<sf::RectangleShape> &obstacles)
{
    sf::FloatRect entityBounds = entity.getSprite().getGlobalBounds();
    for (const auto &obstacle : obstacles)
    {
        sf::FloatRect obstacleBounds = obstacle.getGlobalBounds();
        if (std::optional<sf::FloatRect> intersection; intersection = entityBounds.findIntersection(obstacleBounds))
        {
            std::cout << "Collision detected!" << std::endl;
            entity.setGrounded(true); // Resetta lo stato di "a terra" se c'è una collisione
            resolveCollisionWithIntersection(entity, obstacleBounds, intersection.value());
            break; // O gestisci più collisioni
        }
    }
}

void CollisionSystem::resolveCollisionWithIntersection(Sprite2d &entity, const sf::FloatRect &otherBounds, const sf::FloatRect &intersection)
{
    sf::Vector2f entityPos = entity.getSprite().getPosition();
    sf::FloatRect entityBounds = entity.getSprite().getGlobalBounds();
    sf::Vector2f entityCenter = {entityBounds.position.x + entityBounds.size.x / 2.f,
                                 entityBounds.position.y + entityBounds.size.y / 2.f};
    sf::Vector2f otherCenter = {otherBounds.position.x + otherBounds.size.x / 2.f,
                                otherBounds.position.y + otherBounds.size.y / 2.f};

    sf::Vector2f overlap = {intersection.size.x, intersection.size.y};
    sf::Vector2f correction = {0.0f, 0.0f};

    if (overlap.x < overlap.y)
    {
        correction.x = (entityCenter.x < otherCenter.x) ? -overlap.x : overlap.x;
    }
    else
    {
        correction.y = (entityCenter.y < otherCenter.y) ? -overlap.y : overlap.y;
    }
    entity.setPosition(entityPos + correction);
}
