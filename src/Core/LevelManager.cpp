#include "Core/LevelManager.h"

#define MAX_LEVEL_INDEX 15

std::shared_ptr<Game::Level> LevelManager::CreateLevel(const int levelIndex) {
    if (levelIndex == 0)
        return std::make_shared<Game::Level>(9999, 0);

    std::shared_ptr<Game::Level> level;
    if (levelIndex <= 5) {
        level = std::make_shared<Game::Level>(50, 600 + levelIndex * 100);
        level->SetSpawnLimits({
            {"Diamond", 1},
            {"Gold", 4 + levelIndex * 2},
            {"Stone", 2 + levelIndex / 2},
            {"Bomb", 3},
            {"Bag", 1},
        });
        switch (levelIndex) {
            case 1: level->SetEntityLimit("Stone", 1);
                break;
            case 5: level->SetEntityLimit("Diamond", 2);
                break;
            default: break;
        }
    } else if (levelIndex <= 10) {
        const int offsetIndex = levelIndex - 5;
        level = std::make_shared<Game::Level>(70, 800 + offsetIndex * 50);
        level->SetSpawnLimits({
            {"Rock", 2},
            {"Diamond", 2},
            {"Gold", 6 + offsetIndex},
            {"Stone", 8 + offsetIndex / 2},
            {"Bomb", 8},
            {"Bag", 2},
        });
        if (offsetIndex == 5)
            level->SetEntityLimit("Rock", 3);

    } else if (levelIndex <= MAX_LEVEL_INDEX) {
        const int offsetIndex = levelIndex - 10;
        level = std::make_shared<Game::Level>(90, 1500 + offsetIndex * 150);
        level->SetSpawnLimits({
            {"Gold", 2},
            {"Stone", 2},
            {"Bomb", 15 + offsetIndex},
            {"Bag", 1},
            {"Rat", 8 + offsetIndex},
            {"PulledGold", 2},
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

void LevelManager::SetLevelIndex(const int index) {
    if (index <= 0 || MAX_LEVEL_INDEX < index) {
        printf("[!] Level index out of range\n");
        return;
    }
    s_LevelIndex = index;
}

int LevelManager::GetMaxLevelIndex() {
    return MAX_LEVEL_INDEX;
}
