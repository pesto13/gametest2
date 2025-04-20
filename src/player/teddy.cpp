#include "teddy.hpp"
#include "../engine/utils/assetLoader.hpp"
#include <iostream>
#include <cmath>

Teddy::Teddy(const std::map<AnimationState, std::string> &animationFolders) : Sprite2d(animationFolders)
{
}

void Teddy::onPostUpdate(float deltaTime)
{

    if (!isGrounded)
    {
        setVelocity(std::nullopt, getVelocity().y + gravity * deltaTime);
    }

    // Aggiorna la posizione basata sulla velocità
    sf::Vector2f currentPosition = getSprite().getPosition();
    currentPosition.x += getVelocity().x * deltaTime;
    currentPosition.y += getVelocity().y * deltaTime;
    getSprite().setPosition(currentPosition);
}

sf::Vector2f normalize(const sf::Vector2f &vector)
{
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (length != 0.0f)
    {
        return sf::Vector2f(vector.x / length, vector.y / length);
    }
    else
    {
        return sf::Vector2f(0.0f, 0.0f); // Evita la divisione per zero
    }
}

void Teddy::input(float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        setVelocity(-teddy::lateralVelocity, std::nullopt);
        setMirrored(false);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        setVelocity(teddy::lateralVelocity, std::nullopt);
        setMirrored(true);
    }
    else
    {
        setVelocity(0, std::nullopt); // Stop horizontal movement if no keys are pressed
    }

    if (getVelocity().x != 0)
    {
        setAnimationState(AnimationState::WALKING);
    }
    else
    {
        setAnimationState(AnimationState::IDLE); // Set the state to IDLE if no keys are pressed
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && isGrounded)
    {
        setVelocity(std::nullopt, jumpForce); // Apply the jump force
        isGrounded = false;                   // Set isGrounded to false when jumping
        // currentState = State::JUMPING; // Set the state to JUMPING if the space key is pressed
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        setGrounded(false);
    }

    // Normalize the direction vector to ensure consistent speed in all directions
    // sprite.move(velocity.x * normalize(velocity) * deltaTime);
}
