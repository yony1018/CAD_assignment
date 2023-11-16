include(FetchContent)
FetchContent_Declare(
    glew
    GIT_REPOSITORY https://github.com/nigels-com/glew.git
    GIT_TAG glew-2.2.0
)
FetchContent_MakeAvailable(glew)