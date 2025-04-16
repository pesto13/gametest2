#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <unordered_map>

namespace teddy
{
    const float jumpForce = -900.0f;      // Forza iniziale del salto (negativa perché va verso l'alto) - regolabile
    const float gravity = 980.0f;         // Forza di gravità (pixel/secondo^2) - puoi regolarla
    const float lateralVelocity = 500.0f; // Velocità di movimento (pixel/secondo) - puoi regolarla
    const float scaleFactor = 0.5f;       // Fattore di scala dello sprite - puoi regolarlo
} // namespace teddy

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
    void drawWithOutline(sf::RenderWindow &window, sf::Color outlineColor, float outlineThickness) const;
    void setPosition(sf::Vector2<float> position); // Prova a spostare lo sprite
    void input(float deltaTime);                   // Prova a gestire gli input
    sf::Sprite getSprite() { return sprite; }      // Restituisce lo sprite

    void setVelocity(sf::Vector2<float> newVelocity) { velocity = newVelocity; } // Imposta la velocità dello sprite
    sf::Vector2<float> getVelocity() const { return velocity; }                  // Restituisce la velocità dello sprite

    void setGrounded(bool grounded) { isGrounded = grounded; } // Imposta se lo sprite è a terra
    bool getisGrounded() const { return isGrounded; }          // Restituisce se lo sprite è a terra

private:
    sf::Texture defaultTexture;                                   // Membro per texture predefinita TODO mi pare una merda
    std::unordered_map<State, std::vector<sf::Texture>> textures; // Contiene i frame dell'animazione
    sf::Sprite sprite;                                            // Sprite che viene mostrato
    size_t currentFrame = 0;                                      // Indice del frame attuale
    float elapsedTime = 0.0f;                                     // Tempo accumulato per il cambio frame
    float frameTime = 0.05f;                                      // Tempo tra un frame e l'altro (in secondi)
    sf::Vector2<float> velocity = {teddy::lateralVelocity, 0.f};  // Velocità dello sprite
    State currentState = State::IDLE;                             // Stato attuale dello sprite
    bool isRight = false;                                         // Direzione dello sprite (true = destra, false = sinistra)
    float scaleFactor = teddy::scaleFactor;                       // Fattore di scala dello sprite
    float gravity = teddy::gravity;
    bool isGrounded;                    // Indica se lo sprite è a terra
    float jumpForce = teddy::jumpForce; // Forza iniziale del salto (negativa perché va verso l'alto) - regolabile
};
