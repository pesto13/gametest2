#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Sprite2d
{
public:
    // Costruttore con percorso delle texture
    Sprite2d(const std::string &folderPath);

    // Cambia la texture in base al tempo
    void update(const std::optional<sf::Event> event, float deltaTime);
    void draw(sf::RenderWindow &window);
    void setPosition(sf::Vector2<float> position); // Prova a spostare lo sprite
    void input(float deltaTime);                   // Prova a gestire gli input

private:
    sf::Texture defaultTexture;        // Membro per texture predefinita TODO mi pare una merda
    std::vector<sf::Texture> textures; // Contiene i frame dell'animazione
    sf::Sprite sprite;                 // Sprite che viene mostrato
    size_t currentFrame = 0;           // Indice del frame attuale
    float elapsedTime = 0.0f;          // Tempo accumulato per il cambio frame
    float frameTime = 0.1f;            // Tempo tra un frame e l'altro (100ms)
    float velocity = 40.0f;            // Velocità dello sprite
};
