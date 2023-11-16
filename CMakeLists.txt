#INDEED 指定cmake最低版本
cmake_minimum_required(VERSION 3.16)

#INDEED 指定项目名及项目版本
project(euler_operator_modeling)

#OPTION 指定C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#INDEED 指定需要安装的库cmake文件所在
# list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#INDEED 添加可执行文件
    #文件名变量化声明
set(SOURCE_FILES src/main.cpp src/EulerOperator.cpp src/GUI.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})


#INDEED 指定include库   
    #可以在cmake目录中编写安装配置文件
# glfw
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})



#INDEED 链接库到编译中  此项必须在add_executable()之后
target_link_libraries(
        ${PROJECT_NAME}
        glfw
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${EXTRA_LIBS}
)
