#include "sprite2d.hpp"
#include "../utils/assetLoader.hpp"
#include <iostream>
#include <cmath>

Sprite2d::Sprite2d(std::vector<std::string> folderPath)
    : sprite(defaultTexture, {{0, 0}, {450, 523}})
{
    textures[State::IDLE] = AssetLoader::loadTexturesFromFolder(folderPath[0]);
    textures[State::WALKING] = AssetLoader::loadTexturesFromFolder(folderPath[1]);
    if (!textures.empty())
    {
        sprite.setTexture(textures[State::IDLE][0]); // Imposta la texture desiderata
    }
    else
    {
        std::cerr << "Errore: Nessuna texture caricata da " << folderPath[0] << std::endl;
        // Potresti voler considerare di usare 'defaultTexture' in questo caso
    }

    sprite.scale({scaleFactor, scaleFactor});                                                     // Scala lo sprite a metà dimensione
    sprite.setOrigin({sprite.getGlobalBounds().size.x / 2, sprite.getGlobalBounds().size.y / 2}); // Imposta l'origine al centro dello sprite
}

void Sprite2d::update(float deltaTime)
{
    if (textures.empty())
        return;

    input(deltaTime);

    elapsedTime += deltaTime;
    if (elapsedTime >= frameTime)
    {
        elapsedTime = 0.0f;                                                // Resetta il tempo accumulato
        currentFrame = (currentFrame + 1) % textures[currentState].size(); // Passa al frame successivo ciclicamente
        sprite.setTexture(textures[currentState][currentFrame]);

        sprite.setScale(sf::Vector2f(isRight ? -scaleFactor : scaleFactor, scaleFactor));
    }
}

void Sprite2d::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}

void Sprite2d::setPosition(sf::Vector2<float> position)
{
    sprite.setPosition(position);
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

void Sprite2d::input(float deltaTime)
{
    sf::Vector2f direction(0, 0); // Initialize direction to zero

    // Check the *current state* of the keyboard keys
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        direction.y = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        direction.y = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        direction.x = -1;
        isRight = false; // Set the direction to down if 'A' is pressed
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        direction.x = 1;
        isRight = true; // Set the direction to right if 'D' is pressed
    }

    if (direction.x != 0 || direction.y != 0)
    {
        currentState = State::WALKING; // Set the state to WALKING if any key is pressed
    }
    else
    {
        currentState = State::IDLE; // Set the state to IDLE if no keys are pressed
    }

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    // {
    //     currentState = State::JUMPING; // Set the state to JUMPING if the space key is pressed
    // }

    // Normalize the direction vector to ensure consistent speed in all directions
    sprite.move(velocity * normalize(direction) * deltaTime);
}
