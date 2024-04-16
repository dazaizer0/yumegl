#pragma once // IN DEVELOPMENT

#include "../../config.h"

#define YINPUT_KEY_SPACE              32
#define YINPUT_KEY_APOSTROPHE         39  /* ' */
#define YINPUT_KEY_COMMA              44  /* , */
#define YINPUT_KEY_MINUS              45  /* - */
#define YINPUT_KEY_PERIOD             46  /* . */
#define YINPUT_KEY_SLASH              47  /* / */
#define YINPUT_KEY_0                  48
#define YINPUT_KEY_1                  49
#define YINPUT_KEY_2                  50
#define YINPUT_KEY_3                  51
#define YINPUT_KEY_4                  52
#define YINPUT_KEY_5                  53
#define YINPUT_KEY_6                  54
#define YINPUT_KEY_7                  55
#define YINPUT_KEY_8                  56
#define YINPUT_KEY_9                  57
#define YINPUT_KEY_SEMICOLON          59  /* ; */
#define YINPUT_KEY_EQUAL              61  /* = */
#define YINPUT_KEY_A                  65
#define YINPUT_KEY_B                  66
#define YINPUT_KEY_C                  67
#define YINPUT_KEY_D                  68
#define YINPUT_KEY_E                  69
#define YINPUT_KEY_F                  70
#define YINPUT_KEY_G                  71
#define YINPUT_KEY_H                  72
#define YINPUT_KEY_I                  73
#define YINPUT_KEY_J                  74
#define YINPUT_KEY_K                  75
#define YINPUT_KEY_L                  76
#define YINPUT_KEY_M                  77
#define YINPUT_KEY_N                  78
#define YINPUT_KEY_O                  79
#define YINPUT_KEY_P                  80
#define YINPUT_KEY_Q                  81
#define YINPUT_KEY_R                  82
#define YINPUT_KEY_S                  83
#define YINPUT_KEY_T                  84
#define YINPUT_KEY_U                  85
#define YINPUT_KEY_V                  86
#define YINPUT_KEY_W                  87
#define YINPUT_KEY_X                  88
#define YINPUT_KEY_Y                  89
#define YINPUT_KEY_Z                  90
#define YINPUT_KEY_LEFT_BRACKET       91  /* [ */
#define YINPUT_KEY_BACKSLASH          92  /* \ */
#define YINPUT_KEY_RIGHT_BRACKET      93  /* ] */
#define YINPUT_KEY_GRAVE_ACCENT       96  /* ` */
#define YINPUT_KEY_WORLD_1            161 /* non-US #1  idk */
#define YINPUT_KEY_WORLD_2            162 /* non-US #2  idk */

#define YINPUT_KEY_ESCAPE             256
#define YINPUT_KEY_ENTER              257
#define YINPUT_KEY_TAB                258
#define YINPUT_KEY_BACKSPACE          259
#define YINPUT_KEY_INSERT             260
#define YINPUT_KEY_DELETE             261
#define YINPUT_KEY_RIGHT              262
#define YINPUT_KEY_LEFT               263
#define YINPUT_KEY_DOWN               264
#define YINPUT_KEY_UP                 265
#define YINPUT_KEY_PAGE_UP            266
#define YINPUT_KEY_PAGE_DOWN          267
#define YINPUT_KEY_HOME               268
#define YINPUT_KEY_END                269
#define YINPUT_KEY_CAPS_LOCK          280
#define YINPUT_KEY_SCROLL_LOCK        281
#define YINPUT_KEY_NUM_LOCK           282
#define YINPUT_KEY_PRINT_SCREEN       283
#define YINPUT_KEY_PAUSE              284
#define YINPUT_KEY_F1                 290
#define YINPUT_KEY_F2                 291
#define YINPUT_KEY_F3                 292
#define YINPUT_KEY_F4                 293
#define YINPUT_KEY_F5                 294
#define YINPUT_KEY_F6                 295
#define YINPUT_KEY_F7                 296
#define YINPUT_KEY_F8                 297
#define YINPUT_KEY_F9                 298
#define YINPUT_KEY_F10                299
#define YINPUT_KEY_F11                300
#define YINPUT_KEY_F12                301
#define YINPUT_KEY_F13                302
#define YINPUT_KEY_F14                303
#define YINPUT_KEY_F15                304
#define YINPUT_KEY_F16                305
#define YINPUT_KEY_F17                306
#define YINPUT_KEY_F18                307
#define YINPUT_KEY_F19                308
#define YINPUT_KEY_F20                309
#define YINPUT_KEY_F21                310
#define YINPUT_KEY_F22                311
#define YINPUT_KEY_F23                312
#define YINPUT_KEY_F24                313
#define YINPUT_KEY_F25                314
#define YINPUT_KEY_KP_0               320
#define YINPUT_KEY_KP_1               321
#define YINPUT_KEY_KP_2               322
#define YINPUT_KEY_KP_3               323
#define YINPUT_KEY_KP_4               324
#define YINPUT_KEY_KP_5               325
#define YINPUT_KEY_KP_6               326
#define YINPUT_KEY_KP_7               327
#define YINPUT_KEY_KP_8               328
#define YINPUT_KEY_KP_9               329
#define YINPUT_KEY_KP_DECIMAL         330
#define YINPUT_KEY_KP_DIVIDE          331
#define YINPUT_KEY_KP_MULTIPLY        332
#define YINPUT_KEY_KP_SUBTRACT        333
#define YINPUT_KEY_KP_ADD             334
#define YINPUT_KEY_KP_ENTER           335
#define YINPUT_KEY_KP_EQUAL           336
#define YINPUT_KEY_LEFT_SHIFT         340
#define YINPUT_KEY_LEFT_CONTROL       341
#define YINPUT_KEY_LEFT_ALT           342
#define YINPUT_KEY_LEFT_SUPER         343
#define YINPUT_KEY_RIGHT_SHIFT        344
#define YINPUT_KEY_RIGHT_CONTROL      345
#define YINPUT_KEY_RIGHT_ALT          346
#define YINPUT_KEY_RIGHT_SUPER        347
#define YINPUT_KEY_MENU               348


namespace input {
    bool keyPressedBool[372];
    bool keyDownBool[372];
    bool keyDownLastFrame[372];

    void update() {
        GLFWwindow* window = yumegl::getWindowPointer();

        for (int i = 30; i < 350; i++) {
            keyDownBool[i] = (glfwGetKey(window, i) == GLFW_PRESS);
            keyPressedBool[i] = (keyDownBool[i] && !keyDownLastFrame[i]);
            keyDownLastFrame[i] = keyDownBool[i];
        }
    }

    bool keyPressed(unsigned int keycode) {
        return keyPressedBool[keycode];
    }

    bool keyDown(unsigned int keycode) {
        return keyDownBool[keycode];
    }
}