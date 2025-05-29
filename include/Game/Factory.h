#ifndef FACTORY_H
#define FACTORY_H
#include <memory>
#include <queue>

#include "../Entity/Collection.h"
#include "Entity/Bomb.h"

namespace Game {
    class Factory {
    public:
        ~Factory() = default;

        [[nodiscard]] static std::shared_ptr<Entity> CreateEntity(const std::string &name, float zIndex);

        [[nodiscard]] static std::shared_ptr<Collection> CreateDiamond(float zIndex);

        [[nodiscard]] static std::shared_ptr<Collection> CreateGold(float zIndex);

        [[nodiscard]] static std::shared_ptr<Collection> CreateStone(float zIndex);

        [[nodiscard]] static std::shared_ptr<Collection> CreateRock(float zIndex);

        [[nodiscard]] static std::shared_ptr<Bomb> CreateBomb(float zIndex, float radius = 125);

        [[nodiscard]] static std::shared_ptr<Entity> CreateTnt(float zIndex);

        static void Recycle(const std::shared_ptr<Entity>& entity);

    private:
        static inline std::unordered_map<std::string, std::queue<std::shared_ptr<Entity>>> s_Pool{};

        using Creator = std::function<std::shared_ptr<Entity>(float)>;

        // static const std::unordered_map<std::string, Creator> &Registry() {
        //     static const std::unordered_map<std::string, Creator> registry = {
        //         {"Diamond", CreateDiamond},
        //         {"Gold", CreateGold},
        //         {"Stone", CreateStone},
        //         {"Bomb", CreateBomb}
        //     };
        //     return registry;
        // }

        static const std::unordered_map<std::string, Creator> &Registry() {
            static const std::unordered_map<std::string, Creator> registry = {
                {"Diamond", [](const float z) { return CreateDiamond(z); }},
                {"Gold", [](const float z) { return CreateGold(z); }},
                {"Stone", [](const float z) { return CreateStone(z); }},
                {"Bomb", [](const float z) { return CreateBomb(z); }},
            };
            return registry;
        }
    };
} // Game

#endif //FACTORY_H
