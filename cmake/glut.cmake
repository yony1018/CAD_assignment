include(FetchContent)
FetchContent_Declare(
    glut
    GIT_REPOSITORY https://github.com/FreeGLUTProject/freeglut.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(glut)