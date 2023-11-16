#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace std;

class Intereaction{
public:
    static float horizon, vertical;
    static bool keys[1024];
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void Spin(float delta_time);
};


float Intereaction::horizon = 0.0;
float Intereaction::vertical = 0.0;
bool Intereaction::keys[1024] = {false};


void Intereaction::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE); //ESC关闭窗口
    }
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void Intereaction::Spin(float delta_time)
{
    // 控制旋转速度
    float spin_speed = 1.0f * delta_time * 40;
    // 视角控制，通过计时按键按下长短调整角度
    if (keys[GLFW_KEY_A])
        vertical += spin_speed;
    if (keys[GLFW_KEY_W])
        horizon += spin_speed;
    if (keys[GLFW_KEY_S])
        horizon -= spin_speed;
    if (keys[GLFW_KEY_D])
        vertical -= spin_speed;

}
