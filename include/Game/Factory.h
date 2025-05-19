#ifndef FACTORY_H
#define FACTORY_H
#include <memory>

#include "Core/Collection.h"
#include "Util/Animation.hpp"

namespace Game {
    class Factory {
    public:
        ~Factory() = default;


        static std::shared_ptr<Collection> CreateDiamond();
        static std::shared_ptr<Collection> CreateGold();
        static std::shared_ptr<Collection> CreateStone();
    };
} // Game

#endif //FACTORY_H
