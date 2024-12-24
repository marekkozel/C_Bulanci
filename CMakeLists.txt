cmake_minimum_required(VERSION 3.12)
project(sdlapp C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_USE_RELATIVE_PATHS TRUE)

include_directories(.)

add_executable(game main.c
    Player/player.c
    Config/sdl.c
    Config/sdl.h
    Config/keybinds.c
    Scenes/Obstacles/obstacles.c
    Config/dynamic_array.c
    Weapons/Power_ups/power_ups.c
    Weapons/Projectils/projectils.c
    Scenes/Main_menu/main_menu.c
)

find_package(SDL2 REQUIRED)

target_include_directories(game PRIVATE ${SDL2_INCLUDE_DIRS} Config Player Weapons Scenes Assets)
target_link_libraries(game SDL2 SDL2_image SDL2_ttf)

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON -lm)

include(CheckFunctionExists)

if(NOT POW_FUNCTION_EXISTS AND NOT NEED_LINKING_AGAINST_LIBM)
    CHECK_FUNCTION_EXISTS(pow POW_FUNCTION_EXISTS)

    if(NOT POW_FUNCTION_EXISTS)
        unset(POW_FUNCTION_EXISTS CACHE)
        list(APPEND CMAKE_REQUIRED_LIBRARIES m)
        CHECK_FUNCTION_EXISTS(pow POW_FUNCTION_EXISTS)

        if(POW_FUNCTION_EXISTS)
            set(NEED_LINKING_AGAINST_LIBM True CACHE BOOL "" FORCE)
        else()
            message(FATAL_ERROR "Failed making the pow() function available")
        endif()
    endif()
endif()

if(NEED_LINKING_AGAINST_LIBM)
    target_link_libraries(game m)
endif()
