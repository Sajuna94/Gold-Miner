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

        explicit TextBox(float size = 20, const std::string &text = " ", Align align = Align::MIDDLE,
                         const std::string &path = RESOURCE_DIR "/Font/Caveat/static/Caveat-Bold.ttf");

        void SetColor(Util::Color color) const;

        void SetText(const std::string &text);

    private:
        std::shared_ptr<Util::Text> m_Text;
        Align m_Align;
    };
} // UI

#endif //TEXTBOX_H
