#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H
#include <memory>

#include "Game/Level.h"


class LevelManager {
public:
    static std::shared_ptr<Game::Level> CreateLevel(int levelIndex);

private:
    LevelManager() = default;

    ~LevelManager() = default;
};


#endif //LEVEL_MANAGER_H
