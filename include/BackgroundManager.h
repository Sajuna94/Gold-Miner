#ifndef BACKGROUNDMANAGER_H
#define BACKGROUNDMANAGER_H
#include <memory>
#include <vector>

#include "UI/Picture.h"


class BackgroundManager {

private:
    std::vector<std::shared_ptr<UI::Picture>> m_PictureList;

public:
    explicit BackgroundManager();
};



#endif //BACKGROUNDMANAGER_H
