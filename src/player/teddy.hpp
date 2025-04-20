#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <unordered_map>
#include <../src/engine/2d/sprite2d.hpp> // Assicurati di includere il tuo header per Sprite2d

namespace teddy
{
    const float jumpForce = -2200.0f;     // Forza iniziale del salto (negativa perché va verso l'alto) - regolabile
    const float gravity = 5000.0f;        // Forza di gravità (pixel/secondo^2) - puoi regolarla
    const float lateralVelocity = 500.0f; // Velocità di movimento (pixel/secondo) - puoi regolarla
    const float scaleFactor = 0.5f;       // Fattore di scala dello sprite - puoi regolarlo
} // namespace teddy

enum class AnimationState
{
    IDLE,
    WALKING,
    JUMPING,
    ATTACKING,
    DAMAGED
};

class Teddy : public Sprite2d
{
public:
    Teddy(const std::map<AnimationState, std::string> &animationFolders);

    void onPostUpdate(float deltaTime);

    void input(float deltaTime); // Prova a gestire gli input

    void setGrounded(bool grounded) { isGrounded = grounded; } // Imposta se lo sprite è a terra
    bool getisGrounded() const { return isGrounded; }          // Restituisce se lo sprite è a terra

private:
    float gravity = teddy::gravity;
    bool isGrounded = false;            // Indica se lo sprite è a terra
    float jumpForce = teddy::jumpForce; // Forza iniziale del salto (negativa perché va verso l'alto) - regolabile
};
