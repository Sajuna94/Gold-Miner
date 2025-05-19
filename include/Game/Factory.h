#ifndef FACTORY_H
#define FACTORY_H
#include <memory>

#include "Core/Collection.h"

namespace Game {
    class Factory {
    public:
        ~Factory() = default;

        static std::shared_ptr<Collection> CreateDiamond(float zIndex);

        static std::shared_ptr<Collection> CreateGold(float zIndex);

        static std::shared_ptr<Collection> CreateStone(float zIndex);
    };
} // Game

#endif //FACTORY_H
