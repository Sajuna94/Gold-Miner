#ifndef FACTORY_H
#define FACTORY_H
#include <memory>

#include "../Entity/Collection.h"
#include "Entity/Bomb.h"

namespace Game {
    class Factory {
    public:
        ~Factory() = default;

        static std::shared_ptr<Entity> CreateRandomEntity(float zIndex);

        static std::shared_ptr<Collection> CreateDiamond(float zIndex);

        static std::shared_ptr<Collection> CreateGold(float zIndex);

        static std::shared_ptr<Collection> CreateStone(float zIndex);

        static std::shared_ptr<Bomb> CreateBomb(float zIndex);
    };
} // Game

#endif //FACTORY_H
