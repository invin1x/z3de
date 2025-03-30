#ifndef BINDINGS_HPP
#define BINDINGS_HPP

#include "GLFW/glfw3.h"

int move_forward                 = GLFW_KEY_W;
int move_back                    = GLFW_KEY_S;
int move_left                    = GLFW_KEY_A;
int move_right                   = GLFW_KEY_D;
int move_up                      = GLFW_KEY_SPACE;
int move_down                    = GLFW_KEY_LEFT_SHIFT;

int look_up                      = GLFW_KEY_UP;
int look_down                    = GLFW_KEY_DOWN;
int look_left                    = GLFW_KEY_LEFT;
int look_right                   = GLFW_KEY_RIGHT;
int look_roll_left               = GLFW_KEY_Q;
int look_roll_right              = GLFW_KEY_E;

int key_toggle_developer_console = GLFW_KEY_GRAVE_ACCENT;
int key_exit                     = GLFW_KEY_ESCAPE;

#endif // BINDINGS_HPP
