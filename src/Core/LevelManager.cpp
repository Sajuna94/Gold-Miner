#include "Core/LevelManager.h"

std::shared_ptr<Game::Level> LevelManager::CreateLevel(const int levelIndex) {
    if (levelIndex == 0)
        return std::make_shared<Game::Level>(9999, 0);

    std::shared_ptr<Game::Level> level;
    if (levelIndex <= 5) {
        level = std::make_shared<Game::Level>(30, 600 + levelIndex * 100);
        level->SetSpawnLimits({
            {"Diamond", 2},
            {"Gold", 4 + levelIndex * 2},
            {"Stone", 2 + levelIndex / 2},
            {"Bomb", 3},
        });
        switch (levelIndex) {
            case 1: level->SetEntityLimit("Stone", 1); break;
            case 5: level->SetEntityLimit("Diamond", 3); break;
            default: break;
        }
    } else if (levelIndex <= 10) {
        level = std::make_shared<Game::Level>(60, 800 + levelIndex * 50);
        level->SetSpawnLimits({
            {"Rock", 3},
            {"Diamond", 2},
            {"Gold", 8 + levelIndex - 5},
            {"Stone", 2 + levelIndex / 2},
            {"Bomb", 3},
        });
    }
    return level;
}

void LevelManager::NextLevel() {
    printf("current level: %d\n", s_LevelIndex);
    ++s_LevelIndex;
}

int LevelManager::GetLevelIndex() {
    return s_LevelIndex;
}


