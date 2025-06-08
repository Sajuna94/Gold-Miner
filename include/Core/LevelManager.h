#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H
#include <memory>

#include "Game/Level.h"


class LevelManager {
public:
    static std::shared_ptr<Game::Level> CreateLevel(int levelIndex);

    static void NextLevel();

    static int GetLevelIndex();

    static void SetLevelIndex(int index);

    static int GetMaxLevelIndex();
private:
    LevelManager() = default;

    ~LevelManager() = default;

    static inline int s_LevelIndex = 1;
};


#endif //LEVEL_MANAGER_H
