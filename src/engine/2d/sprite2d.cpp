#include <SFML/Graphics.hpp>
#include "sprite2d.hpp"
#include "../utils/assetLoader.hpp"
#include <iostream>

Sprite2d::Sprite2d(const std::map<AnimationState, std::string> &animationFolders)
    : sprite(defaultTexture, {{0, 0}, {330, 523}})
{
    sprite.setOrigin({sprite.getLocalBounds().size.x / 2.f, sprite.getLocalBounds().size.y / 2.f});

    for (const auto &pair : animationFolders)
    {
        textures[pair.first] = AssetLoader::loadTexturesFromFolder(pair.second);
        if (textures[pair.first].empty() && !pair.second.empty())
        {
            std::cerr << "Errore: Nessuna texture caricata da " << pair.second << " per lo stato " << static_cast<int>(pair.first) << std::endl;
            // Potresti voler caricare una texture di fallback qui
        }
    }

    // TODO
    // // Imposta la texture iniziale se ci sono animazioni
    // if (!textures.empty() && !textures[AnimationState::IDLE].empty())
    // {
    //     sprite.setTexture(textures[AnimationState::IDLE][0]);
    // }

    sprite.setScale({scaleFactor, scaleFactor});
}

void Sprite2d::update(float deltaTime)
{
    onPreUpdate(deltaTime);
    if (textures.empty() || textures[currentState].empty())
        return;

    elapsedTime += deltaTime;
    if (elapsedTime >= frameTime)
    {
        elapsedTime = 0.0f;
        currentFrame = (currentFrame + 1) % textures[currentState].size();
        sprite.setTexture(textures[currentState][currentFrame]);
    }

    float scaleX = isMirrored ? -scaleFactor : scaleFactor;
    sprite.setScale({scaleX, scaleFactor});
    onPostUpdate(deltaTime);
}

void Sprite2d::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}

void Sprite2d::setPosition(sf::Vector2<float> position)
{
    sprite.setPosition(position);
}

void Sprite2d::drawWithOutline(sf::RenderWindow &window, sf::Color outlineColor, float outlineThickness) const
{
    sf::CircleShape circle(5.f);
    sf::FloatRect bounds = sprite.getGlobalBounds();
    sf::RectangleShape outlineRect;

    circle.setPosition(sprite.getGlobalBounds().getCenter());
    outlineRect.setPosition(sprite.getGlobalBounds().position);
    outlineRect.setSize(sprite.getGlobalBounds().size);
    outlineRect.setFillColor(sf::Color::Transparent); // Riempiimento trasparente
    outlineRect.setOutlineColor(outlineColor);
    outlineRect.setOutlineThickness(outlineThickness); // Spessore del contorno (regola a piacere)
    circle.setFillColor(sf::Color::Red);               // Colore del cerchio (regola a piacere)
    window.draw(sprite);                               // Disegna prima il teddy
    window.draw(outlineRect);                          // Poi disegna il rettangolo di contorno
    window.draw(circle);                               // Disegna il cerchio al centro del teddy
}

void Sprite2d::setAnimationState(AnimationState state)
{
    if (currentState != state && textures.count(state))
    {
        currentState = state;
        currentFrame = 0; // Resetta l'animazione quando cambia lo stato
        if (!textures[currentState].empty())
        {
            sprite.setTexture(textures[currentState][0]);
        }
    }
}

sf::Sprite &Sprite2d::getSprite()
{
    return sprite;
}
