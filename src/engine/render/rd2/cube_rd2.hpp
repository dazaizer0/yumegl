#ifndef YUMEGL_CUBE_RD2_HPP
#define YUMEGL_CUBE_RD2_HPP

#include "../../../config.h"
#include "../../../yume.h"

#include "elementary_objects.hpp"

namespace rd2 {
    class Cube : public ExtendedObject {
    public:
        Cube(mathy::vec3yu<> positionV, colour colorV, mathy::vec3yu<> sizeV, bool enableV);
        ~Cube() = default;
    };

    Cube::Cube(mathy::vec3yu<> positionV, colour colorV, mathy::vec3yu<> sizeV, bool enableV)
        : ExtendedObject(position, colorV, size, enableV) {
    }
}

#endif
