#include "sprite2d.hpp"
#include "../utils/assetLoader.hpp"
#include <iostream>
#include <cmath>

Sprite2d::Sprite2d(const std::string &folderPath)
    : sprite(defaultTexture, {{0, 0}, {450, 523}})
{
    textures = AssetLoader::loadTexturesFromFolder(folderPath);
    if (!textures.empty())
    {
        sprite.setTexture(textures[0]); // Imposta la texture desiderata
    }
    else
    {
        std::cerr << "Errore: Nessuna texture caricata da " << folderPath << std::endl;
        // Potresti voler considerare di usare 'defaultTexture' in questo caso
    }

    sprite.scale({0.5f, 0.5f}); // Scala lo sprite a metà dimensione
    std::cout << "Origin X: " << sprite.getOrigin().x << ", Origin Y: " << sprite.getOrigin().y << std::endl;
}

void Sprite2d::update(float deltaTime)
{
    if (textures.empty())
        return;

    input(deltaTime);

    elapsedTime += deltaTime;
    if (elapsedTime >= frameTime)
    {
        elapsedTime = 0.0f;                                  // Resetta il tempo accumulato
        currentFrame = (currentFrame + 1) % textures.size(); // Passa al frame successivo ciclicamente
        sprite.setTexture(textures[currentFrame]);
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
        direction.x = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        direction.x = 1;

    // Normalize the direction vector to ensure consistent speed in all directions
    sprite.move(velocity * normalize(direction) * deltaTime);
}
