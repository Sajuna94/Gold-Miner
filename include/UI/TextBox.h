#ifndef TEXTBOX_H
#define TEXTBOX_H
#include "Util/GameObject.hpp"
#include "Util/Text.hpp"

namespace UI {
    class TextBox final : public Util::GameObject {
    public:
        enum class Align {
            LEFT, MIDDLE, RIGHT
        };

        enum class Style {
            Sans, Caveat
        };

        static constexpr auto CAVEAT_FONT_PATH = RESOURCE_DIR "/Font/Caveat/static/Caveat-Bold.ttf";
        static constexpr auto SAMSUNG_FONT_PATH = RESOURCE_DIR "/Font/samsung-sans-4/SamsungSans-Medium.ttf";

        explicit TextBox(float size = 20,
                         const std::string &text = " ",
                         Align align = Align::MIDDLE,
                         Style style = Style::Caveat);

        void SetColor(Util::Color color) const;
        void SetText(const std::string &text);

        [[nodiscard]] const glm::vec2 &GetPosition() const { return m_Transform.translation; }
        void SetPosition(const glm::vec2 &pos);

        void PrintData() const {
            printf("padding: %.2f, size: (%.2f, %.2f), pos: (%.2f, %.2f)\n", m_Padding, GetScaledSize().x, GetScaledSize().y, GetPosition().x, GetPosition().y);
        }
    private:
        Align m_Align;

        std::shared_ptr<Util::Text> m_Text;
        float m_Padding;

        [[nodiscard]] static std::string ResolveFontPath(Style style);
    };
} // UI

#endif //TEXTBOX_H
