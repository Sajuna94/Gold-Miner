#include "Core/LevelManager.h"

std::shared_ptr<Game::Level> LevelManager::CreateLevel(const int levelIndex) {
    if (levelIndex == 0)
        return std::make_shared<Game::Level>(9999, 0);

    std::shared_ptr<Game::Level> level;
    if (levelIndex <= 5) {
        level = std::make_shared<Game::Level>(30, 600 + levelIndex * 100);
        level->SetEntityLimit("Rock", 0);
        level->SetEntityLimit("Gold", 8 + levelIndex * 2);
        level->SetEntityLimit("Diamond", 2);
        level->SetEntityLimit("Bomb", 3);

        switch (levelIndex) {
            case 1: level->SetEntityLimit("Stone", 0);
                break;
            case 5: level->SetEntityLimit("Diamond", 3);
                break;
            default: break;
        }
    } else if (levelIndex <= 10) {
        level = std::make_shared<Game::Level>(60, 800 + levelIndex * 50);
        level->SetEntityLimit("Rock", 2);
    }
    return level;
}
