#ifndef FACTORY_H
#define FACTORY_H
#include <memory>
#include <queue>

#include "../Entity/Collection.h"
#include "Entity/Bomb.h"
#include "Entity/Rat.h"

namespace Game {
    class Factory {
    public:
        ~Factory() = default;

        [[nodiscard]] static std::shared_ptr<Entity> CreateEntity(const std::string &name, float zIndex);

        [[nodiscard]] static std::shared_ptr<Collection> CreateDiamond(float zIndex);

        [[nodiscard]] static std::shared_ptr<Collection> CreateGold(float zIndex);

        [[nodiscard]] static std::shared_ptr<Collection> CreateStone(float zIndex);

        [[nodiscard]] static std::shared_ptr<Entity> CreateRock(float zIndex);

        [[nodiscard]] static std::shared_ptr<Bomb> CreateBomb(float zIndex, float radius = 125);

        [[nodiscard]] static std::shared_ptr<Entity> CreateTnt(float zIndex);

        [[nodiscard]] static std::shared_ptr<Collection> CreateBag(float zIndex);

        [[nodiscard]] static std::shared_ptr<Rat> CreateRat(float zIndex);

        [[nodiscard]] static std::shared_ptr<Collection> CreatePulledGold(float zIndex);

    private:
        static inline std::unordered_map<std::string, std::queue<std::shared_ptr<Entity>>> s_Pool{};

        using Creator = std::function<std::shared_ptr<Entity>(float)>;

        static const std::unordered_map<std::string, Creator> &FactoryCatalog() {
            static const std::unordered_map<std::string, Creator> catalog = {
                {"Diamond", [](const float z) { return CreateDiamond(z); }},
                {"Gold", [](const float z) { return CreateGold(z); }},
                {"Stone", [](const float z) { return CreateStone(z); }},
                {"Bomb", [](const float z) { return CreateBomb(z); }},
                {"Rock", [](const float z) { return CreateRock(z); }},
                {"Bag", [](const float z) { return CreateBag(z); }},
                {"Rat", [](const float z) { return CreateRat(z + 1); }},
                {"PulledGold", [](const float z) { return CreatePulledGold(z); }},
            };
            return catalog;
        }
    };
} // Game

#endif //FACTORY_H
