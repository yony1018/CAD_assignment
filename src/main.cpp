#include <iostream>
#include <algorithm>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Construction.hpp"
#include "Intereaction.cpp"

using namespace std;


GLFWwindow *window;
int InitGLFW();

int main()
{

    Solid *eight = CreateSolid();

    // GLFW初始化
    InitGLFW();
    glfwSetKeyCallback(window, Intereaction::KeyCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1, 0.4, 0.1, 1.0);

    float start_time = glfwGetTime();
    while (!glfwWindowShouldClose(window)) //每次循环的开始前检查一次GLFW是否被要求退出，是则返回true，渲染循环结束
    {
        //检测（键鼠、手柄等）设备输入的事件、window事件update，调用对应的回调函数（可手动设置）
        glfwPollEvents();
        float curt_time = glfwGetTime();
        Intereaction::Spin(curt_time - start_time);
        start_time = curt_time;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除缓存

        glViewport(0, 0, 800, 600); //显示位置

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluPerspective(45.0f, 0.8f, 0.1f, 100.0f); //调整比例尺寸

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity(); 
        glTranslatef(0.0f, 0.0f, -10.0f);
        

        glRotatef(Intereaction::vertical, 0.0f, 1.0f, 0.0f);
        glRotatef(Intereaction::horizon, 1.0f, 0.0f, 1.0f);

        glRotatef(180.0, 0.0f, 1.0f, 0.0f);
        glRotatef(90.0, 1.0f, 0.0f, 0.0f);
        DrawSolid(eight);

        //交换颜色缓存（存储GLFW窗口每个像素的颜色值），用于绘制
        glfwSwapBuffers(window);
        
    }
    glfwTerminate();
    
    return 0;
}


int InitGLFW()
{
    glfwInit(); //初始化GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //配置GLFW，主版号为3

    // 创建窗口
    window = glfwCreateWindow(800, 600, "CAD Assignment (WASD to spin view, ESC to quit)", NULL, NULL);
    if (window == NULL) //检测创建窗口是否成功
    {
        printf("Open window failed.");
        glfwTerminate(); //关闭窗口
        return -1;
    }
    //OpenGL上下文流，告诉GLFW将创建的窗口的context设为当前线程的主context
    glfwMakeContextCurrent(window); 
    //打开实验功能
    glewExperimental = true; 
    //检测初始化是否成功
    if (glewInit() != GLEW_OK)
    {
        printf("Init GLEW failed.");
        glfwTerminate();
        return -1;
    }

    return 0;
}
