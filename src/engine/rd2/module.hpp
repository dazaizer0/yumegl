#ifndef YUMEGL_MODULE_HPP
#define YUMEGL_MODULE_HPP

#include "../../config.h"
#include "../../yume.h"

namespace rd2 {
    class Module {
    public:
        mathy::vec3yu<> position{ 0.0f, 0.0f, 0.0f };
        bool enable{};

        Module(mathy::vec3yu<> positionV, bool enableV);

        ~Module() = default;
    };

    Module::Module(mathy::vec3yu<> positionV, bool enableV) {
        position = positionV;
        enable = enableV;
    }

    class ExtendedModule : public Module {
    public:
        colour color = colour::WHITE();
        mathy::vec3yu<> size{};

        ExtendedModule(mathy::vec3yu<> positionV, mathy::vec3yu<> sizeV, bool enableV);

        ~ExtendedModule() = default;
    };

    ExtendedModule::ExtendedModule(mathy::vec3yu<> positionV, mathy::vec3yu<> sizeV, bool enableV) : Module(positionV, enableV) {
        size = sizeV;
    }
}
#endif
