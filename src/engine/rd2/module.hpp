#ifndef YUMEGL_MODULE_HPP
#define YUMEGL_MODULE_HPP

#include "yumegl/src/config.h"
#include "yumegl/src/yume.h"

namespace rd2 {
    class Module {
    public:
        glm::vec3 position{ 0.0f, 0.0f, 0.0f };
        bool enable{};

        Module(glm::vec3 positionV, bool enableV);
        // BODY
        ~Module() = default;
    };

    Module::Module(glm::vec3 positionV, bool enableV) {
        position = positionV;
        enable = enableV;
    }

    class ExtendedModule : public Module {
    public:
        mathy::color color = mathy::color::WHITE();
        glm::vec3 size{};

        ExtendedModule(glm::vec3 positionV, mathy::color colorV, glm::vec3 sizeV, bool enableV);
        // BODY
        ~ExtendedModule() = default;
    };

    ExtendedModule::ExtendedModule(glm::vec3 positionV, mathy::color colorV, glm::vec3 sizeV, bool enableV) : Module(positionV, enableV) {
        size = sizeV;
    }
}

#endif
