#pragma once

#ifndef __PRETTY_FUNCTION__
#define __PRETTY_FUNCTION__ __FUNCTION__
#endif

#define yumeSystem namespace
#define yumeSubsystem void

// YUME
#ifdef THIS_IS_YUME_COMPILING
#include "src/engine/shader/shader.hpp"

#include "src/engine/render/render.hpp"

#include "src/engine/objects/camera.hpp"
#include "src/engine/input/input.hpp"
#include "src/engine/audio/beep_engine.hpp"

#include "config.h"
#endif