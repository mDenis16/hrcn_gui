cmake_minimum_required(VERSION 3.9)

project(gui_demo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(DEMO_APP_DIR "${HRCN_GUI_ROOT}/examples/gui_demo")

message("DEMO_APP_DIR " ${DEMO_APP_DIR})


add_subdirectory(${DEMO_APP_DIR}/libs/glew-cmake)
add_subdirectory(${DEMO_APP_DIR}/libs/glfw)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${DEMO_APP_DIR}/libs/glew-cmake/include ${BLEND2D_DIR} ${BLEND2D_DIR}/src)


include_directories(${GLEW_INCLUDE_DIRS})

include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

add_definitions(-DGLEW_STATIC)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

add_executable(gui_demo ${DEMO_APP_DIR}/src/main.cpp
        components/checkbox.cpp
        components/checkbox.h
        src/gui.cpp
        src/gui.h
        components/combobox.cpp
        components/combobox.h
        components_hrcn/config.h)

target_compile_features(gui_demo PUBLIC cxx_std_20)
target_link_libraries(gui_demo glfw
${OPENGL_LIBRARIES}
libglew_static

gui)

