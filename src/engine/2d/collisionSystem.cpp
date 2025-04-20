
// // CollisionSystem.cpp
// #include "CollisionSystem.hpp"
// #include "Sprite2d.hpp"
// #include <iostream>

// void CollisionSystem::checkCollisions(Sprite2d &entity, const std::vector<sf::RectangleShape> &obstacles)
// {
//     sf::FloatRect entityBounds = entity.getSprite().getGlobalBounds();
//     for (const auto &obstacle : obstacles)
//     {
//         sf::FloatRect obstacleBounds = obstacle.getGlobalBounds();
//         if (std::optional<sf::FloatRect> intersection; intersection = entityBounds.findIntersection(obstacleBounds))
//         {
//             resolveCollisionWithIntersection(entity, obstacleBounds, intersection.value());
//             break; // O gestisci più collisioni
//         }
//     }
// }

// void CollisionSystem::resolveCollisionWithIntersection(Sprite2d &entity, const sf::FloatRect &otherBounds, const sf::FloatRect &intersection)
// {
//     sf::Vector2f entityPos = entity.getSprite().getPosition();
//     sf::FloatRect entityBounds = entity.getSprite().getGlobalBounds();
//     sf::Vector2f entityCenter = entityBounds.getCenter();
//     sf::Vector2f otherCenter = otherBounds.getCenter();

//     sf::Vector2f overlap = intersection.size;
//     sf::Vector2f correction = {0.0f, 0.0f};

//     if (overlap.x < overlap.y) // Collisione orizzontale
//     {
//         correction.x = (entityCenter.x < otherCenter.x) ? -overlap.x : overlap.x;
//         entity.setVelocity({0.0f, entity.getVelocity().y}); // Azzerare la velocità orizzontale
//     }
//     else // Collisione verticale
//     {
//         if (entityCenter.y < otherCenter.y && entity.getVelocity().y > 0.0f)
//         {
//             std::cout << "Collisione verticale dall'alto" << std::endl;
//             // Se il centro dell'entità è sopra il centro dell'altro oggetto,
//             // la correzione necessaria per separarli sull'asse Y è verso l'alto
//             // e pari alla sovrapposizione verticale (con segno negativo).
//             correction.y = -overlap.y;
//             entity.setVelocity({entity.getVelocity().x, 0.0f}); // Azzerare la velocità verticale
//             entity.setGrounded(true);                           // Imposta "a terra"
//         }
//     }
//     entity.setPosition(entityPos + correction);
// }
