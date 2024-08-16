#ifndef YUME_SCENE_HPP
#define YUME_SCENE_HPP

#include "../../../config.h"

class Scene {
private:
    bool scene_start_state = false;

public:
    Scene();

    virtual void start();

    virtual void update();

    virtual void render();

    ~Scene();
};

#endif