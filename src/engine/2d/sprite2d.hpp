#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <unordered_map>

class Sprite2d
{
public:
    enum class State
    {
        IDLE,
        WALKING,
        JUMPING,
        ATTACKING,
        DAMAGED
    };

    Sprite2d(std::vector<std::string> folderPath);

    void update(float deltaTime);
    void draw(sf::RenderWindow &window);
    void setPosition(sf::Vector2<float> position); // Prova a spostare lo sprite
    void input(float deltaTime);                   // Prova a gestire gli input

private:
    sf::Texture defaultTexture;                                   // Membro per texture predefinita TODO mi pare una merda
    std::unordered_map<State, std::vector<sf::Texture>> textures; // Contiene i frame dell'animazione
    sf::Sprite sprite;                                            // Sprite che viene mostrato
    size_t currentFrame = 0;                                      // Indice del frame attuale
    float elapsedTime = 0.0f;                                     // Tempo accumulato per il cambio frame
    float frameTime = 0.05f;                                      // Tempo tra un frame e l'altro (100ms)
    float velocity = 500.0f;                                      // Velocità dello sprite
    State currentState = State::IDLE;                             // Stato attuale dello sprite
    bool isRight = false;                                         // Direzione dello sprite (true = destra, false = sinistra)
    float scaleFactor = 0.5f;                                     // Fattore di scala dello sprite
};
