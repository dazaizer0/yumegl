
// WINDOWS
// OPENGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// YUME ESSENTIAL HEADLINES
#include "engine/math/mathy.hpp"
#include "engine/math/colour.hpp"
#include "engine/source/yume_kernel.hpp"
#include "engine/source/panic_handler.hpp"

// BASIC
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <chrono>
#include <chrono>
#include <thread>
#include <conio.h>
#include <cstdlib>
#include <map>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// TODO: LINUX SUPPORT
// #inc...