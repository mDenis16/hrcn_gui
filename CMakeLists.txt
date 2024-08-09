cmake_minimum_required(VERSION 3.9)

project(gui)

message("HRCN GUI")


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(HRCN_GUI_ROOT ${PROJECT_SOURCE_DIR})
message(HRCN_GUI_ROOT ${HRCN_GUI_ROOT})
set(source_dir "${CMAKE_CURRENT_LIST_DIR}")
set(BLEND2D_STATIC TRUE)
 set(BLEND2D_NO_INTRINSICS FALSE)
set(BLEND2D_NO_JIT FALSE)
 set(BLEND2D_NO_NATVIS FALSE)
set(BLEND2D_NO_STDCXX TRUE)
 set(BLEND2D_NO_TLS TRUE)
 set(BLEND2D_NO_JIT_LOGGING TRUE)

add_compile_options(-fno-rtti)


# Where the 'app' and 'blend2d' are.
set(APP_DIR "${CMAKE_CURRENT_LIST_DIR}" CACHE PATH "Application directory")


set(BLEND2D_DIR "${APP_DIR}/libs/blend2d" CACHE PATH "Location of 'blend2d'")


set(ASMJIT_DIR "${APP_DIR}/libs/asmjit")


add_subdirectory(libs/blend2d)
add_subdirectory(libs/yoga/yoga)


include_directories(  ${APP_DIR}/src libs/yoga ${BLEND2D_DIR}/src)

file(GLOB_RECURSE  SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp)



add_library(gui STATIC  ${SOURCES})
target_link_libraries(gui blend2d yogacore )

if(BUILD_EXAMPLE)
    add_subdirectory(examples/gui_demo)
endif()
