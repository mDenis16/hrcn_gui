cmake_minimum_required(VERSION 3.9)

project(gui)

message("HRCN GUI")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(source_dir "${CMAKE_CURRENT_LIST_DIR}")
set(BLEND2D_STATIC TRUE)

# Where the 'app' and 'blend2d' are.
set(APP_DIR "${CMAKE_CURRENT_LIST_DIR}" CACHE PATH "Application directory")


set(DEMO_APP_DIR "${CMAKE_CURRENT_LIST_DIR}/demo" CACHE PATH "Application directory")


set(BLEND2D_DIR "${APP_DIR}/libs/blend2d" CACHE PATH "Location of 'blend2d'")



add_subdirectory(libs/blend2d)
add_subdirectory(libs/yoga/yoga)

include_directories(  ${APP_DIR}/src libs/yoga ${BLEND2D_DIR}/src)


set(HRCN_GUI_SRC_LIST
 ${APP_DIR}/src/base/node.cpp
 ${APP_DIR}/src/components/window.cpp
        src/components/navbar.cpp
        src/components/navbar.hpp
        src/components/navbutton.cpp
        src/components/navbutton.h
        src/base/node_event.hpp
        src/base/mouse_event.hpp
        src/base/input_context.cpp
        src/base/input_context.hpp
        src/base/keyboard_event.hpp
        src/base/scroll_event.hpp
        src/components/c_text.cpp
        src/components/c_text.hpp
        src/base/c_event_listener.cpp
        src/base/c_event_listener.h
        src/base/events/mouse_enter_event.hpp
)


message(${HRCN_GUI_SRC_LIST})


add_library(gui  ${HRCN_GUI_SRC_LIST})

target_link_libraries(gui blend2d yogacore )

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


add_executable(gui-demo 

    ${DEMO_APP_DIR}/arm_opengl.cpp
    ${DEMO_APP_DIR}/gui.cpp
        ${DEMO_APP_DIR}/imgui/imgui.cpp
        ${DEMO_APP_DIR}/imgui/imgui_draw.cpp
        ${DEMO_APP_DIR}/imgui/imgui_tables.cpp
        ${DEMO_APP_DIR}/imgui/imgui_widgets.cpp
        ${DEMO_APP_DIR}/imgui/backends/imgui_impl_glfw.cpp
        ${DEMO_APP_DIR}/imgui/backends/imgui_impl_opengl3.cpp
    )

target_link_libraries(gui-demo glfw
${OPENGL_LIBRARIES}
GLEW::GLEW
gui)