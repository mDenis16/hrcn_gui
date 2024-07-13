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


set(ASMJIT_DIR "${APP_DIR}/libs/asmjit")


add_subdirectory(libs/blend2d)
add_subdirectory(libs/yoga/yoga)
add_subdirectory(libs/glfw)


include_directories(  ${APP_DIR}/src libs/yoga ${BLEND2D_DIR}/src)

file(GLOB_RECURSE  SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp)



add_library(gui STATIC  ${SOURCES})

target_link_libraries(gui glfw blend2d yogacore )

# glfw

include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${APP_DIR}/libs/imgui  ${APP_DIR}/libs/glad  ${BLEND2D_DIR} ${BLEND2D_DIR}/src)




add_executable(gui-demo 

${APP_DIR}/libs/imgui/imgui.cpp
${APP_DIR}/libs/imgui/imgui_draw.cpp
${APP_DIR}/libs/imgui/imgui_tables.cpp
${APP_DIR}/libs/imgui/imgui_widgets.cpp
${APP_DIR}/libs/imgui/backends/imgui_impl_glfw.cpp
${APP_DIR}/libs/imgui/backends/imgui_impl_opengl3.cpp

${DEMO_APP_DIR}/gui.cpp

${DEMO_APP_DIR}/components/combobox.cpp
${DEMO_APP_DIR}/components/checkbox.cpp
${DEMO_APP_DIR}/components/slider.cpp
    ${DEMO_APP_DIR}/arm_opengl.cpp

    )

target_link_libraries(gui-demo glfw
${OPENGL_LIBRARIES}
gui)