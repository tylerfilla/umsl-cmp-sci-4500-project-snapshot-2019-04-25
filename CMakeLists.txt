#
# Cozmonaut
# Copyright 2019 The Cozmonaut Contributors
#

cmake_minimum_required(VERSION 3.4)
project(cozmonaut)

add_subdirectory(third_party/glad-cmake)
add_subdirectory(third_party/glfw)
add_subdirectory(third_party/nanovg-cmake)

find_package(Threads REQUIRED)

set(cozmo_SRC_FILES
        src/client.c
        src/global.c
        src/main.c
        src/monitor.c
        src/service.c
        )

add_executable(cozmo ${cozmo_SRC_FILES})
set_target_properties(cozmo PROPERTIES C_STANDARD 99)
target_link_libraries(cozmo PRIVATE ${CMAKE_THREAD_LIBS_INIT} glad glfw nanovg)
