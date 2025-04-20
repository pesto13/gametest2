#pragma once

#include "../utils/assetLoader.hpp"
#include <iostream>
#include <cmath>
#include <map>
#include <string>

enum class AnimationState;

class Sprite2d
{
public:
    Sprite2d(const std::map<AnimationState, std::string> &animationFolders);

    virtual void onPreUpdate(float deltaTime) {};
    virtual void onPostUpdate(float deltaTime) {};

    void update(float deltaTime);
    void draw(sf::RenderWindow &window);
    void drawWithOutline(sf::RenderWindow &window, sf::Color outlineColor, float outlineThickness) const;

    void setAnimationState(AnimationState state);
    AnimationState getAnimationState() { return currentState; }

    void setFrameTime(float frameTime) { this->frameTime = frameTime; }
    float getFrameTime() const { return frameTime; }

    void setScaleFactor(float scale) { scaleFactor = scale; }
    float getScaleFactor() const { return scaleFactor; }

    void setMirrored(bool mirrored) { isMirrored = mirrored; }
    bool getIsMirrored() const { return isMirrored; }

    // void setSprite();
    sf::Sprite &getSprite();
    void setPosition(sf::Vector2<float> position);

    void setVelocity(std::optional<float> newX = std::nullopt, std::optional<float> newY = std::nullopt)
    {
        if (newX.has_value())
        {
            velocity.x = newX.value();
        }
        if (newY.has_value())
        {
            velocity.y = newY.value();
        }
    }
    sf::Vector2<float> getVelocity() const { return velocity; } // Restituisce la velocità dello sprite

private:
    sf::Sprite sprite;
    sf::Texture defaultTexture; // Potrebbe essere utile se il caricamento fallisce
    std::map<AnimationState, std::vector<sf::Texture>> textures;
    AnimationState currentState;
    sf::Vector2<float> velocity;
    // TODO rimuovi da qua valori default
    float elapsedTime = 0.0f;
    float frameTime = 0.05f;
    float scaleFactor = .5f;
    bool isMirrored = false;
    size_t currentFrame;
};
