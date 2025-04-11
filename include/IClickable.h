#ifndef ICLICKABLE_H
#define ICLICKABLE_H

class IClickable
{
public:
    virtual ~IClickable() = default;

    virtual void Click() = 0;

    // check mouse was click the button
    [[nodiscard]] virtual bool IsClicked() = 0;

    // check mouse hover on the UI
    [[nodiscard]] virtual bool OnHover() const = 0;
};

#endif //ICLICKABLE_H
