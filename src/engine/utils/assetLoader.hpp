#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <filesystem> // For filesystem operations (C++17)
#include <iostream>

class AssetLoader
{
public:
    // Load all textures from a specific folder
    static std::vector<sf::Texture> loadTexturesFromFolder(const std::string &folderPath);
};
