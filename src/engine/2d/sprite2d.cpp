#include "sprite2d.hpp"
#include "../utils/assetLoader.hpp"
#include <iostream>

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
    window.draw(sprite); // Disegna lo sprite nella finestra
}

void Sprite2d::setPosition(sf::Vector2<float> position)
{
    sprite.setPosition(position);
}
