#ifndef ICLICKABLE_H
#define ICLICKABLE_H

class IClickable {
public:
    virtual ~IClickable() = default;

    virtual void Click() = 0;

    [[nodiscard]] virtual bool CheckClick() = 0;

    [[nodiscard]] virtual bool OnHover() const = 0;

    // virtual void OnLeave() = 0;
    // 檢查是否可點擊
    // virtual bool IsClickable() const = 0;

    // 可傳入滑鼠座標的點擊事件
    // virtual void OnClick(int x, int y) = 0;
};

#endif //ICLICKABLE_H
