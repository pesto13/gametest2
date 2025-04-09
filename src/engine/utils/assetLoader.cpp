#include "assetLoader.hpp"

std::vector<sf::Texture> AssetLoader::loadTexturesFromFolder(const std::string &folderPath)
{
    std::vector<sf::Texture> textures;
    namespace fs = std::filesystem;

    for (const auto &entry : fs::directory_iterator(folderPath))
    {
        if (entry.is_regular_file())
        {
            const auto &filePath = entry.path().string();
            sf::Texture texture;
            if (texture.loadFromFile(filePath))
            {
                textures.push_back(texture);
            }
            else
            {
                std::cerr << "Errore: Impossibile caricare l'immagine!" << std::endl;
                throw std::runtime_error("Failed to load texture from " + filePath);
            }
        }
    }
    return textures;
}
