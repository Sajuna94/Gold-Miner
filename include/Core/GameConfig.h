#ifndef GAMECONFIG_H
#define GAMECONFIG_H

namespace Item
{
    enum class Props
    {
        TNT,
        STONE_LIGHT,
    };

    enum class Collectible
    {
        BAG,
        BOMB,
        DIAMOND,
        GOLD,
        ROCK,
    };

    inline const std::unordered_map<Props, std::string> propsImages{
        {Props::TNT, RESOURCE_DIR"/Textures/tnt.png"},
        {Props::STONE_LIGHT, RESOURCE_DIR"/Textures/stone.png"},
    };

    inline const std::unordered_map<Collectible, std::vector<std::string>> collectibleImages{
        {
            Collectible::BAG, {
                RESOURCE_DIR "/Textures/bag.png",
            }
        },
        {
            Collectible::BOMB, {
                RESOURCE_DIR "Sprites/bomb_0.png",
                RESOURCE_DIR "Sprites/bomb_1.png",
                RESOURCE_DIR "Sprites/bomb_2.png"
            }
        },
        {
            Collectible::DIAMOND, {
                RESOURCE_DIR "Sprites/diamond_0.png",
                RESOURCE_DIR "Sprites/diamond_1.png"
            }
        },
        {
            Collectible::GOLD, {
                RESOURCE_DIR "Sprites/gold_0.png",
                RESOURCE_DIR "Sprites/gold_1.png",
                RESOURCE_DIR "Sprites/gold_2.png"
            }
        },
        {
            Collectible::ROCK, {
                RESOURCE_DIR "Sprites/rock.png"
            }
        }
    };

    template <typename T>
    inline std::string GetPath(const T item)
    {
        if constexpr (std::is_same_v<T, Props>) return propsImages.at(item);
        if constexpr (std::is_same_v<T, Collectible>) return collectibleImages.at(item);
        return "";
    }
}


#endif //GAMECONFIG_H
